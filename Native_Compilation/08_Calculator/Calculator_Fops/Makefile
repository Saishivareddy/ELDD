
obj-m := calculator.o

KERN_DIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

default	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules
	gcc -o arith arith.c
	
clean 	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
	rm -rf arith
