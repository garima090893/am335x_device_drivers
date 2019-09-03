/* 
 * Simple driver with parameters and lifespan of driver
 */
#include<linux/module.h>
#include<linux/time.h>				/* includes prototype of function do_gettimeofday()*/

static int num = 2;				/* default value of num, if not passed while calling driver*/

/* 
 * struct timeval {
 * 	__kernel_time_t		tv_sec;		(seconds)
 *	__kernel_suseconds_t	tv_usec;	(microseconds)
 */
static struct timeval start_time;		/* stores time when module is loaded*/

/* 
 * module_param(name,type,perm)
 * Here S_IRUGO: eyeryone can read sysfs entry
 */
module_param(num, int, S_IRUGO);		

/*
 * Function just to increase module time for demo
 */
static void dummy_function(void)
{
    int i;
    for(i = 1; i <= num; i++)
	pr_info("Just chilling...!!");
}

static int __init hello_init(void)
{
    do_gettimeofday(&start_time);		/* get time of module loading */
    pr_info("Hello world init\n");		/* pr_info -> KERN_ERR */
    pr_info("num: %d\n", num);
    dummy_function();		
    return 0;
}

static void __exit hello_exit(void)
{
    struct timeval end_time;
    do_gettimeofday(&end_time);			/* get time of module unloading */
    pr_info("Hello world exit\n");
    pr_info("Module lifespan: %ld s\n", end_time.tv_sec - start_time.tv_sec);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Garima Kaushik <garimakaushik134@gmail.com>");
MODULE_DESCRIPTION("Arm simple driver with params and module lifespan");
