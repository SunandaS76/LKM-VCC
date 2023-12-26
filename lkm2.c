#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/mm.h>

static void get_heap_info(struct task_struct *task)
{
    struct mm_struct *mm = task->mm;
    if (!mm)
        return;

    unsigned long heap_size = mm->total_vm - mm->stack_vm;
    printk(KERN_INFO "pid: %d, heap_size: %lu\n", task->pid, heap_size);
}

static void get_largest_task(void)
{
    struct task_struct *task, *ltask = NULL;
    unsigned long largest_heap_size = 0;

    for_each_process(task)
    {
        struct mm_struct *mm = task->mm;
        if (!mm)
            continue;

        unsigned long heap_size = mm->brk - mm->start_brk;
        if (heap_size > largest_heap_size)
        {
            largest_heap_size = heap_size;
            ltask = task;
        }
    }

    if (ltask)
        get_heap_info(ltask);
    else
        printk(KERN_INFO "No task found with heap memory\n");
}

static int __init module_entry_init(void)
{
    printk(KERN_INFO "Hii, Kernel\n");
    get_largest_task();
    return 0;
}

static void __exit module_exit_exit(void)
{
    printk(KERN_INFO "Bye, Kernel\n");
}

module_init(module_entry_init);
module_exit(module_exit_exit);
MODULE_LICENSE("GPL");

