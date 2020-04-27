CC=gcc
INSTALL = /usr/bin/install
#all: opcode_coverage_all_32 x86_ins_cpl0
all: opcode_coverage_all_32 x86_ins_cpl0 opcode_coverage_all
opcode_coverage_all:opcode_coverage_all.c sampling.c
	$(CC) -O0 -o opcode_coverage_all opcode_coverage_all.c sampling.c
opcode_coverage_all_32:opcode_coverage_all_32.c sampling.c
	$(CC) -O0  -m32 -o opcode_coverage_all_32 opcode_coverage_all_32.c sampling.c 

obj-m :=x86_ins_cpl0.o #sampling.o
x86_ins_cpl0-y += sampling.o
x86_ins_cpl0:x86_ins_cpl0.c sampling.c
	make -C /lib/modules/$(shell uname -r)/build SUBDIRS=$(PWD) modules

prefix :=/usr/local

install: all 
	test -d $(prefix) || mkdir $(prefix)
	test -d $(prefix)/bin || mkdir $(prefix)/bin
	$(INSTALL) -m 0755 opcode_coverage_all $(prefix)/bin
	$(INSTALL) -m 0755 x86_ins_cpl0 $(prefix)/bin
	$(INSTALL) -m 0755 opcode_coverage_all_32 $(prefix)/bin

clean:
	rm -f opcode_coverage_all x86_ins_cpl0 opcode_coverage_all_32 *.o
	make -C /lib/modules/$(shell uname -r)/build SUBDIRS=$(PWD) clean
.PHONY: all clean install
