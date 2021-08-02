#include <linux/kernel.h>
#include <linux/module.h>

#if 0
int init_module(void)
{
	printk("%s\n", __func__);
	return 0;
}

#else

#include <linux/init.h>
static int __init hello_init(void)
{
	printk("%s\n", __func__);
	return 0;
}

module_init(hello_init);

#endif

