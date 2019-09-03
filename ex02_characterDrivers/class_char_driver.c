/*
 * Class character driver, which automatically assigns Major number
 * by using devtmpfs filesystem
 */

#include<linux/module.h>		/* For all module realted macros and APIs*/
#include<linux/cdev.h>			/* For character driver structure cdev and 
					 * supported APIs-cdev_init(),cdev_add(),cdev_del() 
					 */
#include<linux/fs.h>			/* For file_operations structure and character driver supported APIs
					 * such as register/unregister
					 */
#include<linux/device.h>		/* For APIs to create class and device files- class_create(),class_destroy(),
					 * device_create() and device_destroy()
					 */

/* For purpose of creation of device at /sys/class/my_cdev_class/my_cdev*/
#define DEVICE_NAME "my_cdev"
#define CLASS_NAME "my_cdev_class"

static struct class* myCdevClass;
static struct cdev my_dev;
dev_t dev;

static int my_dev_open(struct inode *inode, struct file *file)
{
    pr_info("my_dev_open() called.\n");
    return 0;
}

static int my_dev_close(struct inode *inode, struct file *file)
{
    pr_info("my_dev_close() called.\n");
    return 0;
}

static long my_dev_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    pr_info("my_dev_ioctl() called.cmd = %d, arg = %ld\n", cmd, arg);
    return 0;
}

/* Declare file operations structure */
static const struct file_operations my_cdev_fops= {
	.owner 		= THIS_MODULE,
	.open 		= my_dev_open,
	.release 	= my_dev_close,
	.unlocked_ioctl = my_dev_ioctl
};

static int __init myClass_char_driver_init(void)
{
    int ret;
    dev_t dev_no;
    int Major;
    struct device* myCdevDevice;

    pr_info("Class Char Driver Init...\n");
    
    /* int alloc_chrdev_region(dev_t* dev, unsigned baseminor, unsigned count, const char* name)
     * dev - output parameter for first assigned number
     * baseminor - first of requested range of minor numbers
     * count - number of minors required
     * name - name of associated device or driver
     */    
    ret = alloc_chrdev_region(&dev_no, 0, 1, DEVICE_NAME);
    if(ret < 0)
    {
        pr_info("Unable to allocate major number. \n");
        return ret;
    }
    Major = MAJOR(dev_no);
    dev = MKDEV(Major,0);
    pr_info("Major number allocated correstly as %d.\n", Major);
    
    cdev_init(&my_dev, &my_cdev_fops);
    ret = cdev_add(&my_dev, dev, 1);
    if(ret < 0)
    {
        unregister_chrdev_region(dev,1);
        pr_info("Unable to add cdev. \n");
        return ret;
    }

    /* Register the device class */
    myCdevClass = class_create(THIS_MODULE, CLASS_NAME);
    if(IS_ERR(myCdevClass))
    {
        unregister_chrdev_region(dev, 1);
        cdev_del(&my_dev);
        pr_info(" Device class registration faileed. \n");
        return PTR_ERR(myCdevClass);
    }
    pr_info("Device class registration successful \n");
    /* Create device node in device class */
    myCdevDevice = device_create(myCdevClass, NULL, dev, NULL, DEVICE_NAME);
    if(IS_ERR(myCdevDevice))
    {
        class_destroy(myCdevClass);
        unregister_chrdev_region(dev, 1);
        cdev_del(&my_dev);
        pr_info(" Device node creation faileed. \n");
        return PTR_ERR(myCdevDevice);
    }
    pr_info("Device created correctly. \n");

    return 0;
}

static void __exit myClass_char_driver_exit(void)
{
    device_destroy(myCdevClass, dev);
    class_destroy(myCdevClass);
    cdev_del(&my_dev);
    unregister_chrdev_region(dev, 1);
    pr_info("Class Char Driver Exit...\n");
}

module_init(myClass_char_driver_init);
module_exit(myClass_char_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Garima Kaushik <garimakaushik134@gmail.com>");
MODULE_DESCRIPTION("This character driver allocates major number automatically using devtmpfs framework");
