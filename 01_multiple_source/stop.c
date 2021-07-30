#include <linux/kernel.h>
#include <linux/module.h>

#if 0

void cleanup_module(void)
{
	printk("%s\n", __func__);
}

#else

#include <linux/init.h>

static void __exit hello_exit(void)
{
	printk("%s\n", __func__);
}

module_exit(hello_exit);

#endif

