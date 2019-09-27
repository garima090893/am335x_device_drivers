#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/ioctl.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <asm/irq.h>

/* Macros */
#define SW_GPIO_0_20		20
#define LED_GPIO_2_18       	82

static int myDeviceId = 0, irqCounter = 0;

static int led_init(int gpio_number)
{
    int ret;
    pr_info("led_init() called...\n");
    ret = gpio_request(gpio_number, "sled");
    if(ret < 0)
        return ret;
    ret = gpio_direction_output(gpio_number, 1);
        return ret;
}

void led_on(int gpio_number)
{
    gpio_set_value(gpio_number, 1);
}

void led_off(int gpio_number)
{
    gpio_set_value(gpio_number, 0);
}

void led_deinit(int gpio_number)
{
    gpio_free(gpio_number);
}

void led_toggle(void)
{
    int led_status = 0;
    if(led_status==(!led_status)) {led_on(LED_GPIO_2_18);}
    else {led_off(LED_GPIO_2_18);}
}

static irqreturn_t my_interrupt_handler(int irq, void *device_id)
{
    pr_info("my_interrupt_handler() called...\n");
    irqCounter++;
    led_toggle();
    pr_info("irqCounter = %d...\n", irqCounter);
    return IRQ_HANDLED;
}

static int __init my_switch_init(void)
{
    pr_info("my_switch_init() called...\n");
    gpio_request(SW_GPIO_0_20, "switch");
    led_init(LED_GPIO_2_18);
    gpio_direction_input(SW_GPIO_0_20);
    if(request_irq(gpio_to_irq(SW_GPIO_0_20),my_interrupt_handler, IRQ_TYPE_EDGE_BOTH, "my_interrupt", &myDeviceId))
        return -1;
    return 0;
}

static void __exit my_switch_exit(void)
{
    pr_info("my_switch_exit() called...\n");
    free_irq(gpio_to_irq(SW_GPIO_0_20), &myDeviceId);
    led_deinit(LED_GPIO_2_18);
}

module_init(my_switch_init);
module_exit(my_switch_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Garima Kaushik <garimakaushik134@gmail.com>");
MODULE_DESCRIPTION("Switch interrupt to toggle LED");

