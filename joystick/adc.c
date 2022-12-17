#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <math.h>



int main(int argc, char **argv)
{
    int buff;
    char tmp;
    char prev = 'r';

    int dev = open("/dev/adc_driver", O_RDWR);
    if (dev == -1)
    {
        printf("Opening was not possible!\n");
        return -1;
    }
    printf("Opening was successfull!\n");

    while (1)
    {
        read(dev, &buff, 1);
        prev = tmp;
        tmp = buff;
        printf("%d\n", buff);
    }

    close(dev);
    return 0;
}

int adc_read()
{
    int buff;


    int dev = open("/dev/adc_driver", O_RDWR);
    if (dev == -1)
    {
        printf("Opening was not possible!\n");
        return -1;
    }

    for(int i = 0; i < 2; i++)
    {
        buff = 0;
        read(dev, &buff, 1);
    }
    
    close(dev);

    return buff;
}