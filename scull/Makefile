# Makefile
#
# make clean; make
#

ARCH := arm 
CROSS_COMPILE := arm-himix200-linux-

ifneq ($(KERNELRELEASE),)
	obj-m := scull.o
else
	KERNELDIR ?= /home/a003257/er330/src/osdrv/opensource/kernel/linux-4.9.y-smp
#	KERNELDIR ?= /lib/modules/$(shell uname -r)/build

default:
	ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(MAKE) -C $(KERNELDIR) M=$$PWD 

clean:
	ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) $(MAKE) -C $(KERNELDIR) M=$$PWD clean

endif

EXTRA_CFLAGS += 
