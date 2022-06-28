#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define mem_size 1024

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to Create Simple Device Driver");

dev_t dev = 0;
static struct cdev my_dev;
uint8_t *kernel_buffer;


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
	if(copy_to_user(buf, kernel_buffer, mem_size) )
	{
		pr_err("\n Error in Reading\n");
		return -1;
	}
	pr_info("\n Driver Read Done!\n");
	return mem_size;
}

static ssize_t my_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	if(copy_from_user(kernel_buffer, buf, len) )
	{
		pr_err("\n Error in writing\n");
		return -1;
	}
	pr_info("\n Driver Write Done!\n");
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
	if(cdev_add(&my_dev, dev, 1) < 0)
	{
		pr_err("\n Error in adding device \n");
		return -1;
	}
	if((kernel_buffer = kmalloc(mem_size, GFP_KERNEL) )== 0)
	{
		pr_err("\n Error in allocating memory in kernel\n");
		return -1;
	}
	strcpy(kernel_buffer, "Hello World");
	pr_info("\n Driver Inserted Successfully\n");
	return 0;
}

static void __exit char_driver_exit(void)
{
	kfree(kernel_buffer);
	cdev_del(&my_dev);
	unregister_chrdev_region(dev, 1);
	pr_info("\n Driver Removed Successfully\n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);

