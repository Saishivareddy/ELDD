#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

dev_t dev = 0;
static struct cdev *my_cdev;

static int	__init calculator_init(void);
static void	__exit calculator_exit(void);

static long  my_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

static struct file_operations fops =
{
	.unlocked_ioctl = my_ioctl,
};

static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case ADD :
			printk(KERN_INFO "This is Add Function\n");
			copy_to_user(
				    )
	}
}

static int __init calculator_init(void)
{
	alloc_chrdev_region(&dev, 0, 1, "Mydriver");
	printk(KERN_INFO "Major Number = %d\nMinor Number = %d\n", MAJOR(dev), MINOR(dev));
	my_cdev = cdev_alloc();
	my_cdev -> ops = &fops;
	cdev_add(my_cdev, dev, 1);
	printk(KERN_INFO "Driver Inserted Successfully...!\n");
	return 0;
}

static void __exit calculator_exit(void)
{
	cdev_del(my_cdev);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "Driver Removed Successfully...!\n");
}


module_init(calculator_init);
module_exit(calculator_exit);



