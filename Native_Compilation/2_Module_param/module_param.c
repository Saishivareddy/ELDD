#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy");
MODULE_DESCRIPTION("Module to a demo of Module parameters");


static char* charvar = "CDAC";

module_param(charvar, charp, S_IRUGO);

static int param_init(void)
{
    printk("\nThe charvar is %s\n", charvar);
    return 0;
}

static void param_exit(void)
{
    printk("\nGoodbye, World\n");
}

module_init(param_init);
module_exit(param_exit);
