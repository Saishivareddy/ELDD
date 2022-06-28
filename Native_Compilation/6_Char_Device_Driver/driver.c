#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/device.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to create a Character Device Driver");

dev_t dev = 0;
static struct class *dev_class;
static struct cdev my_cdev;

static int __init char_driver_init(void);
static void __exit char_driver_exit(void);

static int my_open(struct inode *inode, struct file *file);
static int my_release(struct inode *inode, struct file *file);
static ssize_t my_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t my_write(struct file *filp, const char __user *buf, size_t len, loff_t *off);

static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_release,
};

static int my_open(struct inode *inode, struct file *file)
{
	printk("\n Driver opened \n");
	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	printk("\n Driver Closed \n");
	return 0;
}

static ssize_t my_read(struct file *filp, char __user *buf, size_t len, loff_t *off)
{
	printk("\n Driver Read \n");
	return 0;
}

static ssize_t my_write(struct file *filp, const char __user *buf, size_t len, loff_t *off)
{
	printk("\n Driver Write \n");
	return 0;
}

static int __init char_driver_init(void)
{
	if(alloc_chrdev_region(&dev, 0, 1, "Mydev") < 0)
	{
		printk("\n Error in allocating Major Number \n");
		return -1;
	}
	printk("\n Major = %d and Minor = %d\n", MAJOR(dev), MINOR(dev));

	cdev_init(&my_cdev, &fops);	
	if(cdev_add(&my_cdev, dev, 1) < 0)
	{
		printk("\n Cannot add device \n");
		goto r_class;
	}
	if((dev_class = class_create(THIS_MODULE, "my_class"))== NULL)
	{
		printk("\n Cannot create device class\n");
		goto r_class;
	}
	if(device_create(dev_class, NULL, dev, NULL, "My_device") == NULL)
	{
		printk("\n Cannot create Device \n");
		goto r_device;
	}
	printk("\n Driver Inserted\n");
	return 0;

r_class :
	unregister_chrdev_region(dev, 1);
	return -1;
r_device :
	class_destroy(dev_class);
	return -1;	
}

static void __exit char_driver_exit(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	cdev_del(&my_cdev);
	unregister_chrdev_region(dev, 1);
	printk("\n Driver removed \n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);

