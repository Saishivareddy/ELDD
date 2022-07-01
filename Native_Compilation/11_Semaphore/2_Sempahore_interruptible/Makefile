obj-m := driver.o

#Native Compilation

KERN_DIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

default	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules
	gcc -o write1 write1.c
	gcc -o write2 write2.c
	gcc -o read read.c

clean	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
	rm -rf write1 write2 read
