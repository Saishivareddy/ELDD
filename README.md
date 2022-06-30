# Embedded Linux Device Drivers

## Linux Architecture
- Linux is primarily divided into User Space & Kernel Space. These two components interact through a System Call Interface – which is a predefined and matured interface to Linux Kernel for Userspace applications. The below image will give you a basic understanding.

  ![https://embetronicx.com/wp-content/uploads/2017/08/kernel-space-vs-user-space.png](https://embetronicx.com/wp-content/uploads/2017/08/kernel-space-vs-user-space.png)

  ### Kernel Space

  - Kernel space is where the kernel (i.e., the core of the operating system) executes (i.e., runs) and provides its services.

  ### User Space

  - User Space is where the user applications are executed.

    

  ## Linux Kernel Modules

  - Kernel modules are pieces of code that can be loaded and unloaded into  the kernel upon demand. They extend the functionality of the kernel  without the need to reboot the system.

  - Custom codes can be added to Linux kernels via two methods.

    - The basic way is to add the code to the kernel source tree and recompile the kernel. --> ***In-tree Kernel Module*** 
    - A more efficient way is to do this is by adding code to the kernel while  it is running. This process is called loading the module, where the  module refers to the code that we want to add to the kernel.  --> ***Out of tree Kernel Module***

  - Since we are loading these codes at runtime and they are not part of the official Linux kernel, these are called **Loadable Kernel Modules (LKM)**.

  - LKMs can perform a variety of task, but basically, they come under three main categories,

    - Device drivers

    - Filesystem drivers

    - System calls

      

  ### LInux Device Drivers

  - A device driver is designed for a specific piece of hardware. The kernel uses it to communicate with that piece of hardware without having to  know any details of how the hardware works.

    

  ### File Sysytem Drivers

  - A filesystem driver interprets the contents of a filesystem (which is  typically the contents of a disk drive) as files and directories and  such. There are lots of different ways of storing files and directories  and such on disk drives, on network servers, and in other ways. For each way, you need a filesystem driver. For example, there’s a filesystem  driver for the ext2 filesystem type used almost universally on Linux  disk drives. There is one for the MS-DOS filesystem too, and one for  NFS

    

  ### System calls

  - Userspace programs use system calls to get services from the kernel. For example, there are system calls to read a file, to create a new process, and to  shut down the system. Most system calls are integral to the system and  very standard, so are always built into the base kernel (no LKM option).

    

  ### Advantages of LKM

  - One major advantage they have is that we don’t need to keep rebuilding the  kernel every time we add a new device or if we upgrade an old device.  This saves time and also helps in keeping our base kernel error-free.

  - LKMs are very flexible, in the sense that they can be loaded and unloaded  with a single line of command. This helps in saving memory as we load  the LKM only when we need them.

    

  ### Differences Between Kernel Modules and User Programs

  - **Kernel modules have separate address spaces.** A module runs in kernel space. An application runs in userspace. The  system software is protected from user programs. Kernel space and user space have their own memory address spaces.

  - **Kernel modules have higher execution privileges.** Code that runs in kernel space has greater privilege than code that runs in userspace.

  - **Kernel modules do not execute sequentially.** A user program typically executes sequentially and performs a single task from beginning to end. A kernel module does not execute sequentially. A kernel module registers itself in order to serve future requests.

  - **Kernel modules use different header files.** Kernel modules require a different set of header files than user programs require.

    

  ### Difference Between Kernel Drivers and Kernel Modules

  - A kernel module is a bit of compiled code that can be inserted into the kernel at run-time, such as with `insmod` or `modprobe`.

  - A driver is a bit of code that runs in the kernel to talk to some hardware device. It “drives” the hardware. Almost every bit of hardware  in your computer has an associated driver.

    

  ## Device Driver

  - A device driver is a particular form of software application that is designed to enable interaction with hardware devices. 

  - Without the required device driver, the corresponding hardware device fails to work.

  - A device driver usually communicates with the hardware by means of the communications subsystem or computer bus to which the hardware is  connected. 

  - Device drivers are operating system-specific and  hardware-dependent. 

  - A device driver acts as a translator between the  hardware device and the programs or operating systems that use it.

    

  ### Types

  - Character Driver
  - Block Driver
  - Network Driver

  

  ***In Linux, everything is a file. It means Linux treats everything as a File even hardware.***

  

  ### Character Device

  - A char file is a hardware file that reads/writes data in character by character fashion. 
  - Some classic examples are keyboard, mouse, serial printer.

  ### Block Device

  - A block file is a hardware file that reads/writes data in blocks instead of character by character.
  - This type of file is very much useful when we want to write/read data in a bulk fashion. 
  - Examples : HDD, USB, and CDROM's are block devices.

  ### Network Device

  - A network device is, so far as Linux’s network subsystem is concerned, an entity that sends and receives packets of data. 
  - Examples : Ethernet, Wi-Fi, Bluetooth

  


- Creating a Device file Manually
```bash
mknod -m <permissions> <name> <device type> <major> <minor>
<name> – your device file name that should have a full path (/dev/name)
<device type> – Put c or b
c – Character Device
b – Block Device
<major> – major number of your driver
<minor> – minor number of your driver
-m <permissions> – optional argument that sets the permission bits of the new device file to permissions
```

### copy_from_user()

- This function is used to Copy a block of data from user space (Copy data from user space to kernel space).

**`unsigned long copy_from_user(void \*to, const void __user \*from, unsigned long  n);`**

**Arguments**

**`to`** – Destination address, in the kernel space

**`from`** – The source address in the user space

**`n`** – Number of bytes to copy

**Returns number of bytes that could not be copied. On success, this will be zero.**

### copy_to_user()

- This function is used to Copy a block of data into userspace (Copy data from kernel space to user space).

**`unsigned long copy_to_user(const void __user \*to, const void \*from, unsigned long  n);`**

**Arguments**

**`to`** – Destination address, in the user space

**`from`** – The source address in the kernel space

**`n`** – Number of bytes to copy

**Returns number of bytes that could not be copied. On success, this will be zero.**

## Open()

This function is called first, whenever we are opening the device file. In  this function, I am going to allocate the memory using `kmalloc`. In the userspace application, you can use **`open()`** system call to open the device file.

```c
static int my_open(struct inode *inode, struct file *file)
{
​        /*Creating Physical memory*/
​        if((kernel_buffer = kmalloc(mem_size , GFP_KERNEL)) == 0){
​            printk(KERN_INFO "Cannot allocate memory in kernel\n");
​            return -1;
​        }
​        printk(KERN_INFO "Device File Opened...!!!\n");
​        return 0;
}
```

## write()

When writing the data to the device file it will call this write function.  Here I will copy the data from user space to kernel space using **`copy_from_user()`** function. In the userspace application, you can use **`write()`** system call to write any data the device file.

```c
static ssize_t my_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
​        copy_from_user(kernel_buffer, buf, len);
​        printk(KERN_INFO "Data Write : Done!\n");
​        return len;
}
```

## read()

When we read the device file it will call this function. In this function, I used **`copy_to_user()`**. This function is used to copy the data to the userspace application. In the userspace application, you can use **read()** system call to read the data from the device file.

```c
static ssize_t my_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
​        copy_to_user(buf, kernel_buffer, mem_size);
​        printk(KERN_INFO "Data Read : Done!\n");
​        return mem_size;
}
```

## close()

When we close the device file that will call this function. Here I will free the memory that is allocated by **`kmalloc`** using **`kfree()`**. In the userspace application, you can use **`close()`** system call to close the device file.

```c
static int my_release(struct inode *inode, struct file *file)
{
​        kfree(kernel_buffer);
​        printk(KERN_INFO "Device File Closed...!!!\n");
​        return 0;
}
```

## IOCTL

IOCTL is referred to as Input and Output Control, which is used to talking to device drivers. This system call, available in most driver categories. The major use of this is in case of handling some specific operations of a device for which the kernel does not have a system call by default.

- Some real-time applications of ioctl are Ejecting the media from a “cd”  drive, change the Baud Rate of Serial port, Adjust the Volume, Reading  or Writing device registers, etc.

#### Steps involved in IOCTL

There are some steps involved to use IOCTL.

- Create IOCTL command in driver
- Write IOCTL function in the driver
- Create IOCTL command in a Userspace application
- Use the IOCTL system call in a Userspace



## Waitqueue in Linux

## Introduction

When you write a Linux Driver or Module or Kernel Program, Some processes  should wait or sleep for some event. There are several ways of handling  sleeping and waking up in Linux, each suited to different needs.  Waitqueue also one of the methods to handle that case.

Whenever a process must wait for an event (such as the arrival of data or the  termination of a process), it should go to sleep. Sleeping causes the  process to suspend execution, freeing the processor for other uses.  After some time, the process will be woken up and will continue with its job when the event which we are waiting for has arrived.

Wait queue is a mechanism provided in the kernel to implement the wait. As  the name itself suggests, waitqueue is the list of processes waiting for an event. In other words, A wait queue is used to wait for someone to wake you up when a certain condition is true. They must be used carefully to ensure there is no race condition.

There are 3 important steps in Waitqueue.

1. Initializing Waitqueue
2. Queuing (Put the Task to sleep until the event comes)
3. Waking Up Queued Task

## Initializing Waitqueue

Use this Header file for Waitqueue (**`include /linux/wait.h`**). There are two ways to initialize the waitqueue.

1. Static method
2. Dynamic method

You can use any one of the methods.

### Static Method

```c
DECLARE_WAIT_QUEUE_HEAD(wq);
```

Where the “wq” is the name of the queue on which task will be put to sleep.

### Dynamic Method

```c
wait_queue_head_t wq;
init_waitqueue_head (&wq);
```

## Queuing

Once the wait queue is declared and initialized, a process may use it to go  to sleep. There are several macros are available for different uses. We  will see each one by one.

1. **wait_event**
2. **wait_event_timeout**
3. **wait_event_cmd**
4. **wait_event_interruptible**
5. **wait_event_interruptible_timeout**
6. **wait_event_killable**

Old kernel versions used the functions **`sleep_on()`** and **`interruptible_sleep_on()`**, but those two functions can introduce bad race conditions and should not be used.

Whenever we use the above one of the macro, it will add that task to the  waitqueue which is created by us. Then it will wait for the event.

### 1. wait_event

sleep until a condition gets true.

```bash
wait_event(wq, condition);

wq – the waitqueue to wait on
condition – a C expression for the event to wait for
```

### 2. wait_event_timeout

sleep until a condition gets true or a timeout elapses

```bash
wait_event_timeout(wq, condition, timeout);

wq – the waitqueue to wait on
condtion – a C expression for the event to wait for
timeout – timeout, in jiffies
```

### 3. wait_event_cmd

sleep until a condition gets true

```bash
wait_event_cmd(wq, condition, cmd1, cmd2);

wq – the waitqueue to wait on
condtion – a C expression for the event to wait for
cmd1 – the command will be executed before sleep
cmd2 – the command will be executed after sleep
```

### 4. wait_event_interruptible

sleep until a condition gets true

```bash
wait_event_interruptible(wq, condition);

wq – the waitqueue to wait on
condtion – a C expression for the event to wait for
```

### 5. wait_event_interruptible_timeout

sleep until a condition gets true or a timeout elapses

```bash
wait_event_interruptible_timeout(wq, condition, timeout);

wq– the waitqueue to wait on
condtion – a C expression for the event to wait for
timeout – timeout, in jiffies
```

### 6. wait_event_killable

sleep until a condition gets true

```bash
wait_event_killable(wq, condition);

wq – the waitqueue to wait on
condtion– a C expression for the event to wait for
```

## Waking Up Queued Task

When some Tasks are in sleep mode because of the waitqueue, then we can use the below function to wake up those tasks.

1. **wake_up**
2. **wake_up_all**
3. **wake_up_interruptible**
4. **wake_up_sync and `wake_up_interruptible_sync`**

### 1. wake_up

wakes up only one process from the wait queue which is in non-interruptible sleep.

```bash
wake_up(&wq);

wq – the waitqueue to wake up
```

### 2. wake_up_all

wakes up all the processes on the wait queue

```bash
wake_up_all(&wq);

wq – the waitqueue to wake up
```

### 3 . wake_up_interruptible

wakes up only one process from the wait queue that is in interruptible sleep

```bash
wake_up_interruptible(&wq);

wq– the waitqueue to wake up
```

### 4. wake_up_sync and wake_up_interruptible_sync

```bash
wake_up_sync(&wq);

wake_up_interruptible_sync(&wq);
```

 

## Kernel Synchronization

## Race Condition

A race condition occurs when two or more threads can access shared data  and they try to change it at the same time. Because the thread scheduling algorithm can swap between threads at any time, we don’t know the order in which the threads will attempt to access the shared data.  Therefore, the result of the change in data is dependent on the thread  scheduling algorithm, i.e. both threads are “racing” to access/change  the data.

To avoid race conditions, we have many ways like Semaphore, Spinlock, and Mutex. 

## Mutex

A *mutex* is a mutual exclusion lock. Only one thread can hold the lock.

A mutex can be used to prevent the simultaneous execution of a block of  code by multiple threads that are running in a single or multiple  processes.

Mutex is used as a synchronization primitive in situations where a resource has to be shared by multiple threads simultaneously.

A mutex has ownership. The thread which locks a Mutex must also unlock it.

So whenever you are accessing a shared resource that time first we lock the mutex and then access the shared resource. When we are finished with that shared resource then we unlock the Mutex.

I hope you got some idea about Mutex. Now, let us look at Mutex in the Linux Kernel.

## Mutex in Linux Kernel

Today most major operating systems employ multitasking. Multitasking is where multiple threads can execute in parallel and thereby utilizing the CPU  in an optimum way. Even though, multitasking is useful, if not implemented cautiously can lead to concurrency issues (Race condition), which can be very difficult to handle.

The actual mutex type (minus debugging fields) is quite simple:

```c
struct mutex {
    atomic_t        count;
    spinlock_t      wait_lock;
    struct list_head    wait_list;
};
```

We will be using this structure for Mutex in Linux kernel. Refer to `Linux/include/linux/mutex.h`

### Initializing Mutex

We can initialize Mutex in two ways

1. Static Method
2. Dynamic Method

#### Static Method

This method will be useful while using global Mutex. This macro is defined below.

**`DEFINE_MUTEX(name);`**

This call *defines* and *initializes* a mutex. Refer to **`Linux/include/linux/mutex.h`**

#### Dynamic Method

This method will be useful  for per-object mutexes when the mutex is just a  field in a heap-allocated object. This macro is defined below.

**`mutex_init(struct mutex \*lock);`**

**Argument:**

**`struct mutex \*lock`** – the mutex to be initialized.

This call *initializes* already allocated mutex. Initialize the mutex to the unlocked state.

It is not allowed to initialize an already locked mutex.

##### Example

```c
struct mutex etx_mutex; 
mutex_init(&etx_mutex);
```



### Mutex Lock

Once a mutex has been initialized, it can be locked by any one of them explained below.

#### mutex_lock

This is used to lock/acquire the mutex exclusively for the current task. If the mutex is not available, the current task will sleep until it acquires the Mutex.

The mutex must, later on, released by the same task that acquired it.  Recursive locking is not allowed. The task may not exit without first  unlocking the mutex. Also, kernel memory where the mutex resides must  not be freed with the mutex still locked. The mutex must first be  initialized (or statically defined) before it can be locked. **`memset`**-ing the mutex to 0 is not allowed.

**`void mutex_lock(struct mutex \*lock);`**

**Argument:**

**`struct mutex \*lock`** – the mutex to be acquired

#### mutex_lock_interruptible

Locks the mutex like `mutex_lock`, and returns 0 if the mutex has been acquired or sleep until the mutex  becomes available. If a signal arrives while waiting for the lock then  this function returns `-EINTR`.

**`int mutex_lock_interruptible(struct mutex \*lock);`**

**Argument:**

**`struct mutex \*lock`** – the mutex to be acquired

#### mutex_trylock

This will try to acquire the mutex, without waiting (will attempt to obtain  the lock, but will not sleep). Returns 1 if the mutex has been acquired  successfully, and 0 on contention.

**`int mutex_trylock(struct mutex \*lock);`**

**Argument:**

**`struct mutex \*lock`** – the mutex to be acquired

This function must not be used in an interrupt context. The mutex must be released by the same task that acquired it.

### Mutex Unlock

This is used to unlock/release a mutex that has been locked by a task previously.

This function must not be used in an interrupt context. Unlocking of a not locked mutex is not allowed.

**`void mutex_unlock(struct mutex \*lock);`**

**Argument:**

**`struct mutex \*lock`** – the mutex to be released

### Mutex Status

This function is used to check whether mutex has been locked or not.

**`int mutex_is_locked(struct mutex \*lock);`**

**Argument:**

**`struct mutex \*lock`** – the mutex to check the status.

**Returns** 1 if the mutex is locked, 0 if unlocked.

