#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>
int pid = 4453;
int size = 4096;
module_param(pid, int, 0);

int get_sizes(pid_t pid, unsigned long *virtual, unsigned long *physical) {
    struct task_struct *task;
    struct mm_struct *mm;
    struct vm_area_struct *vma;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task) {
		        printk(KERN_ERR "Task not found\n");
        return -1;
    }

    mm = task->mm;
    *virtual = 0;
    *physical = 0;

   
    *physical = get_mm_rss(mm) * PAGE_SIZE / 1024;
	*virtual = mm->total_vm * PAGE_SIZE / 1024;
    return 0;
}

static int __init my_module_init(void) {
    
	    printk(KERN_INFO "Hi, Kernel\n");

    unsigned long virtual, physical;
	int res = get_sizes(pid, &virtual, &physical);
    if (res == 0) {
        printk(KERN_INFO "VM size: %lu \n", virtual);
       printk(KERN_INFO "PM size: %lu \n", physical);
    } else {
        printk(KERN_ERR "Error getting memory information\n");
    }

    return 0;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "Bye, Kernel\n");
}

module_init(my_module_init);
module_exit(my_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Determines the size of the virtual and physical address space for a specified process");
