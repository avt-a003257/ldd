#include <linux/kernel.h>
#include <linux/module.h>

int myint = 0;
//module_param(myint, int, S_IRWXU | S_IRWXG);
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myint, "debug flag");

#ifdef __TEST__

#include <linux/init.h>
static int __init hello_2_init(void)
{
	printk("%s\n", __func__);
	if (myint) printk("myint=%d\n", myint);
	return 0;
}

module_init(hello_2_init);

static void __exit hello_2_exit(void)
{
	printk("%s\n", __func__);
}

module_exit(hello_2_exit);

#else

int init_module(void)
{
	printk("%s\n", __func__);
	return 0;
}

void cleanup_module(void)
{
	printk("%s\n", __func__);
}

#endif

MODULE_LICENSE("GPL");
MODULE_AUTHOR("A003257");
MODULE_DESCRIPTION("Test module");
MODULE_SUPPORTED_DEVICE("none");

