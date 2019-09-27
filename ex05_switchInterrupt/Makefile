obj-m += simple_switch_interrupts.o 

# KERNEL_DIR ?= $(HOME)/personalSpace/linux-am335x/linux-mainline
KERNEL_DIR ?= $(HOME)/workspace/Altair/linux-am335x/linux-mainline

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
	scp *.ko ioctl_test root@192.168.1.11:/home/root/garima_drivers/
