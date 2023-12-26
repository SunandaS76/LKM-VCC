#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>
#include <linux/slab.h>
#include <linux/string.h>


#define MAX_PID 32768

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sunanda");
MODULE_DESCRIPTION("VCC assign hello world");

static int print_processes(void)
{
	struct task_struct *task;

    printk(KERN_INFO "Listing processes:\n");
    for_each_process(task) {
        if (task->__state == 0) {
            printk(KERN_INFO "State: %ld PID: %d, Name: %s\n", task->__state, task->pid, task->comm);
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


