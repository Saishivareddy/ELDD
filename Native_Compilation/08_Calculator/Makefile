
obj-m := calculator.o

KERN_DIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

default	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules
	gcc -o add add.c
	gcc -o sub sub.c
	gcc -o mul mul.c
	gcc -o div div.c

clean 	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
	rm -rf add sub mul div
