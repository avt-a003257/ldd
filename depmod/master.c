#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include "slave.h"

static int __init master_init(void)
{
	printk("%s\n", __func__);
	slave_test();
	return 0;
}

module_init(master_init);

static void __exit master_exit(void)
{
	printk("%s\n", __func__);
}

module_exit(master_exit);

MODULE_LICENSE("GPL");

