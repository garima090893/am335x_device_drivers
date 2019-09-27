/* Application code to test character driver */

#include<stdio.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<unistd.h>

int main(void)
{
    /* First run "mknod /dev/mydev c 305 0" to create /dev/mydev */
    int my_dev = open("/dev/my_led_driver", 0);
    if(my_dev < 0)
    {
        perror("Fail to open device: /dev/my_led_driver");   
    }
    else
    {
        ioctl(my_dev, 150, 110);	/* cmd = 100, arg = 110*/
	sleep(4);
        ioctl(my_dev, 151, 110);	/* cmd = 100, arg = 110*/
        close(my_dev);
    }
    return 0;
}
