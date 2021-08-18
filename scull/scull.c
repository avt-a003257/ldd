#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/types.h> // dev_t
#include <linux/cdev.h> //cdev_init

static int scull_major, scull_minor = 0, scull_nr = 1;
static dev_t devno;
static struct file_operations fops;
static struct cdev *mycdev = NULL;

module_param(scull_major, int, S_IRUSR | S_IWUSR);
MODULE_PARM_DESC(scull_major, "major number of the device");

static int __init scull_init(void)
{
	int retval;

	printk("%s\n", __func__);

	if (scull_major)
	{ 
		devno = MKDEV(scull_major, scull_minor);
		retval = register_chrdev_region(devno, scull_nr, "scull");
	}
	else
	{
		retval = alloc_chrdev_region(&devno, scull_minor, scull_nr, "scull");
	}
	
	if (retval < 0)
	{
		printk("scull: can't get major %d\n", scull_major);
		return retval;
	}
	else
	{
		scull_major = MAJOR(devno);
		printk("device num: %d:%d - %d devices\n", scull_major, scull_minor, scull_nr);
	}

	mycdev = cdev_alloc();
	if (!mycdev)
	{
		unregister_chrdev_region(devno, scull_nr);
		printk("fail cdev_alloc\n");
		return -1;
	}

	cdev_init(mycdev, &fops);
	mycdev->owner = THIS_MODULE;
	cdev_add(mycdev, MKDEV(scull_major, 0), 1);

	return 0;
}

module_init(scull_init);

static void __exit scull_exit(void)
{
	printk("%s\n", __func__);

	cdev_del(mycdev);
	unregister_chrdev_region(devno, scull_nr);
}

module_exit(scull_exit);

MODULE_LICENSE("GPL");

