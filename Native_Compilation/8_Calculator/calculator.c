#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to create a Simple Device Driver(File Operations)");

dev_t dev = 0;
static struct cdev my_cdev;

static int __init char_driver_init(void);
static void __exit char_driver_exit(void);

static int my_open(struct inode *inode, struct file *file);
static int my_release(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t my_write(struct file *filp, const char *buf, size_t len, loff_t *off);

static struct file_operations fops = 
{
	.owner	 = THIS_MODULE,
	.read	 = my_read,
	.write	 = my_write,
	.open	 = my_open,
	.release = my_release,
};

static int my_open(struct inode *inode, struct file *file)
{
	pr_info("\n Driver Opened \n");
	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	pr_info("\n Driver Closed \n");
	return 0;
}

static ssize_t my_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	pr_info("\n Driver Read \n");
	return 0;
}

static ssize_t my_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	pr_info("\n Driver Write \n");
	return len;
}

static int __init char_driver_init(void)
{
	if(alloc_chrdev_region(&dev, 0, 4, "Mydev") < 0)
	{
		pr_err("\n Error in allocating Major Number \n");
		return -1;
	}
	pr_info("\n Major = %d and Minor = %d\n", MAJOR(dev), MINOR(dev));

	cdev_init(&my_cdev, &fops);	
	if(cdev_add(&my_cdev, dev, 4) < 0)
	{
		pr_err("\n Cannot add device \n");
	}
	printk("\n Driver Inserted\n");
	return 0;
}

static void __exit char_driver_exit(void)
{
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev, 4);
	printk("\n Driver removed \n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);
