#include <linux/init.h>
#include <linux/module.h>
 
static int my_init(void)
{
	printk("Loaded hellok\n");
	return 0;
}
 
static void my_exit(void)
{
	printk("Unloaded hellok\n");
	return;
}
 
module_init(my_init);
module_exit(my_exit);


// otherwise it complains that
// `module license 'unspecified' taints kernel`
MODULE_LICENSE("GPL");