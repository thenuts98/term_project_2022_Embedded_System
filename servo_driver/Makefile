obj-m += pwm_driver.o
KDIR = ~/kernel
RESULT = servo_driver
SRC = $(RESULT).c
CCC = gcc


all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean