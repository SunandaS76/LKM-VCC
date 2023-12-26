
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/moduleparam.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sunanda");
MODULE_DESCRIPTION("VCC assign");

static unsigned long virtual_addr = 0x7fcfba5fd000;

int size = 4096;
static int pid;

module_param(virtual_addr, long, 0);
module_param(pid, int, 0);

static int get_vas(void)
{

    struct task_struct *task;
    struct mm_struct *mm;
    task = pid_task(find_vpid(pid), PIDTYPE_PID);

    if (task)
    {
        mm = task->mm;
        if (!mm)
            return 0;

        pgd_t *p1 = pgd_offset(mm, virtual_addr);

        if (!pgd_none(*p1) && !pgd_bad(*p1))
        {
            p4d_t *p2 = p4d_offset(p1, virtual_addr);
            if (!p4d_none(*p2) && !p4d_bad(*p2))
            {

                pud_t *p3 = pud_offset(p2, virtual_addr);

                if (!pud_none(*p3) && !pud_bad(*p3))
                {

                    pmd_t *p4 = pmd_offset(p3, virtual_addr);
                    if (!pmd_none(*p4) && !pmd_bad(*p4))
                    {

                        pte_t *pte = pte_offset_map(p4, virtual_addr);
                        if (!pte_none(*pte))
                        {
                            struct page *pg = pte_page(*pte);
                            unsigned long phys = page_to_phys(pg);
                            pr_info("pid: %d, Physical address:%lx, Virtual Address: %lx\n", task->pid, phys, virtual_addr);
                        }
                        else
                        {
                            printk(KERN_INFO "virtual address not mapped, Kernel\n");
                            pte_unmap(pte);
                            return 0;
                        }
                    }
                    else
                    {
                        printk(KERN_INFO "virtual address not mapped, Kernel\n");
                        return 0;
                    }
                }
                else
                {
                    printk(KERN_INFO "virtual address not mapped, Kernel\n");

                    return 0;
                }
            }
            else
            {
                printk(KERN_INFO "virtual address not mapped, Kernel\n");

                return 0;
            }
        }
        else
        {
            printk(KERN_INFO "virtual address not mapped, Kernel\n");
            return 0;
        }
    }

    return 0;
}

static void dummy_exit(void)
{
    // kfree(virtual_addr);
    printk(KERN_INFO "Bye, Kernel\n");
}

module_init(get_vas);
module_exit(dummy_exit);
