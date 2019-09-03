obj-m += hello_world.o
obj-m += hello_world_with_params.o
obj-m += hello_world_with_timing.o

# for rpi KERNEL_DIR ?= $(HOME)/personalSpace/linux
# for rpi CROSS_COMPILER=arm-linux-gnueabihf-
KERNEL_DIR ?= $(HOME)/personalSpace/linux-am335x/linux-mainline

all:
	make -C $(KERNEL_DIR) \
                ARCH=arm CROSS_COMPILE=arm-cortexa8-linux-gnueabihf- \
                SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNEL_DIR) \
                ARCH=arm CROSS_COMPILE=arm-cortexa8-linux-gnueabihf- \
                SUBDIRS=$(PWD) clean

deploy:
	scp *.ko root@192.168.1.11:/home/root/garima_drivers/
