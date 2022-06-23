#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to Create a Device file Manually");

dev_t dev = 0;

static int __init devfile_init(void)
{
	if(alloc_chrdev_region(&dev, 0, 1,  "MycharDriver")<0)
	{
		printk(KERN_ALERT"\n Cannot allocate Major Number\n");
	}
	else
	{
		printk(KERN_INFO"\n Major = %d and Minor = %d\n", MAJOR(dev), MINOR(dev));
		printk(KERN_ALERT"\n Inserted Succesfully\n");
	}
	return 0;
}

static void __exit devfile_exit(void)
{
	printk(KERN_ALERT "\nremoved Successfully\n");
}
module_init(devfile_init);
module_exit(devfile_exit);

