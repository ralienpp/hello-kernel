obj-m := hellok.o 

# location of the kernel source
KDIR  := /lib/modules/$(shell uname -r)/build

PWD   := $(shell pwd)

# only compile the modules in the current directory, i.e. our driver
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
