#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>
#include <linux/slab.h>
#include <linux/string.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sunanda");
MODULE_DESCRIPTION("VCC assignment");

static int print_processes(void)
{
	struct task_struct *task;

    printk(KERN_INFO "Hi, Kernel\n");
    for_each_process(task) {
        if (task->pid == 1) {
            printk(KERN_INFO "Stack Max limit: %lx Stack Pointer: %lx PID: %d, Name: %s\n", task->stack,task->thread.sp, task->pid, task->comm);
        }
    }
	return 0;
}

static void dummy_exit(void)
{
	printk(KERN_INFO "Bye, Kernel\n");
}

module_init(print_processes);
module_exit(dummy_exit);


