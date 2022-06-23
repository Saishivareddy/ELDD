#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "header.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to find Average of two Numbers");

static int __init avg_init(void)
{
	int a = 14, b = 12;
	int avg = 0;
	avg = my_add(a,b)/2;
	printk(KERN_ALERT"\n This is Average Module\n");
	printk(KERN_ALERT"\n Average of %d and %d is %d\n", a,b,avg);
	return 0;
}

static void __exit avg_exit(void)
{
	printk(KERN_ALERT"\n Exiting Average\n");
}

module_init(avg_init);
module_exit(avg_exit);

