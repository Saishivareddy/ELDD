obj-y := Average/ Addition/

# Native Compilation
KERN_DIR= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

default	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules

install	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules_install
	depmod -a
clean	:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
	rm -rf /lib/modules/$(shell uname -r)/extra/*


