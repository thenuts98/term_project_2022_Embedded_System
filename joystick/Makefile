obj-m += adc_driver.o
RESULT = adc
SRC = $(RESULT).c
CCC = gcc

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	$(CCC) -o $(RESULT) $(SRC)
	$(CCC) -c $(SRC)
	$(CCC) -shared -o $(RESULT).dll $(RESULT).o

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean