obj-m := module_param.o

# Native Compilation

KERN_DIR = /lib/modules/$(shell uname -r)/build

PWD:= $(shell pwd)

all :
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules

install : 
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules_install

clean :
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
