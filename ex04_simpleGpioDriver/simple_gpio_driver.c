/*
 * Simple led gpio driver, to turn on-off an led from user space
 */

/* Header files */
#include<linux/kernel.h>
#include<linux/module.h>		/* For module related APIs and macros*/
#include<linux/fs.h>			/* For character related APIs and structures*/
#include<linux/gpio.h>			/* For accessing gpios*/
#include<linux/uaccess.h>		/* For user space data exchange APIs*/

/* Macros */
#define GPIO_2_18 	82
#define BUFFER_SIZE 	80
#define LED_ON		150
#define LED_OFF 	151

/* Global variables*/
static int major_number;
char lbuff[BUFFER_SIZE];

int led_init(int gpio_num)
{
    int ret;
    ret = gpio_request(gpio_num, "sled");	
    if(ret < 0)
        return ret;
    ret = gpio_direction_output(gpio_num, 1);
    return ret;
}

void led_on(int gpio_num)
{
    pr_info("LED ON...\n");
    gpio_set_value(gpio_num, 1);
}

void led_off(int gpio_num)
{
    pr_info("LED OFF...\n");
    gpio_set_value(gpio_num, 0);
}

static int my_led_open(struct inode *inode, struct file *file)
{
    int ret;
    pr_info("my_led_open() is called...\n");
    ret = led_init(GPIO_2_18);
    return ret;
}

static int my_led_close(struct inode *inode, struct file *file){
    pr_info("my_led_close() is called...\n");
    gpio_free(GPIO_2_18);
    return 0;
}

static ssize_t my_led_read(struct file *file, char __user *kbuff, size_t sz, loff_t *offset)
{
    pr_info("my_led_read() is called ...\n");
    return 0;
}

static ssize_t my_led_write(struct file *file, const char __user *ubuff, size_t sz, loff_t *offset)
{
    pr_info("my_led_write() is called ...\n");
    copy_from_user(lbuff,ubuff,sz);
    if(lbuff[0] == '1') led_on(GPIO_2_18);
    else if(lbuff[0] == '0') led_off(GPIO_2_18);
         else return -1;    
    return 0;
}

static long my_led_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    pr_info("my_led_ioctl() is called with cmd= %d...\n", cmd);
    switch(cmd)
    {
        case LED_ON:
		led_on(GPIO_2_18);
		break;
	case LED_OFF:
		led_off(GPIO_2_18);
		break;
	default:
		pr_info("Wrong cmd passed...\n");
    }
    return 0;
}

static const struct file_operations my_led_fops = {
	.owner		= THIS_MODULE,
	.open		= my_led_open,
	.release	= my_led_close,
	.read		= my_led_read,
	.write		= my_led_write,
	.unlocked_ioctl	= my_led_ioctl 
};

static int __init simple_gpio_init(void)
{
    pr_info("GPIO module loaded...\n");
    major_number = register_chrdev(0, "my_led_driver", &my_led_fops);
    pr_info("Major number of char device(GPIO): %d\n",major_number);
    return 0;
}

static void __exit simple_gpio_exit(void)
{
    pr_info("GPIO module unloading...\n");
    unregister_chrdev(major_number,"my_led_driver");
}

module_init(simple_gpio_init);
module_exit(simple_gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Garima Kaushik <garimakaushik134@gmail.com>");
MODULE_DESCRIPTION("Simple GPIO driver to drive led on expander");
