#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to write Major and Minor Numbers using Static Method");

dev_t dev = MKDEV(269,0);

static int __init number_init(void)
{
	register_chrdev_region(dev, 1, "ShivacharDriver");
	printk(KERN_ALERT"\n Major = %d and Minor = %d\n", MAJOR(dev), MINOR(dev));
	printk(KERN_ALERT"\n Inserted Successfully\n");
	return 0;
}

static void __exit number_exit(void)
{
	unregister_chrdev_region(dev,1);
	printk(KERN_ALERT"\n Removed Successfully\n");
}

module_init(number_init);
module_exit(number_exit);

