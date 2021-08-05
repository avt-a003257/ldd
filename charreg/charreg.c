#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/types.h> // dev_t
#include <linux/cdev.h> //cdev_init

static int count = 1;
static int major = 250;
static dev_t devno;
static struct file_operations fops;
static struct cdev mycdev;

static int __init charreg_init(void)
{
	printk("%s\n", __func__);

#if 0
	if (register_chrdev(major, "charreg", &fops) < 0)
	{
		printk("register_chrdev failed\n");
		return -1;
	}
	
	printk("%d,%d\n", major, 0);
#endif
#if 0 
	devno = MKDEV(major, 0);
	if (register_chrdev_region(devno, count, "charreg") < 0)
	{
		printk("register_chrdev_region failed\n");
		return -1;
	}

	printk("%d,%d\n", MAJOR(devno), MINOR(devno));
#endif
#if 1
	if (alloc_chrdev_region(&devno, 0, count, "charreg") < 0)
	{
		printk("alloc_chrdev_region failed\n");
		return -1;
	}
	
	major = MAJOR(devno);
	printk("%d,%d\n", major, MINOR(devno));
#endif

	cdev_init(&mycdev, &fops);
	mycdev.owner = THIS_MODULE;
	cdev_add(&mycdev, MKDEV(major, 0), 1);

	return 0;
}

module_init(charreg_init);

static void __exit charreg_exit(void)
{
	printk("%s\n", __func__);

	cdev_del(&mycdev);
#if 0	
	unregister_chrdev(major, "charreg");
#endif
#if 1
	unregister_chrdev_region(devno, count);
#endif
}

module_exit(charreg_exit);

MODULE_LICENSE("GPL");

