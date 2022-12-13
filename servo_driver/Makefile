obj-m += pwm_driver.o
RESULT = test
SRC = $(RESULT).c
CCC = gcc
# KDIR 오류로 인해 빠짐



all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	$(CCC) -o $(RESULT) $(SRC)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean