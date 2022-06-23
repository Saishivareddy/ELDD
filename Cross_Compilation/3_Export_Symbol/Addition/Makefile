obj-m := add.o

# Cross Compilation
KERN_DIR = /lib/modules/5.15.48-Shiva-v7l+/build

default	:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERN_DIR) M=$(PWD) modules

clean	:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERN_DIR) M=$(PWD) clean

