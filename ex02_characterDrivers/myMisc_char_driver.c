/*
 * Character driver showing misc framework for automatically assigning major number:- 
 * a) Registering/unregistering
 * b) simple file operations - open, close, ioctl
 */

#include<linux/module.h>		/* For all module related macros and APIs*/
#include<linux/miscdevice.h>		/* For struct miscdev, APIs- misc_register(), misc_deregister()*/
#include<linux/fs.h>			/* For supporting characer devies, APIs- registering/deregistering*/

/*
 * Kernel uses the structure to represent character devices internally
 * struct miscdevice {
 *       int minor;
 *       const char *name;
 *       const struct file_operations *ops;
 *       struct list_head list;
 *       struct device *parent;
 *       struct device *this_device;
 *	 umode_t mode;
 * };
 */

static int my_dev_open(struct inode *inode, struct file *file)
{
    pr_info("my_dev_open() is called \n");
    return 0;
}

static int my_dev_close(struct inode *inode, struct file *file)
{
    pr_info("my_dev_close() is called \n");
    return 0;
}

static long my_dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    pr_info("my_dev_ioctl() is called. cmd= %d, arg= %ld\n",cmd, arg);
    return 0;
}

/* 
 * This structure defines the pointers to opening, closing, reading from, 
 * writing to, close device etc
 * static const struct file_operations __fops = {                        
 *       .owner   = THIS_MODULE,                                         
 *       .open    = __fops ## _open,                                     
 *       .release = simple_attr_release,                                 
 *       .read    = simple_attr_read,                                    
 *       .write   = simple_attr_write,                                   
 *       .llseek  = generic_file_llseek,                                 
 * }
*/
static const struct file_operations my_cdev_fops = {
    .owner = THIS_MODULE,
    .open = my_dev_open,
    .release = my_dev_close,
    .unlocked_ioctl = my_dev_ioctl
};

static struct miscdevice myChar_miscdevice = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "mydev",
    .fops = &my_cdev_fops
};

static int __init myMisc_char_init(void)
{
    int ret;
    pr_info("Misc char driver init... \n");
    
    ret = misc_register(&myChar_miscdevice);
    if(ret != 0)
    {
        pr_info("Unable to register misc device\n");
        return ret;
    }
    pr_info("mydev: got minor %d\n",myChar_miscdevice.minor);
    return 0;
}

static void __exit myMisc_char_exit(void)
{
    pr_info("Misc char driver exit...");
    misc_deregister(&myChar_miscdevice);
}

module_init(myMisc_char_init);
module_exit(myMisc_char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Garima Kaushik <garimakaushik134@gmail.com>");
MODULE_DESCRIPTION("Simple Character Driver using misc framework");
