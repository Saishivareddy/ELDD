obj-m := driver.o

# Native Compilation

KERN_DIR := /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

default	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules
	gcc -o test_app test_app.c 

clean	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
	rm -rf test_app
