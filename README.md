# am335x_device_drivers
ARM device drivers from scratch for beginners in device drivers
->The drivers are compatible with kernel version 4.9.98-dirty. All drivers are tested on am335x custom hardware.

Procedure to follow (General procedure, not limited to am335x only):-
1) Download the kernel source for which you want to build drivers
2) Compile the source using make (respective DEFCONFIG and make) in order to generate zImage and required *.dtb
(as per requirement of your board)
3) By using make menuconfig enable/disable your requirements, and recompile the source
4) Prepare the bootable sd-card and test if working for required configuration on boot 
5) Now set environment for driver compilation in current terminal using script env.sh(modify as per your requirement) ,then after writing c file of your driver, don't forget to replace your kernel directory(KERN_DIR) with mine 
and then use make.
