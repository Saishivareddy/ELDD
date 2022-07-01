#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/spinlock.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to a Demo of Spinlocks");

dev_t dev = 0;
static struct cdev *my_cdev;
spinlock_t my_spinlock;
unsigned int op_result;

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
	pr_info("\n In Read Function\n");
	int result;
	result = copy_to_user((char *)buf, &op_result, sizeof(op_result));
	if(result == 0)
	{
		pr_info("\n In read section the result is : %d\n", op_result);
		spin_unlock(&my_spinlock);
		return len;
	}
	else
	{
		pr_info("\n Error in reading data from kernel\n");
		return -1;
	}
}

static ssize_t my_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	spin_lock(&my_spinlock);
	pr_info("\n In Write Function\n");
	int kbuff[2];
	int result, num1, num2;
	result = copy_from_user((char *)kbuff, (char *)buf, sizeof(buf));
	if(result == 0)
	{
		num1 = kbuff[0];
		num2 = kbuff[1];
		op_result = num1 + num2;
		pr_info("\n Result in Write Section of driver : %d\n", op_result);
		return len;
	}
	else
	{
		pr_info("\n Error in writing data from user to kernel\n");
	}

	return len;
}

static int __init char_driver_init(void)
{
	if(alloc_chrdev_region(&dev, 0, 3, "Mydev") < 0)
	{
		pr_err("\n Error in allocating Major Number \n");
		return -1;
	}
	pr_info("\n Major = %d and Minor = %d\n", MAJOR(dev), MINOR(dev));

	
	// cdev_init(&my_cdev, &fops);	
	
	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;

	if(cdev_add(my_cdev, dev, 3) < 0)
	{
		pr_err("\n Cannot add device \n");
	}
	printk("\n Driver Inserted\n");

	spin_lock_init(&my_spinlock);
	return 0;
}

static void __exit char_driver_exit(void)
{
	cdev_del(my_cdev);
	unregister_chrdev_region(dev, 3);
	printk("\n Driver removed \n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);

