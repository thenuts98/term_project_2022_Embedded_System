#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <math.h>

static struct termios init_setting, new_setting;

//                  0      1     2     3     4     5     6     7    8       9       (is it correct?)
char seg_num[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90};
char seg_dnum[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x58, 0x00, 0x10};

//port(?)
#define D1 0x01
#define D2 0x02
#define D3 0x04
#define D4 0x08


void init_keyboard()
{
    tcgetattr(STDIN_FILENO, &init_setting);
    new_setting = init_setting;
    new_setting.c_lflag &= ~ICANON;
    new_setting.c_lflag &= ~ECHO;
    new_setting.c_cc[VMIN] = 0;
    new_setting.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_setting);    
}


void close_keyboard()
{
    tcsetattr(0, TCSANOW, &init_setting);
}

char get_key()
{
    char ch = -1;

    if(read(STDIN_FILENO, &ch, 1) != 1)
        ch = -1;
    return ch;
}

void print_menu()
{
    printf("\n\n-----------------------\n");
    printf("type degree for servo motor\n");
    printf("--------------------------\n\n");
}


int main(int argc, char **argv) {
    //-----------------setting ---------------------
    //fnd
    unsigned short data[4];
    char key;

    int num_array = 0; //index for fnd number * * * *

    //------------------driver initialize---------------
    //opening driver
    int dev_servo = open("/dev/my_pwm_driver", O_RDWR);

    if(dev_servo == -1) {
        printf("Opening servo was not possible!\n");
        return -1;
    }

    printf("device opening was successfull!\n");

    //------------------start-------------------------
    init_keyboard();
    //print_menu();

    short buff;
    if(argc < 2)
    {
        printf("please put degree\n");
        return -1;
    }
    else
    {
        // 전달받은 인자 문자열 숫자로 변환 및 전달
        buff = (unsigned short)strtol(argv[1], NULL, 10);
        write(dev_servo, &buff, 2);
        printf("%d\n", buff);
    }

    close_keyboard();
    close(dev_servo);
    return 0;
}

int pwm(short degree)
{
    //------------------driver initialize---------------
    //opening driver
    int dev_servo = open("/dev/my_pwm_driver", O_RDWR);

    if(dev_servo == -1) {
        printf("Opening servo was not possible!\n");
        return -1;
    }

    printf("device opening was successfull!\n");

    //------------------start-------------------------

    write(dev_servo, &degree, 2);
    printf("%d\n", degree);


    close(dev_servo);
    return 0;
}