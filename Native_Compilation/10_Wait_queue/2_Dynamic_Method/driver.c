#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/uaccess.h>
#include <linux/wait.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to a demo of Wait Queue(Dynamic Method)");

unsigned int count = 0;
static struct task_struct *wait_thread;

wait_queue_head_t wait_queue;

dev_t dev = 0;
static struct cdev my_dev;
int wait_queue_flag = 0;

static int __init char_driver_init(void);
static void __exit char_driver_exit(void);

static int my_open(struct inode *inode, struct file *file);
static int my_release(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t my_write(struct file *filp, const char __user *buf, size_t len, loff_t *off);

static struct file_operations fops =
{
	.owner		= THIS_MODULE,
	.read		= my_read,
	.write		= my_write,
	.open		= my_open,
	.release 	= my_release, 
};

static int wait_function(void *unused)
{

        while(1) 
	{
                pr_info("Waiting For Event...\n");
                wait_event_interruptible(wait_queue, wait_queue_flag != 0 );
                if(wait_queue_flag == 2) 
		{
                        pr_info("Event Came From Exit Function\n");
                        return 0;
                }
                pr_info("Event Came From Read Function - %d\n", ++count);
                wait_queue_flag = 0;
        }
        do_exit(0);
        return 0;
}


static int my_open(struct inode *inode, struct file *file)
{
	pr_info("\n Device file Opened\n");
	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	pr_info("\n Device file Closed\n");
	return 0;
}

static ssize_t my_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{

	pr_info("\n Driver Read Function\n");
	wait_queue_flag = 1;
	wake_up_interruptible(&wait_queue);
	return 0;
}

static ssize_t my_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	pr_info("\n Driver Write Function\n");
	return len;
}

static int __init char_driver_init(void)
{
	if(alloc_chrdev_region(&dev, 0, 1, "Mydev") < 0)
	{
		pr_err("\n Error in allocating Major Number\n");
		return -1;
	}
	pr_info("\n Major = %d and Minor = %d\n", MAJOR(dev), MINOR(dev));

	cdev_init(&my_dev, &fops);
	my_dev.owner = THIS_MODULE;
	my_dev.ops   = &fops;

	if(cdev_add(&my_dev, dev, 1) < 0)
	{
		pr_err("\n Error in adding device \n");
		return -1;
	}

	init_waitqueue_head(&wait_queue);

	wait_thread = kthread_create(wait_function, NULL, "WaitThread");
	if(wait_thread)
	{
		pr_info("\n Thread Created Successfully\n");
		wake_up_process(wait_thread);
	}
	else
		pr_info("Thread Creation Failed\n");

	pr_info("\n Driver Inserted Successfully\n");
	return 0;
}

static void __exit char_driver_exit(void)
{
	wait_queue_flag = 2;
	wake_up_interruptible(&wait_queue);
	cdev_del(&my_dev);
	unregister_chrdev_region(dev, 1);
	pr_info("\n Driver Removed Successfully\n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);

