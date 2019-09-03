/*
 * Simple character driver showing:- 
 * a) Registering/unregistering
 * b) simple file operations - open, close, ioctl
 */

#include<linux/module.h>		/* For all module related macros and APIs*/
#include<linux/cdev.h>			/* For supporting character devices, APIs- cdev_init(),cdev_add(), cdev_del()*/
#include<linux/fs.h>			/* For supporting characer devies, APIs- registering/deregistering*/

/* Define major number*/
#define MY_MAJOR_NUM 305

/*
 * Kernel uses the structure to represent character devices internally
 * struct cdev {
 *       struct kobject kobj;
 *       struct module *owner;
 *       const struct file_operations *ops;
 *       struct list_head list;
 *       dev_t dev;
 *       unsigned int count;
 * };
 */
static struct cdev my_cdev;

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

static int __init simple_char_init(void)
{
    int ret;
    dev_t dev = MKDEV(MY_MAJOR_NUM,0);		/* Used to keep device identifiers, gives first identifier*/
    pr_info("Simple char driver init... \n");
    
    /*
     * Allocate device numbers
     * register_chrdev_region(dev_t first, unsigned int count, chr *name);
     */
    ret = register_chrdev_region(dev, 1, "my_char_dev");
    if(ret < 0)
    {
        pr_info("Unable to give major number %d\n", MY_MAJOR_NUM);
        return ret;
    }
    /* void cdev_init(struct cdev *, const struct file_operations *);*/
    cdev_init(&my_cdev, &my_cdev_fops);
    
    /* int cdev_add(struct cdev *, dev_t, unsigned);
     * Tells kernel about device is set up.
     * These two APIs are called as many times as allocated character device identifiers
     */
    ret = cdev_add(&my_cdev, dev, 1);
    if(ret < 0)
    {
        unregister_chrdev_region(dev, 1);
	pr_info("Unable to add cdev \n");
	return ret;
    }
    return 0;
}

static void __exit simple_char_exit(void)
{
    pr_info("SImple char driver exit...");
    cdev_del(&my_cdev);
    unregister_chrdev_region(MKDEV(MY_MAJOR_NUM, 0), 1);
}

module_init(simple_char_init);
module_exit(simple_char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Garima Kaushik <garimakaushik134@gmail.com>");
MODULE_DESCRIPTION("Simple Character Driver");
