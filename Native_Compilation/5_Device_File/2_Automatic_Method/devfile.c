#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to create a Device file Automatically");

dev_t dev = 0;
static struct class *dev_class;

static int __init devfile_init(void)
{
	// Allocating Major Number 
	if(alloc_chrdev_region(&dev, 0, 1, "MycharDriver")<0)
	{
		printk(KERN_ALERT"\nCannot allocate Major number\n");
		return -1;
	}
	printk(KERN_ALERT"\nMajor = %d and Minor = %d\n", MAJOR(dev), MINOR(dev));
	
	if((dev_class = class_create(THIS_MODULE, "Myclass")) == NULL)
	{
		printk(KERN_ALERT"\n Cannot create the struct for Device\n");
		goto r_class;
	}
	
	// Creating Device
	if(device_create(dev_class, NULL, dev, NULL, "MyDevice") == NULL)
	{
		printk(KERN_ALERT"\nCannot create Device\n");
		goto r_device;
	}

	printk(KERN_ALERT"\nInsterted Successfully\n");
	return 0;
r_device:
	class_destroy(dev_class);
r_class	:
	unregister_chrdev_region(dev, 1);
	return -1;
}

static void __exit devfile_exit(void)
{
	device_destroy(dev_class, dev);
	class_destroy(dev_class);
	unregister_chrdev_region(dev, 1);
	printk(KERN_ALERT"\nRemoved Successfully\n");
}
module_init(devfile_init);
module_exit(devfile_exit);

