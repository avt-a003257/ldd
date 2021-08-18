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

static loff_t scull_llseek(struct file *filp, loff_t loff, int pos)
{
	printk("%s\n", __func__);
	return 0;
}

static ssize_t scull_read(struct file *filp, char __user *mem, size_t sz, loff_t *loff)
{
	printk("%s\n", __func__);
	return 0; 
}

static ssize_t scull_write(struct file *filp, const char __user *mem, size_t sz, loff_t *loff)
{
	printk("%s\n", __func__);
	return 0; 
}

//int scull_ioctl(struct inode *, struct file *filp, unsigned int, unsigned long);
static long scull_unlocked_ioctl(struct file *filp, unsigned int x, unsigned long y)
{
	printk("%s\n", __func__);
	return 0; 
}

static int scull_open(struct inode *inode, struct file *filp)
{
	printk("%s\n", __func__);
	return 0; 
}

static int scull_release(struct inode *inode, struct file *filp)
{
	printk("%s\n", __func__);
	return 0; 
}

struct file_operations scull_fops = 
{
	.owner	= THIS_MODULE,
	.llseek	= scull_llseek,
	.read	= scull_read,
	.write	= scull_write,
	.unlocked_ioctl	= scull_unlocked_ioctl,
	.open	= scull_open,
	.release= scull_release,
};


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

