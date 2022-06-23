#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to print Hello World");

static int hello_init(void)
{
    printk(KERN_ALERT "\n Hello, World\n");
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "\n Goodbye, World\n");
}

module_init(hello_init);
module_exit(hello_exit);
