#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

struct _invpcid{
	u64 pcid;
	u64 linear_addr;
};

static void start_sample()
{
	asm volatile (
		"mov $102, %%rax\n\t"
		"vmcall\n\t"
		:
		:
		:"rax"
	);
}

static void stop_sample()
{
	asm volatile (
		"mov $103, %%rax\n\t"
		"vmcall\n\t"
		:
		:
		:"rax"
	);
}

static void mtr_dump()
{
	printk("mtr dump\n");
	asm volatile (
		"mov $104, %%rax\n\t"
		"vmcall\n\t"
		:
		:
		:"rax"
	);
}

static int __init x86_ins_cpl0_init(void)
{
	void *mem = kmalloc(0x1000, GFP_KERNEL);
	struct _invpcid invpcid = {
		0,
		&invpcid
	};

	void *invpcid_ptr = &invpcid;
	u64 fs_base, gs_base;
	asm volatile (
		"mov $102, %%rax\n\t"
		"vmcall\n\t"
		:
		:
		:"rax"
	);
	rdmsrl_safe(MSR_FS_BASE, &fs_base);
	rdmsrl_safe(MSR_FS_BASE, &gs_base);
	asm("push %rcx");
	asm("push %rdx");
	asm("push %rsi");
	asm("push %rdi");
	asm("pushf");
	
	asm("mov %0, %%rdi"::"m"(mem):);
	asm("mov %0, %%rsi"::"m"(mem):);
	
	asm("in $0x64, %al");
	asm("out %al, $0x64");
	asm("mov $0x64, %dx");
	asm("in %dx, %al");
	asm("in %dx, %ax");
	asm("in %dx, %eax");
	asm("out %al, %dx");
	asm("out %ax, %dx");
	asm("out %eax, %dx");


	asm("mov $0x64, %dx");
	asm("mov $1, %rcx");
	asm("rep insb");

	asm("mov $0x64, %dx");
	asm("mov $1, %rcx");
	asm("rep insw");

	asm("mov $0x64, %dx");
	asm("mov $1, %rcx");
	asm("rep insl");

	asm("mov $0x64, %dx");
	asm("mov $1, %rcx");
	asm("rep outsb");

	asm("mov $0x64, %dx");
	asm("mov $1, %rcx");
	asm("rep outsw");

	asm("mov $0x64, %dx");
	asm("mov $1, %rcx");
	asm("rep outsl");

	asm("mov %cr0, %rax");
	asm("mov %rax, %cr0");
	asm("mov %cr2, %rax");
	asm("mov %rax, %cr2");
	asm("mov %cr3, %rax");
	asm("mov %rax, %cr3");
	asm("mov %cr4, %rax");
	asm("mov %rax, %cr4");
	asm("mov %cr8, %rax");
	asm("mov %rax, %cr8");

	asm("mov %dr0, %rax");
	asm("mov %rax, %dr0");

	asm("mov %0, %%rdi"::"m"(mem):);
	asm("mov %0, %%rsi"::"m"(mem):);
	
	asm("sidt (%rsi)");
	asm("lidt (%rsi)");
	asm("sgdt (%rsi)");
	asm("lgdt (%rsi)");
	asm("sldt (%rsi)");
	asm("lldt (%rsi)");
	asm("str %ax");

	//asm("ltr %ax");
	asm("clts");

	asm("smsw %ax");
	asm("lmsw %ax");
	
	asm("invd");
	asm("wbinvd");

	asm("mov %0, %%rdi"::"m"(mem):);
	asm("mov %0, %%rsi"::"m"(mem):);

	
	//asm("xsaves (%0)"::"rsi"(mem):);
	//asm("xrstors (%0)"::"rsi"(mem):);
	//asm("lds (%rsi), %rax");
	//asm("les (%rsi), %rax");
	//asm("lds (%rsi), %ax");
	//asm("les (%rsi), %ax");

	asm("mov %fs, %ax");
	asm("mov %ax, (%rsi)");
	asm("xor %rax, %rax");
	asm("mov %rax, 2(%rsi)");
	asm("lfs (%rsi), %rax");
	asm("lfs (%rsi), %ax");

	asm("mov %gs, %ax");
	asm("mov %ax, (%rsi)");
	asm("xor %rax, %rax");
	asm("mov %rax, 2(%rsi)");
	//asm("lgs (%rsi), %rax");
	//asm("lgs (%rsi), %ax");
	
	asm("mov %ss, %ax");
	asm("mov %ax, (%rsi)");
	asm("xor %rax, %rax");
	asm("mov %rax, 2(%rsi)");
	asm("lss (%rsi), %rax");
	asm("lss (%rsi), %ax");

	asm("mov $0x1, %rax");
	asm("mov %0, %%rsi"::"m"(invpcid_ptr):);
	asm("invpcid (%rsi), %rax");
	
end:
	asm("popf");
	asm("pop %rdi");
	asm("pop %rsi");
	asm("pop %rdx");
	asm("pop %rcx");

	asm volatile (
		"mov $103, %%rax\n\t"
		"vmcall\n\t"
		:
		:
		:"rax"
	);

	asm volatile (
		"mov $104, %%rax\n\t"
		"vmcall\n\t"
		:
		:
		:"rax"
	);

	wrmsrl(MSR_FS_BASE, fs_base);
	//wrmsrl(MSR_GS_BASE, gs_base);
	
	return 0;
}

static void __exit x86_ins_cpl0_exit(void)
{
	
}

module_init(x86_ins_cpl0_init);
module_exit(x86_ins_cpl0_exit);
MODULE_LICENSE("GPL");
