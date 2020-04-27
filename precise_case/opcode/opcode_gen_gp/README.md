environment:
	ubuntu 18.04 / centos 7.4
	gcc 7.3.0

guide:

user mode instruction test:(64 bit)
	compile: gcc instruction_coverage_all.c 
	(note: centos gcc 4.8 is ok but failed on gcc 7.3.0 on ubuntu 18, remove inline assembly containing 'var' in case this happens.)
	run: ./a.out

user mode instruction test:(32 bit)
	compile: gcc instruction_coverage_all_32.c -m32
	(note: m32 lib is required. Link failed due to the absence of m32 lib on centos 7.4)
	run: ./a.out

kernel mode instruction test:
	compile: cd instruction_coverage_kernel
		 make
	run: insmod x86_ins_cpl0.ko (root required)

generate assembly code:
	python instruction_generation.py opcode_table.csv

summary coverage and print uncovered instructions:
	python instruction_statistic.py valid_opcode.csv [dir that contains inst.logs...]
