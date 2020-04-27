obj-m :=x86_ins_cpl0.o
all:
	make -C /lib/modules/$(shell uname -r)/build SUBDIRS=$(PWD) -Werror=strict-prototypes  modules
clean:
	make -C /lib/modules/$(shell uname -r)/build SUBDIRS=$(PWD) clean
