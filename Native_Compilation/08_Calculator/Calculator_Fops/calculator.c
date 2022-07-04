#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

static int result;


dev_t dev = 0;
static struct cdev *my_cdev;

static int __init   calculator_init(void);
static void __exit  calculator_exit(void);

static int      char_open(struct inode *inode, struct file *file);
static int      char_release(struct inode *inode, struct file *file);
static ssize_t  char_read(struct file *file, char __user *buff, size_t len, loff_t *off);
static ssize_t  char_write(struct file *file, const char __user *buff, size_t len, loff_t *off);

static struct file_operations fops=
{
    .owner      =   THIS_MODULE,
    .open       =   char_open,
    .read       =   char_read,
    .write      =   char_write,
    .release    =   char_release,  
};

static int char_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Driver open function called....!\n");
    return 0;
}

static int char_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "Driver Release function Called....!\n");
    return 0;
}

static ssize_t char_read(struct file *file, char __user *buff, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver Read function Called....!\n");
    int ret = copy_to_user((char*)buff, &result, sizeof(result));
    printk(KERN_INFO"Output is %d\n", result);
    return len;
}

static ssize_t char_write(struct file *file, const char __user *buff, size_t len, loff_t *off)
{
    int kbuff[3];
    printk(KERN_INFO "Driver Write function called....!\n");
    int ret = copy_from_user((int *)kbuff, (int *)buff, sizeof(kbuff));
    // printk("%d %d %d", kbuff[0], kbuff[1], kbuff[2]);
    if(kbuff[2] == 1)
    {
        result = kbuff[0] + kbuff[1];
    }
    else if(kbuff[2] == 2)
    {
        result = kbuff[0] - kbuff[1];
    }
    else if(kbuff[2] == 3)
    {
        result = kbuff[0] * kbuff[1];
    }
    else if(kbuff[2] == 4)
    {
        result = kbuff[0] / kbuff[1];
    }
    return len;
}

static int __init calculator_init(void)
{
    alloc_chrdev_region(&dev,0,1,"MyDriver");
    printk(KERN_INFO "Major Number = %d\nMinor Number = %d",MAJOR(dev), MINOR(dev));
    my_cdev = cdev_alloc();
    my_cdev->ops = &fops;
    cdev_add(my_cdev,dev,1);
    printk(KERN_INFO "Driver Inserted Successfully\n");
    return 0;
}

static void __exit calculator_exit(void)
{
    cdev_del(my_cdev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "Driver removed Successfully\n");
}

module_init(calculator_init);
module_exit(calculator_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saishiva Reddy Gatla");
MODULE_DESCRIPTION("Module to perform Calculator Functionality");
