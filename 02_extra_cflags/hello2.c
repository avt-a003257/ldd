#include <linux/kernel.h>
#include <linux/module.h>

#ifdef __TEST__

#include <linux/init.h>
static int __init hello_2_init(void)
{
	printk("%s\n", __func__);
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

