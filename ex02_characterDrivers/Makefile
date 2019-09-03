obj-m += simple_char_driver.o
obj-m += class_char_driver.o
obj-m += myMisc_char_driver.o

KERNEL_DIR ?= $(HOME)/personalSpace/linux-am335x/linux-mainline

all:
	make -C $(KERNEL_DIR) \
                ARCH=arm CROSS_COMPILE=arm-cortexa8-linux-gnueabihf- \
                SUBDIRS=$(PWD) modules

app:
	arm-cortexa8-linux-gnueabihf-gcc ioctl_test.c -o  ioctl_test

clean:
	make -C $(KERNEL_DIR) \
                ARCH=arm CROSS_COMPILE=arm-cortexa8-linux-gnueabihf- \
                SUBDIRS=$(PWD) clean

deploy:
	scp ioctl_test *.ko root@192.168.1.11:/home/root/garima_drivers/
