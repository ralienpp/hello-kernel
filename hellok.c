#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

// example of using parameters that are passed to the module when
// it is loaded (with a default value)
// see http://www.tldp.org/LDP/lkmpg/2.6/html/x323.html
int magic = 42;
module_param(magic, int, 0); //name, type, permissions
 
static int my_init(void)
{
	printk(KERN_ALERT "Loaded hellok in %s\n", __FUNCTION__);
	printk(KERN_ALERT "Magic number = %d\n", magic);
	return 0;
}
 
static void my_exit(void)
{
	printk("Unloaded hellok\n");
	return;
}


// maybe for later
// int exported_function(void)
// {
// 	printk("Called dummy function\n")
// 	return 0;
// }
// EXPORT_SYMBOL(exported_function);
 
module_init(my_init); // still loadable, even if not implemented
module_exit(my_exit); // if not implemented, the module won't be unloadable


// otherwise it complains that
// `module license 'unspecified' taints kernel`
MODULE_LICENSE("GPL");