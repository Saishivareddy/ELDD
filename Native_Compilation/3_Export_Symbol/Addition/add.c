#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to add two numbers");

int my_add(int a, int b)
{
	return (a+b);
}

EXPORT_SYMBOL(my_add);

static int __init add_init(void)
{
	printk(KERN_ALERT "\n This is Addition Module\n");
	return 0;
}

static void __exit add_exit(void)
{
	printk(KERN_ALERT"\n Exiting Addition\n");
}

module_init(add_init);
module_exit(add_exit);

