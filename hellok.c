#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>

#define MAJOR 100
#define DEVICE_NAME "Oracle"

// example of using parameters that are passed to the module when
// it is loaded (with a default value)
// see http://www.tldp.org/LDP/lkmpg/2.6/html/x323.html
int magic = 42;
module_param(magic, int, 0644); //name, type, permissions
// if the permissions are set to 0, the parameter cannot be changed,
// otherwise you can tinker with it via /sys/


// undefined functions are set to NULL
struct file_operations ocacle_operations = {
	.owner = THIS_MODULE,
	.read  = oracle_read,
};

#define BUFF_SIZE 100
static char response_buffer[BUFF_SIZE];

ssize_t oracle_read(struct file *pfile, char __user *buffer, size_t length, loff_t *offset)
{
	printk(KERN_ALERT "Attempting to read, length %d in %s\n", length, __FUNCTION__);
	snprintf(response_buffer, BUFF_SIZE, "%d", magic);
	printk(KERN_ALERT "prepared answer\n");
	copy_to_user(buffer, response_buffer, sizeof(response_buffer))
	printk(KERN_ALERT "copied answer to user-space buffer\n");
	return sizeof(response_buffer);
}

static int my_init(void)
{
	printk(KERN_ALERT "Loaded hellok in %s\n", __FUNCTION__);
	printk(KERN_ALERT "Magic number = %d\n", magic);

	register_chrdev(MAJOR, DEVICE_NAME, &ocacle_operations);
	return 0;
}
 
static void my_exit(void)
{
	printk("Unregistering the device\n");
	unregister_chrdev(MAJOR, DEVICE_NAME);
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