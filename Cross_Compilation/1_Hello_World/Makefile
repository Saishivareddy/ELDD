obj-m := Hello.o

# Cross Compilation
KERNELDIR = /lib/modules//5.15.48-Shiva-v7l+/build

default :
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(PWD) modules

clean :
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNELDIR) M=$(PWD) clean
