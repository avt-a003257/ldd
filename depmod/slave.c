#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

void slave_test(void)
{
	printk("%s\n", __func__);
}

EXPORT_SYMBOL(slave_test);

static int __init slave_init(void)
{
	printk("%s\n", __func__);
	return 0;
}

module_init(slave_init);

static void __exit slave_exit(void)
{
	printk("%s\n", __func__);
}

module_exit(slave_exit);

MODULE_LICENSE("GPL");

