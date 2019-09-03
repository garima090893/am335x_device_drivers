/* Application code to test character driver */

#include<stdio.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<unistd.h>

int main(void)
{
    /* First run "mknod /dev/mydev c 305 0" to create /dev/mydev */
    int my_dev = open("/dev/mydev", 0);
    if(my_dev < 0)
    {
        perror("Fail to open device: /dev/mydev");   
    }
    else
    {
        ioctl(my_dev, 100, 110);	/* cmd = 100, arg = 110*/
        close(my_dev);
    }
    return 0;
}
