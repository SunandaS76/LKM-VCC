Part A:

Output:

[ 1042.065530] Listing processes:
[ 1042.065586] State: 0 PID: 5544, Name: insmod
[ 1229.554839] Bye, Kernel

Explaination:

Process state = Running / 0
When we equate task->state to running we get all the running/runnable states




Part B:

Output: 
[ 3676.171249] Hii, Kernel
[ 3676.171319] pid: 2607, heap_size: 3012630, name: firefox
[ 3683.096997] Bye, Kernel

Explaination:

We traverse all the active tasks, check the sizes of heaps in all the task
find the task with maximum size and print it 




Part C:

Output:

[ 5062.307855] Listing processes:
[ 5062.307862] Stack Pointer: ffffac14c0070000 PID: 1, Name: systemd
[ 5122.930199] Bye, Kernel

Explaination:

We find the task with pid = 1, which is init and print its task->thread.sp pointer




Part D:
Command:

sudo insmod d.ko virtual_addr=0x7fcfba5fd000 pid=1806

[ 1170.147122] Hello, Kernel
[ 1170.147133] Physical address:ffffffffc10fd000

sudo insmod d.ko virtual_addr=0x7fcfba5fd000 pid=1706

[ 1277.716118] virtual address not mapped, Kernel

Explaination:

Page table walked in the program. If task or mm doesnt exit it returns the same
if virtual address is not mapped output is address not mapped
if address is mapped physical address is displayed




Part E:

Output
Command: sudo insmod e.ko pid=2004

[ 1861.963180] VM size: 5613220 
[ 1861.963183] PM size: 275948 `

Explaination:

We take total_vm to get virtual memory size and get_mm_rss for physical memory size and multiply it with page size to get exact memory size we required.

Lazzy allocation explaination:
First output is taken for a program where we allocate, some memory dynamically (array) but do not use it. The physical memory size is 1612. But in second output we use the memory of array by initialising the array. We can see the physical memory size after that is 1644, 32B increased. This means that when process accesses the memory, os allocates the page as required and not as soon as process gets created. 

[  783.902540] Hi, Kernel
[  783.902546] VM size: 2772 
[  783.902550] PM size: 1612 
[  783.921661] Bye, Kernel

[  783.955337] Hi, Kernel
[  783.955341] VM size: 2772 
[  783.955344] PM size: 1644 
[  783.967738] Bye, Kernel
