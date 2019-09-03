/* Simple driver with parameters*/
#include<linux/module.h>

static int num = 2;				/*default value of num, if not passed while calling driver*/

/*module_param(name,type,perm)
 *Here S_IRUGO: eyeryone can read sysfs entry
 */
module_param(num, int, S_IRUGO);		

static int __init hello_init(void)
{
    pr_info("Hello world init\n");		/*pr_info -> KERN_ERR */
    pr_info("num: %d\n", num);		
    return 0;
}

static void __exit hello_exit(void)
{
    pr_info("Hello world exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Garima Kaushik <garimakaushik134@gmail.com>");
MODULE_DESCRIPTION("Arm simple driver with params");
