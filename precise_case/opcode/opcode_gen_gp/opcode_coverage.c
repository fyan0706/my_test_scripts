#include <stdio.h>

static void start_sample()
{
	printf("start_sample\n");
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
	printf("stop_sample\n");
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
	printf("mtr dump\n");
	asm volatile (
		"mov $104, %%rax\n\t"
		"vmcall\n\t"
		:
		:
		:"rax"
	);
}

static void wait_replay()
{
	printf("wait_replay\n");
	asm volatile (
		"mov $105, %%rax\n\t"
		"vmcall\n\t"
		:
		:
		:"rax"
	);
}
int instruction_coverage()
{

	void *mem = malloc(0x8000);
	void *mem_addr = mem + 0x4000;
//asm("aaa");
//asm("aad");
//asm("aam");
//asm("aas");
//asm("daa");
//asm("das");

asm("push %rsi");
asm("push %rdi");
asm("push %rbx");
asm("push %rax");
asm("push %rcx");
asm("pushf");

asm("adc %bl, %bl");
asm("sub %bl, %bl");
asm("adc %bx, %bx");
asm("or %bx, %bx");
asm("sbb %bx, %bx");
asm("adc %ebx, %ebx");
asm("adc $0x70, %al");
asm("sbb $0x70, %al");
asm("adc $0x7000, %ax");
asm("add $0x7000, %ax");
asm("or $0x7000, %ax");
asm("sbb $0x7000, %ax");
asm("xor $0x7000, %ax");
asm("adc $0x70000000, %eax");
asm("sbb $0x70000000, %eax");
asm("xor $0x70000000, %eax");
asm("adc $0x70, %bl");
asm("sbb $0x70, %bl");
asm("adc $0x7000, %bx");
asm("sbb $0x7000, %bx");
asm("xor $0x7000, %bx");
asm("adc %bl, %bl");
asm("sbb %bl, %bl");
asm("adc %bx, %bx");
asm("sbb %bx, %bx");
asm("adc %ebx, %ebx");
asm("bsf %bx, %bx");
asm("bsr %bx, %bx");
asm("btc %bx, %bx");
asm("btr %bx, %bx");
asm("bts %bx, %bx");
asm("btc $0x70, %bx");
asm("btr $0x70, %bx");
asm("bts $0x70, %bx");
asm("btc $0x70, %ebx");
asm("bt $0x70, %bx");
asm("bt %bx, %bx");
//asm("bound (%rsi), %bx");
//asm("bound (%rsi), %ebx");
//asm("arpl %bx, %bx");
//asm("call %ebx");
//asm("call %bx");
//asm("call 0x00000000");
//asm("call 0x0000");
asm("cbw");
asm("clc");
// #GP asm("clts");
asm("cmc");
asm("cwd");
//asm("enter_op16 $0x70, $0x7000");
//asm("enter_op32 $0x70, $0x7000");
asm("imul %rbx, %rbx");
asm("imul $0x70, %rbx, %rbx");
//asm("in $0x70, %al");
//asm("in %dx, %ax");
//asm("in $0x70, %ax");
//asm("in %dx, %eax");
//asm("in $0x70, %eax");
//asm("out %ax, %dx");
//asm("out %eax, %dx");
//asm("out %al, $0x70");
//asm("out %ax, $0x70");
//asm("out %eax, $0x70");
//asm("int $0x70");
//asm("int3");
//asm("into");
//asm("jmp %rbx");
asm("movabsq $jmp_i_next, %rax \n\t"
    "jmp *%rax \n\t"
    "jmp_i_next: \n\t"
    "nop \n\t");
//asm("jmp %bx");
asm("jmp jmp_next \n\t"
    "jmp_next: \n\t"
    "nop \n\t");
//asm("jmp 0x00000000");
//asm("jcxz 0x0");
//asm("jecxz 0x0");

asm("mov $5, %rcx");
//asm("loop_op16 0x0");
asm("loop loop_next \n\t"
    "loop_next:\n\t"
    "nop");
//asm("loope_op16 0x0");
asm("loope loope_next \n\t"
    "loope_next:\n\t"
    "nop");
//asm("loopne_op16 0x0");
asm("loopne loopne_next \n\t"
    "loopne_next:\n\t"
    "nop");
//asm("loop_op32 0x0");
//asm("loope_op32 0x0");
//asm("loopne_op32 0x0");
//asm("jb 0x0000");
asm("jb jb_next \n\t"
    "jb_next: \n\t"
    "nop \n\t");
//asm("jbe 0x0000");
asm("jbe jbe_next \n\t"
    "jbe_next: \n\t"
    "nop \n\t");
//asm("jl 0x0000");
asm("jl jl_next \n\t"
    "jl_next: \n\t"
    "nop \n\t");
//asm("jle 0x0000");
asm("jle jle_next \n\t"
    "jle_next: \n\t"
    "nop \n\t");
//asm("jnb 0x0000");
asm("jnb jnb_next \n\t"
    "jnb_next: \n\t"
    "nop \n\t");
//asm("jnbe 0x0000");
asm("jnbe jnbe_next \n\t"
    "jnbe_next: \n\t"
    "nop \n\t");
//asm("jnl 0x0000");
asm("jnl jnl_next \n\t"
    "jnl_next: \n\t"
    "nop \n\t");
//asm("jnle 0x0000");
asm("jnle jnle_next \n\t"
    "jnle_next: \n\t"
    "nop \n\t");
//asm("jno 0x0000");
asm("jno jno_next \n\t"
    "jno_next: \n\t"
    "nop \n\t");
//asm("jnp 0x0000");
asm("jnp jnp_next \n\t"
    "jnp_next: \n\t"
    "nop \n\t");
//asm("jns 0x0000");
asm("jns jns_next \n\t"
    "jns_next: \n\t"
    "nop \n\t");
//asm("jnz 0x0000");
asm("jnz jnz_next \n\t"
    "jnz_next: \n\t"
    "nop \n\t");
//asm("jo 0x0000");
asm("jo jo_next \n\t"
    "jo_next: \n\t"
    "nop \n\t");
//asm("jp 0x0000");
asm("jp jp_next \n\t"
    "jp_next: \n\t"
    "nop \n\t");
//asm("js 0x0000");
asm("js js_next \n\t"
    "js_next: \n\t"
    "nop \n\t");
//asm("jz 0x0000");
asm("jz jz_next \n\t"
    "jz_next: \n\t"
    "nop \n\t");
//asm("jb 0x00000000");
//asm("jbe 0x00000000");
//asm("jl 0x00000000");
//asm("jle 0x00000000");
//asm("jnb 0x00000000");
//asm("jnbe 0x00000000");
//asm("jnl 0x00000000");
//asm("jnle 0x00000000");
//asm("jno 0x00000000");
//asm("jnp 0x00000000");
//asm("jns 0x00000000");
//asm("jnz 0x00000000");
//asm("jo 0x00000000");
//asm("jp 0x00000000");
//asm("js 0x00000000");
//asm("jz 0x00000000");
//asm("lahf");
//asm("sahf");
//asm("lds %ds:(%rsi), %ebx");
//asm("lds %ds:(%rsi), %bx");
//asm("les %ds:(%rsi), %ebx");
//asm("les %ds:(%rsi), %bx");
//asm("lfs %ds:(%rsi), %ebx");
//asm("lfs %ds:(%rsi), %bx");
//asm("lss %ds:(%rsi), %ebx");
//asm("lss %ds:(%rsi), %bx");
//asm("lgs %ds:(%rsi), %ebx");
//asm("lgs %ds:(%rsi), %bx");
asm("xor %bx, %bx"); asm("lar %bx, %bx");
asm("lsl %bx, %bx");
asm("lar %bx, %ebx");
//asm("sidt (%rsi)");
//asm("lidt (%rsi)");
//asm("sgdt (%rsi)");
//asm("lgdt (%rsi)");
//asm("sldt %bx");
//asm("lldt %bx");
//asm("str %bx");
//asm("ltr %bx");
asm("smsw %bx");
// CPL0 asm("lmsw %bx");
// CPL0 asm("mov %ebx, %cr0");
// CPL0 asm("mov %ebx, %cr2");
// CPL0 asm("mov %ebx, %cr3");
// CPL0 asm("mov %cr0, %ebx");
// CPL0 asm("mov %cr2, %ebx");
// CPL0 asm("mov %cr3, %ebx");
// CPL0 asm("mov %db0, %ebx");
// CPL0 asm("mov %ebx, %db0");
//asm("mov_op32 %ebx, %ebx");
//asm("mov_op32 %ebx, %ebx");

asm("mov %0, %%rdi"::"rdi"(mem_addr):);
asm("mov %0, %%rsi"::"rsi"(mem_addr):);
asm("mov %ds:(%rdi), %al");
asm("mov %ds:(%rdi), %ax");
asm("mov %ds:(%rdi), %eax");
asm("mov %al, %ds:(%rdi)");
asm("mov %ax, %ds:(%rdi)");
asm("mov %eax, %ds:(%rdi)");

asm("push %bx");
//asm("push %ebx");
asm("push %rbx");
asm("push $0x70000000");
asm("push $0x7000");
asm("pushf ");
asm("popf ");
asm("pop %bx");
//asm("pop %ebx");
asm("pop %rbx");
asm("pop %rbx");
asm("pop %bx");

asm("mov %ds, %ax");
asm("mov %ax, %es");
asm("mov %0, %%rdi"::"rdi"(mem_addr):);
asm("mov %0, %%rsi"::"rsi"(mem_addr):);
asm("mov $5, %rcx");
asm("rep cmpsd");
asm("rep cmpsw");
//asm("rep insb");
//asm("rep insd");
//asm("rep insw");
asm("rep lodsb (%rsi)");
//asm("rep lodsd (%rsi)");
asm("rep lodsw (%rsi)");
asm("rep movsw");
//asm("rep outsb %dx");
//asm("rep outsd %dx");
//asm("rep outsw %dx");
//asm("rep scasd %eax");
asm("rep scasw (%rdi)");
//asm("ret_op16 $0x7000");
//asm("ret_op32 $0x7000");
asm("not %bx");
asm("neg %bx");
asm("rol %bl");
asm("ror %bl");
asm("rcl %bl");
asm("rcr %bl");
asm("shr %bl");
asm("sar %bl");
asm("rol %bx");
asm("ror %bx");
asm("rcl %bx");
asm("rcr %bx");
asm("shr %bx");
asm("sar %bx");
asm("ror %ebx");
asm("rcl %ebx");
asm("rcr %ebx");
asm("rol $0x70, %bl");
asm("ror $0x70, %bl");
asm("rcl $0x70, %bl");
asm("rcr $0x70, %bl");
asm("ror $0x70, %bx");
asm("rcl $0x70, %bx");
asm("rcr $0x70, %bx");
asm("rcl $0x70, %ebx");
asm("rcr $0x70, %ebx");
asm("setno %bl");
asm("shld %ebx, %ebx");
asm("shld $0x70, %ebx, %ebx");
asm("shld %bx, %bx");
asm("shld $0x70, %bx, %bx");
asm("shrd %ebx, %ebx");
asm("shrd $0x70, %ebx, %ebx");
asm("shrd %bx, %bx");
asm("shrd $0x70, %bx, %bx");
//asm("rsm");
asm("stc");
asm("std");
asm("mul %al");
asm("imul %al");
asm("div %bl, %al");
asm("idiv %bl, %al");
asm("mul %ax");
asm("imul %ax");
asm("div %bx, %ax");
asm("idiv %bx, %ax");
asm("verr %bx");
asm("verw %bx");
asm("xchg %bl, %bl");

asm("mov %0, %%rbx"::"rbx"(mem_addr):);
asm("xlat");
asm("movq %xmm0, %rbx");
//asm("ud0 %eax, %eax");
//asm("ud1 %eax, %eax");
//asm("ud2");
asm("adc $0x70000000, %rax");
asm("sbb $0x70000000, %rax");
asm("xor $0x70000000, %rax");

asm("mov %0, %%rdi"::"rdi"(mem_addr):);
asm("mov %0, %%rsi"::"rsi"(mem_addr):);
asm("mov $5, %rcx");
asm("mov %ds:(%rdi), %ax");
asm("mov %ax, %ds:(%rdi)");
asm("mov %al, %ds:(%rdi)");
asm("rep lodsq (%rsi)");
asm("rep scasq (%rdi)");
//asm("jo 0x0000000000000000");
//asm("enter_op64 $0x70, $0x7000");
asm("shld $0x70, %rbx, %rbx");
asm("shrd $0x70, %rbx, %rbx");
asm("movzx %bl, %rbx");
asm("btc %rbx, %rbx");
asm("btc $0x70, %rbx");
asm("rcl %rbx");
asm("rcr %rbx");
asm("rcl $0x70, %rbx");
asm("rcr $0x70, %rbx");
asm("cmovno %rbx, %rbx");
asm("cmovp %rbx, %rbx");
//asm("sgdt_op64 (%rsi)");
//asm("sidt_op64 (%rsi)");
//asm("lgdt_op64 (%rsi)");
//asm("lidt_op64 (%rsi)");

//asm("lss %ds:(%rsi), %rbx");
//asm("lfs %ds:(%rsi), %rbx");
//asm("lgs %ds:(%rsi), %rbx");
//asm("loopne_op64 0x0");
//asm("loope_op64 0x0");
//asm("loop_op64 0x0");
asm("jrcxz jrcxz_next \n\t"
    "jrcxz_next: \n\t"
    "nop");
asm("movq %rbx, %xmm0");
asm("cvttss2si %xmm0, %rbx");
asm("cvtss2si %xmm0, %rbx");
asm("cvtsd2si %xmm0, %rbx");
// CPL0 asm("mov %rbx, %cr2");
// CPL0 asm("mov %rbx, %cr4");
// CPL0 asm("mov %cr4, %rbx");
// CPL0 asm("mov %rbx, %db0");
// CPL0 asm("mov %db0, %rbx");
// CPL0 asm("invd");
// CPL0 asm("wbinvd");
asm("xadd %bx, %bx");
asm("adcx %ebx, %ebx");
asm("adox %ebx, %ebx");
asm("adcx %rbx, %rbx");
asm("adox %rbx, %rbx");
asm("aesimc %xmm0, %xmm0");
asm("aeskeygenassist $0x70, %xmm0, %xmm0");
asm("aesenc %xmm0, %xmm0");
asm("aesenclast %xmm0, %xmm0");
asm("aesdec %xmm0, %xmm0");
asm("aesdeclast %xmm0, %xmm0");
asm("andn %ebx, %ebx, %ebx");
asm("andn %rbx, %rbx, %rbx");
asm("blsi %ebx, %ebx");
asm("blsi %rbx, %rbx");
asm("blsmsk %ebx, %ebx");
asm("blsmsk %rbx, %rbx");
asm("blsr %ebx, %ebx");
asm("blsr %rbx, %rbx");
asm("bextr %ebx, %ebx, %ebx");
asm("bextr %rbx, %rbx, %rbx");
asm("tzcnt %bx, %bx");
asm("tzcnt %ebx, %ebx");
asm("mulx %ebx, %ebx, %ebx");
asm("mulx %rbx, %rbx, %rbx");
asm("rorx $0x70, %ebx, %ebx");
asm("rorx $0x70, %rbx, %rbx");
asm("shlx %ebx, %ebx, %ebx");
asm("shlx %rbx, %rbx, %rbx");
asm("shrx %ebx, %ebx, %ebx");
asm("shrx %rbx, %rbx, %rbx");
asm("sarx %ebx, %ebx, %ebx");
asm("sarx %rbx, %rbx, %rbx");
asm("bzhi %ebx, %ebx, %ebx");
asm("bzhi %rbx, %rbx, %rbx");
asm("pext %ebx, %ebx, %ebx");
asm("pext %rbx, %rbx, %rbx");
asm("pdep %ebx, %ebx, %ebx");
asm("pdep %rbx, %rbx, %rbx");
asm("clflush (%rsi)");
asm("clflushopt (%rsi)");
asm("clwb (%rdi)");
// UD asm("rdfsbase %ebx");
// UD asm("rdgsbase %ebx");
// UD asm("rdfsbase %rbx");
// UD asm("rdgsbase %rbx");
// UD asm("wrfsbase %ebx");
// UD asm("wrgsbase %ebx");
// UD asm("wrfsbase %rbx");
// UD asm("wrgsbase %rbx");
//asm("invpcid");
asm("lzcnt %bx, %bx");
asm("lzcnt %ebx, %ebx");
asm("lzcnt %rbx, %rbx");
asm("movbe (%rsi), %bx");
asm("movbe (%rsi), %ebx");
asm("movbe (%rsi), %rbx");
asm("movbe %bx, (%rsi)");
asm("movbe %ebx, (%rsi)");
asm("movbe %rbx, (%rsi)");
asm("cmovb %bx, %bx");
asm("cmovbe %bx, %bx");
asm("cmovl %bx, %bx");
asm("cmovle %bx, %bx");
asm("cmovnb %bx, %bx");
asm("cmovnbe %bx, %bx");
asm("cmovnl %bx, %bx");
asm("cmovnle %bx, %bx");
asm("cmovno %bx, %bx");
asm("cmovnp %bx, %bx");
asm("cmovnz %bx, %bx");
asm("cmovo %bx, %bx");
asm("cmovp %bx, %bx");
asm("cmovs %bx, %bx");
asm("cmovz %bx, %bx");
asm("cmovno %ebx, %ebx");
asm("cmovnp %ebx, %ebx");
asm("cmovo %ebx, %ebx");
asm("cmovp %ebx, %ebx");
// CPL0 asm("rdpmc");
// CPL0 asm("mov %ebx, %cr4");
// CPL0 asm("mov %cr4, %ebx");
//asm("cmpxchg8b %al, %bl");
// UD asm("rdpkru");
// UD asm("wrpkru");
// UD asm("rdpid %rbx");
asm("rdrand %bx");
asm("rdseed %bx");
asm("rdseed %ebx");
asm("rdseed %rbx");
// UD asm("sha1nexte %xmm0, %xmm0");
// UD asm("sha1msg1 %xmm0, %xmm0");
// UD asm("sha1msg2 %xmm0, %xmm0");
// UD asm("sha256rnds2 %xmm0, %xmm0");
// UD asm("sha256msg1 %xmm0, %xmm0");
// UD asm("sha256msg2 %xmm0, %xmm0");
// UD asm("sha1rnds4 $0x70, %xmm0, %xmm0");
//asm("sysenter");
//asm("sysexit");
// UD asm("bextr $0x70000000, %ebx, %ebx");
// UD asm("bextr $0x70000000, %rbx, %rbx");
asm("fninit");
asm("fnclex");
//asm("frstor");
asm("fnsave (%rdi)");
asm("fldenv (%rdi)");
//asm("fnstenv");
asm("fldcw (%rdi)");
asm("fnstsw");
asm("fnstsw %ax");
asm("fld1");
asm("fldl2t");
asm("fldl2e");
asm("fldpi");
asm("fldlg2");
asm("fldln2");
asm("fldz");
asm("fcompp");
asm("fucompp");
asm("fnop");
asm("fchs");
asm("fabs");
asm("ftst");
asm("fxam");
asm("fdecstp");
asm("fincstp");
asm("f2xm1");
asm("fyl2x");
asm("fptan");
asm("fpatan");
asm("fxtract");
asm("fprem1");
asm("fprem");
asm("fyl2xp1");
asm("fsqrt");
asm("fsincos");
asm("frndint");
asm("fscale");
asm("fsin");
asm("fcos");
//asm("xsetbv");
//asm("xsavec (%rdi)");
//asm("xsaves (%r8)");
//asm("xrstors (%rdi)");

asm("popf");
asm("pop %rcx");
asm("pop %rax");
asm("pop %rbx");
asm("pop %rdi");
asm("pop %rsi");

	free(mem);
}
int main()
{
	start_sample();
	instruction_coverage();
	stop_sample();
	mtr_dump();
	return 0;
}
