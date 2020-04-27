#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>
#define __USE_GNU
#include<sched.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>
#define __USE_GNU
#include<sched.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <ucontext.h>
#include <signal.h>
#include "sampling.h"

#define filename(x) strrchr(x,'/')?strrchr(x,'/')+1:x

void fault_handler(int signum, siginfo_t * si, void *p)
{
	ucontext_t *uc = (ucontext_t *)p;
	printf("rip = 0x%llx\n", uc->uc_mcontext.gregs[REG_RIP]);
	exit(0);
}


void inner_call()
{
	
}

//long var = 0;
#define ALIGN_4K(x) (void *)((long)(x) + (0x1000 - (long)(x) % 0x1000))

int instruction_coverage()
{
	void *tmp_ptr;
	tmp_ptr = malloc(0x8000);
	void *mem_addr_int = ALIGN_4K(tmp_ptr);
	tmp_ptr = malloc(0x8000);
	void *mem_addr_fp = ALIGN_4K(tmp_ptr);
	tmp_ptr = malloc(0x8000);
	void *fpu_state_save = ALIGN_4K(tmp_ptr);
	void *inner_call_ptr = inner_call;


asm("push %rsi");
asm("push %rdi");
asm("push %rbx");
asm("push %rax");
asm("push %rcx");
asm("pushf");
//asm("mov %0, %%rdi"::"m"(fpu_state_save):);
//asm("xsave (%rdi)");

double a = 1.0f;
((double *)mem_addr_fp)[0] = a;
((double *)mem_addr_fp)[1] = a;
((double *)mem_addr_fp)[2] = a;
((double *)mem_addr_fp)[3] = a;
((double *)mem_addr_fp)[4] = a;
((double *)mem_addr_fp)[5] = a;
((double *)mem_addr_fp)[6] = a;
((double *)mem_addr_fp)[7] = a;

asm("mov %0, %%rdi"::"m"(mem_addr_int):);
asm("mov %0, %%rsi"::"m"(mem_addr_int):);

// 32-bit asm("aaa"); 	//0	_AAA
// 32-bit asm("aad"); 	//0	_AAD
// 32-bit asm("aam"); 	//0	_AAM
// 32-bit asm("aas"); 	//0	_AAS
// 32-bit asm("daa"); 	//0	_DAA
// 32-bit asm("das"); 	//0	_DAS
asm("adc %bl, %bl"); 	//0	_ADC_EbGb
asm("and %bl, %bl"); 	//0	_AND_EbGb
asm("add %bl, %bl"); 	//0	_ADD_EbGb
asm("cmp %bl, %bl"); 	//0	_CMP_EbGb
asm("or %bl, %bl"); 	//0	_OR_EbGb
asm("sbb %bl, %bl"); 	//0	_SBB_EbGb
asm("sub %bl, %bl"); 	//0	_SUB_EbGb
asm("test %bl, %bl"); 	//0	_TEST_EbGb
asm("xor %bl, %bl"); 	//0	_XOR_EbGb
asm("adc %bx, %bx"); 	//0	_ADC_EwGw
asm("add %bx, %bx"); 	//0	_ADD_EwGw
asm("and %bx, %bx"); 	//0	_AND_EwGw
asm("cmp %bx, %bx"); 	//0	_CMP_EwGw
asm("or %bx, %bx"); 	//0	_OR_EwGw
asm("sbb %bx, %bx"); 	//0	_SBB_EwGw
asm("sub %bx, %bx"); 	//0	_SUB_EwGw
asm("test %bx, %bx"); 	//0	_TEST_EwGw
asm("xor %bx, %bx"); 	//0	_XOR_EwGw
asm("adc %ebx, %ebx"); 	//0	_ADC_EdGd
asm("add %ebx, %ebx"); 	//0	_ADD_EdGd
asm("and %ebx, %ebx"); 	//0	_AND_EdGd
asm("cmp %ebx, %ebx"); 	//0	_CMP_EdGd
asm("or %ebx, %ebx"); 	//0	_OR_EdGd
asm("sbb %ebx, %ebx"); 	//0	_SBB_EdGd
asm("sub %ebx, %ebx"); 	//0	_SUB_EdGd
asm("test %ebx, %ebx"); 	//0	_TEST_EdGd
asm("xor %ebx, %ebx"); 	//0	_XOR_EdGd
asm("adc $0x70, %al"); 	//0	_ADC_ALIb
asm("add $0x70, %al"); 	//0	_ADD_ALIb
asm("and $0x70, %al"); 	//0	_AND_ALIb
asm("cmp $0x70, %al"); 	//0	_CMP_ALIb
asm("or $0x70, %al"); 	//0	_OR_ALIb
asm("sbb $0x70, %al"); 	//0	_SBB_ALIb
asm("sub $0x70, %al"); 	//0	_SUB_ALIb
asm("test $0x70, %al"); 	//0	_TEST_ALIb
asm("xor $0x70, %al"); 	//0	_XOR_ALIb
asm("adc $0x7000, %ax"); 	//0	_ADC_AXIw
asm("add $0x7000, %ax"); 	//0	_ADD_AXIw
asm("and $0x7000, %ax"); 	//0	_AND_AXIw
asm("cmp $0x7000, %ax"); 	//0	_CMP_AXIw
asm("or $0x7000, %ax"); 	//0	_OR_AXIw
asm("sbb $0x7000, %ax"); 	//0	_SBB_AXIw
asm("sub $0x7000, %ax"); 	//0	_SUB_AXIw
asm("test $0x7000, %ax"); 	//0	_TEST_AXIw
asm("xor $0x7000, %ax"); 	//0	_XOR_AXIw
asm("adc $0x70000000, %eax"); 	//0	_ADC_EAXId
asm("add $0x70000000, %eax"); 	//0	_ADD_EAXId
asm("and $0x70000000, %eax"); 	//0	_AND_EAXId
asm("cmp $0x70000000, %eax"); 	//0	_CMP_EAXId
asm("or $0x70000000, %eax"); 	//0	_OR_EAXId
asm("sbb $0x70000000, %eax"); 	//0	_SBB_EAXId
asm("sub $0x70000000, %eax"); 	//0	_SUB_EAXId
asm("test $0x70000000, %eax"); 	//0	_TEST_EAXId
asm("xor $0x70000000, %eax"); 	//0	_XOR_EAXId
asm("add $0x70, %bl"); 	//0	_ADD_EbIb
asm("or $0x70, %bl"); 	//0	_OR_EbIb
asm("adc $0x70, %bl"); 	//0	_ADC_EbIb
asm("sbb $0x70, %bl"); 	//0	_SBB_EbIb
asm("and $0x70, %bl"); 	//0	_AND_EbIb
asm("sub $0x70, %bl"); 	//0	_SUB_EbIb
asm("xor $0x70, %bl"); 	//0	_XOR_EbIb
asm("test $0x70, %bl"); 	//0	_TEST_EbIb
asm("cmp $0x70, %bl"); 	//0	_CMP_EbIb
asm("add $0x7000, %bx"); 	//0	_ADD_EwIw
asm("or $0x7000, %bx"); 	//0	_OR_EwIw
asm("adc $0x7000, %bx"); 	//0	_ADC_EwIw
asm("sbb $0x7000, %bx"); 	//0	_SBB_EwIw
asm("and $0x7000, %bx"); 	//0	_AND_EwIw
asm("sub $0x7000, %bx"); 	//0	_SUB_EwIw
asm("xor $0x7000, %bx"); 	//0	_XOR_EwIw
asm("test $0x7000, %bx"); 	//0	_TEST_EwIw
asm("cmp $0x7000, %bx"); 	//0	_CMP_EwIw
asm("add $0x70000000, %ebx"); 	//0	_ADD_EdId
asm("or $0x70000000, %ebx"); 	//0	_OR_EdId
asm("adc $0x70000000, %ebx"); 	//0	_ADC_EdId
asm("sbb $0x70000000, %ebx"); 	//0	_SBB_EdId
asm("and $0x70000000, %ebx"); 	//0	_AND_EdId
asm("sub $0x70000000, %ebx"); 	//0	_SUB_EdId
asm("xor $0x70000000, %ebx"); 	//0	_XOR_EdId
asm("test $0x70000000, %ebx"); 	//0	_TEST_EdId
asm("cmp $0x70000000, %ebx"); 	//0	_CMP_EdId
asm("add (%rdi), %bl"); 	//0	_ADD_GbEb
asm("or (%rdi), %bl"); 	//0	_OR_GbEb
asm("adc (%rdi), %bl"); 	//0	_ADC_GbEb
asm("sbb (%rdi), %bl"); 	//0	_SBB_GbEb
asm("and (%rdi), %bl"); 	//0	_AND_GbEb
asm("sub (%rdi), %bl"); 	//0	_SUB_GbEb
asm("xor (%rdi), %bl"); 	//0	_XOR_GbEb
asm("cmp (%rdi), %bl"); 	//0	_CMP_GbEb
asm("adc (%rdi), %bx"); 	//0	_ADC_GwEw
asm("add (%rdi), %bx"); 	//0	_ADD_GwEw
asm("and (%rdi), %bx"); 	//0	_AND_GwEw
asm("cmp (%rdi), %bx"); 	//0	_CMP_GwEw
asm("or (%rdi), %bx"); 	//0	_OR_GwEw
asm("sbb (%rdi), %bx"); 	//0	_SBB_GwEw
asm("sub (%rdi), %bx"); 	//0	_SUB_GwEw
asm("xor (%rdi), %bx"); 	//0	_XOR_GwEw
asm("adc (%rdi), %ebx"); 	//0	_ADC_GdEd
asm("add (%rdi), %ebx"); 	//0	_ADD_GdEd
asm("and (%rdi), %ebx"); 	//0	_AND_GdEd
asm("cmp (%rdi), %ebx"); 	//0	_CMP_GdEd
asm("or (%rdi), %ebx"); 	//0	_OR_GdEd
asm("sbb (%rdi), %ebx"); 	//0	_SBB_GdEd
asm("sub (%rdi), %ebx"); 	//0	_SUB_GdEd
asm("xor (%rdi), %ebx"); 	//0	_XOR_GdEd
asm("inc %bl"); 	//0	_INC_Eb
asm("inc %bx"); 	//0	_INC_Ew
asm("inc %ebx"); 	//0	_INC_Ed
asm("dec %bl"); 	//0	_DEC_Eb
asm("dec %bx"); 	//0	_DEC_Ew
asm("dec %ebx"); 	//0	_DEC_Ed
asm("bsf (%rdi), %bx"); 	//0	_BSF_GwEw
asm("bsr (%rdi), %bx"); 	//0	_BSR_GwEw
asm("bsf (%rdi), %ebx"); 	//0	_BSF_GdEd
asm("bsr (%rdi), %ebx"); 	//0	_BSR_GdEd
asm("btc %bx, %bx"); 	//0	_BTC_EwGw
asm("btr %bx, %bx"); 	//0	_BTR_EwGw
asm("bts %bx, %bx"); 	//0	_BTS_EwGw
asm("btc %ebx, %ebx"); 	//0	_BTC_EdGd
asm("btr %ebx, %ebx"); 	//0	_BTR_EdGd
asm("bts %ebx, %ebx"); 	//0	_BTS_EdGd
asm("btc $0x70, %bx"); 	//0	_BTC_EwIb
asm("btr $0x70, %bx"); 	//0	_BTR_EwIb
asm("bts $0x70, %bx"); 	//0	_BTS_EwIb
asm("btc $0x70, %ebx"); 	//0	_BTC_EdIb
asm("btr $0x70, %ebx"); 	//0	_BTR_EdIb
asm("bts $0x70, %ebx"); 	//0	_BTS_EdIb
asm("bt $0x70, %bx"); 	//0	_BT_EwIb
asm("bt $0x70, %ebx"); 	//0	_BT_EdIb
asm("bt %bx, %bx"); 	//0	_BT_EwGw
asm("bt %ebx, %ebx"); 	//0	_BT_EdGd

// 32-bit asm("bound (%rsi), %bx"); 	//0	_BOUND_GwMa
// 32-bit asm("bound (%rsi), %ebx"); 	//0	_BOUND_GdMa
// 32-bit asm("arpl %bx, %bx"); 	//0	_ARPL_EwGw
// 32-bit asm("call %ebx"); 	//0	_CALL_Ed
asm("mov %0, %%rbx \n\t"::"m"(inner_call_ptr):);
// 16-bit asm("call *%bx"); 	//0	_CALL_Ew
// 32-bit asm("call call_Jd \n\t call_Jd:\n\t"); 	//0	_CALL_Jd
// 16-bit asm("call call_Jw \n\t call_Jw:\n\t"); 	//0	_CALL_Jw
asm("mov %rbx, (%rdi)");
//asm("call %cs:(%rdi)"); 	//0	_CALLF_Op16_Ap
//asm("call %cs:(%rdi)"); 	//0	_CALLF_Op32_Ap
//asm("call *%rbx"); 	//0	_CALLF_Op16_Ep
//asm("call *%rbx"); 	//0	_CALLF_Op32_Ep
asm("cbw"); 	//0	_CBW
asm("cdq"); 	//0	_CDQ
asm("clc"); 	//0	_CLC
asm("cld"); 	//0	_CLD
// CPL0 asm("cli"); 	//0	_CLI
// CPL0 asm("clts"); 	//0	_CLTS
asm("cmc"); 	//0	_CMC
asm("cwd"); 	//0	_CWD
asm("cwde"); 	//0	_CWDE
// CPL0 asm("hlt"); 	//0	_HLT
asm("clflush (%rdi)"); 	//BX_ISA_CLFLUSH	_CLFLUSH
asm("clflushopt (%rdi)"); 	//BX_ISA_CLFLUSHOPT	_CLFLUSHOPT
asm("clwb (%rdi)"); 	//BX_ISA_CLWB	_CLWB
// UD asm("clzero"); 	//BX_ISA_CLZERO	_CLZERO
// RT asm("enter $0x1000, $0x0"); 	//0	_ENTER_Op16_IwIb
// RT asm("enter $0x1000, $0x1"); 	//0	_ENTER_Op32_IwIb
// RT asm("leave"); 	//0	_LEAVE_Op16
// RT asm("leave"); 	//0	_LEAVE_Op32
asm("imul %ebx, %ebx"); 	//0	_IMUL_GdEd
asm("imul $0x70000000, %ebx, %ebx"); 	//0	_IMUL_GdEdId
asm("imul %bx, %bx"); 	//0	_IMUL_GwEw
asm("imul $0x7000, %bx, %bx"); 	//0	_IMUL_GwEwIw
// CPL0 asm("in %dx, %al"); 	//0	_IN_ALDX
// CPL0 asm("in $0x70, %al"); 	//0	_IN_ALIb
// CPL0 asm("in %dx, %ax"); 	//0	_IN_AXDX
// CPL0 asm("in $0x70, %ax"); 	//0	_IN_AXIb
// CPL0 asm("in %dx, %eax"); 	//0	_IN_EAXDX
// CPL0 asm("in $0x70, %eax"); 	//0	_IN_EAXIb
// CPL0 asm("out %al, %dx"); 	//0	_OUT_DXAL
// CPL0 asm("out %ax, %dx"); 	//0	_OUT_DXAX
// CPL0 asm("out %eax, %dx"); 	//0	_OUT_DXEAX
// CPL0 asm("out %al, $0x70"); 	//0	_OUT_IbAL
// CPL0 asm("out %ax, $0x70"); 	//0	_OUT_IbAX
// CPL0 asm("out %eax, $0x70"); 	//0	_OUT_IbEAX
// RT asm("int $0x80"); 	//0	_INT_Ib
// NI asm("int1"); 	//0	_INT1
// TRAP asm("int3"); 	//0	_INT3
// 32 bit asm("into"); 	//0	_INTO
// CPL0 asm("iret"); 	//0	_IRET_Op16
// CPL0 asm("iret"); 	//0	_IRET_Op32
// 32-bit asm("jmp *%ebx"); 	//0	_JMP_Ed
// 16-bit asm("jmp *%bx"); 	//0	_JMP_Ew
// 16-bit asm("jmp jmp_Jw \n\t jmp_Jw:\n\t"); 	//0	_JMP_Jw
// 32-bit asm("jmp jmp_Jd \n\t jmp_Jd:\n\t"); 	//0	_JMP_Jd
// TODO asm("jmp *%cs:(%rdi)"); 	//0	_JMPF_Ap
// 16-bit asm("jmp *%bx"); 	//0	_JMPF_Op16_Ep
// 32-bit asm("jmp *%ebx"); 	//0	_JMPF_Op32_Ep
// 32-bit asm("jcxz jcxz_Jb \n\t jcxz_Jb:\n\t"); 	//0	_JCXZ_Jb
// 32-bit asm("jecxz jecxz_Jb \n\t jecxz_Jb:\n\t"); 	//0	_JECXZ_Jb
// 32-bit asm("loop LOOP_Jb \n\t LOOP_Jb:\n\t"); 	//0	_LOOP_Op16_Jb
// 32-bit asm("loope LOOPE_Jb \n\t LOOPE_Jb:\n\t"); 	//0	_LOOPE_Op16_Jb
// 32-bit asm("loopne LOOPNE_Jb \n\t LOOPNE_Jb:\n\t"); 	//0	_LOOPNE_Op16_Jb
// 32-bit asm("loop LOOP_Jb \n\t LOOP_Jb:\n\t"); 	//0	_LOOP_Op32_Jb
// 32-bit asm("loope LOOPE_Jb \n\t LOOPE_Jb:\n\t"); 	//0	_LOOPE_Op32_Jb
// 32-bit asm("loopne LOOPNE_Jb \n\t LOOPNE_Jb:\n\t"); 	//0	_LOOPNE_Op32_Jb
// 16-bit asm("jb jb_Jw \n\t jb_Jw:\n\t"); 	//0	_JB_Jw
// 16-bit asm("jbe jbe_Jw \n\t jbe_Jw:\n\t"); 	//0	_JBE_Jw
// 16-bit asm("jl jl_Jw \n\t jl_Jw:\n\t"); 	//0	_JL_Jw
// 16-bit asm("jle jle_Jw \n\t jle_Jw:\n\t"); 	//0	_JLE_Jw
// 16-bit asm("jnb jnb_Jw \n\t jnb_Jw:\n\t"); 	//0	_JNB_Jw
// 16-bit asm("jnbe jnbe_Jw \n\t jnbe_Jw:\n\t"); 	//0	_JNBE_Jw
// 16-bit asm("jnl jnl_Jw \n\t jnl_Jw:\n\t"); 	//0	_JNL_Jw
// 16-bit asm("jnle jnle_Jw \n\t jnle_Jw:\n\t"); 	//0	_JNLE_Jw
// 16-bit asm("jno jno_Jw \n\t jno_Jw:\n\t"); 	//0	_JNO_Jw
// 16-bit asm("jnp jnp_Jw \n\t jnp_Jw:\n\t"); 	//0	_JNP_Jw
// 16-bit asm("jns jns_Jw \n\t jns_Jw:\n\t"); 	//0	_JNS_Jw
// 16-bit asm("jnz jnz_Jw \n\t jnz_Jw:\n\t"); 	//0	_JNZ_Jw
// 16-bit asm("jo jo_Jw \n\t jo_Jw:\n\t"); 	//0	_JO_Jw
// 16-bit asm("jp jp_Jw \n\t jp_Jw:\n\t"); 	//0	_JP_Jw
// 16-bit asm("js js_Jw \n\t js_Jw:\n\t"); 	//0	_JS_Jw
// 16-bit asm("jz jz_Jw \n\t jz_Jw:\n\t"); 	//0	_JZ_Jw
// 32-bit asm("jb jb_Jd \n\t jb_Jd:\n\t"); 	//0	_JB_Jd
// 32-bit asm("jbe jbe_Jd \n\t jbe_Jd:\n\t"); 	//0	_JBE_Jd
// 32-bit asm("jl jl_Jd \n\t jl_Jd:\n\t"); 	//0	_JL_Jd
// 32-bit asm("jle jle_Jd \n\t jle_Jd:\n\t"); 	//0	_JLE_Jd
// 32-bit asm("jnb jnb_Jd \n\t jnb_Jd:\n\t"); 	//0	_JNB_Jd
// 32-bit asm("jnbe jnbe_Jd \n\t jnbe_Jd:\n\t"); 	//0	_JNBE_Jd
// 32-bit asm("jnl jnl_Jd \n\t jnl_Jd:\n\t"); 	//0	_JNL_Jd
// 32-bit asm("jnle jnle_Jd \n\t jnle_Jd:\n\t"); 	//0	_JNLE_Jd
// 32-bit asm("jno jno_Jd \n\t jno_Jd:\n\t"); 	//0	_JNO_Jd
// 32-bit asm("jnp jnp_Jd \n\t jnp_Jd:\n\t"); 	//0	_JNP_Jd
// 32-bit asm("jns jns_Jd \n\t jns_Jd:\n\t"); 	//0	_JNS_Jd
// 32-bit asm("jnz jnz_Jd \n\t jnz_Jd:\n\t"); 	//0	_JNZ_Jd
// 32-bit asm("jo jo_Jd \n\t jo_Jd:\n\t"); 	//0	_JO_Jd
// 32-bit asm("jp jp_Jd \n\t jp_Jd:\n\t"); 	//0	_JP_Jd
// 32-bit asm("js js_Jd \n\t js_Jd:\n\t"); 	//0	_JS_Jd
// 32-bit asm("jz jz_Jd \n\t jz_Jd:\n\t"); 	//0	_JZ_Jd
asm("sahf"); 	//0	_SAHF
asm("lahf"); 	//0	_LAHF
// 32-bit asm("lds (%rsi), %ebx"); 	//0	_LDS_GdMp
// 32-bit asm("lds (%rsi), %bx"); 	//0	_LDS_GwMp
// 32-bit asm("les (%rsi), %ebx"); 	//0	_LES_GdMp
// 32-bit asm("les (%rsi), %bx"); 	//0	_LES_GwMp
// RT asm("lfs (%rsi), %ebx"); 	//0	_LFS_GdMp
// RT asm("lfs (%rsi), %bx"); 	//0	_LFS_GwMp
// RT asm("lss (%rsi), %ebx"); 	//0	_LSS_GdMp
// RT asm("lss (%rsi), %bx"); 	//0	_LSS_GwMp
// RT asm("lgs (%rsi), %ebx"); 	//0	_LGS_GdMp
// RT asm("lgs (%rsi), %bx"); 	//0	_LGS_GwMp
asm("lar %bx, %bx"); 	//0	_LAR_GwEw
asm("lsl %bx, %bx"); 	//0	_LSL_GwEw
asm("lar %bx, %ebx"); 	//0	_LAR_GdEw
asm("lsl %bx, %ebx"); 	//0	_LSL_GdEw
asm("lea (%rsi), %ebx"); 	//0	_LEA_GdM
asm("lea (%rsi), %bx"); 	//0	_LEA_GwM
asm("sidt (%rsi)"); 	//0	_SIDT_Ms
// CPL0 asm("lidt (%rsi)"); 	//0	_LIDT_Ms
asm("sgdt (%rsi)"); 	//0	_SGDT_Ms
// CPL0 asm("lgdt (%rsi)"); 	//0	_LGDT_Ms
asm("sldt %bx"); 	//0	_SLDT_Ew
// CPL0 asm("lldt %bx"); 	//0	_LLDT_Ew
asm("str %bx"); 	//0	_STR_Ew
// CPL0 asm("ltr %bx"); 	//0	_LTR_Ew
asm("smsw %bx"); 	//0	_SMSW_Ew
// CPL0 asm("lmsw %bx"); 	//0	_LMSW_Ew
// CPL0 asm("mov %ebx, %cr0"); 	//0	_MOV_CR0Rd
// CPL0 asm("mov %ebx, %cr2"); 	//0	_MOV_CR2Rd
// CPL0 asm("mov %ebx, %cr3"); 	//0	_MOV_CR3Rd
// CPL0 asm("mov %ebx, %cr4"); 	//BX_ISA_PENTIUM	_MOV_CR4Rd
// CPL0 asm("mov %cr0, %ebx"); 	//0	_MOV_RdCR0
// CPL0 asm("mov %cr2, %ebx"); 	//0	_MOV_RdCR2
// CPL0 asm("mov %cr3, %ebx"); 	//0	_MOV_RdCR3
// CPL0 asm("mov %cr4, %ebx"); 	//BX_ISA_PENTIUM	_MOV_RdCR4
// CPL0 asm("mov %db0, %ebx"); 	//0	_MOV_RdDd
// CPL0 asm("mov %ebx, %db0"); 	//0	_MOV_DdRd
asm("mov $0x70, %bl"); 	//0	_MOV_EbIb
asm("mov $0x70000000, %ebx"); 	//0	_MOV_EdId
asm("mov $0x7000, %bx"); 	//0	_MOV_EwIw
asm("mov %bl, %bl"); 	//0	_MOV_GbEb
asm("mov %bl, %bl"); 	//0	_MOV_EbGb
asm("mov %bx, %bx"); 	//0	_MOV_GwEw
asm("mov %bx, %bx"); 	//0	_MOV_EwGw
asm("mov (%rdi), %ebx"); 	//0	_MOV_Op32_GdEd
asm("mov %ebx, %ebx"); 	//0	_MOV_Op32_EdGd
// ??? asm("mov , %bx"); 	//0	_MOV_EwSw
// ??? asm("mov %bx, "); 	//0	_MOV_SwEw
// CE asm("mov %ds:var, %al"); 	//0	_MOV_ALOd
// CE asm("mov %ds:var, %ax"); 	//0	_MOV_AXOd
// CE asm("mov %ds:var, %eax"); 	//0	_MOV_EAXOd
// CE asm("mov %al, %ds:var"); 	//0	_MOV_OdAL
// CE asm("mov %ax, %ds:var"); 	//0	_MOV_OdAX
// CE asm("mov %eax, %ds:var"); 	//0	_MOV_OdEAX
asm("movsx %bl, %ebx"); 	//0	_MOVSX_GdEb
asm("movsx %bx, %ebx"); 	//0	_MOVSX_GdEw
asm("movsx %bl, %bx"); 	//0	_MOVSX_GwEb
asm("movzx %bl, %ebx"); 	//0	_MOVZX_GdEb
asm("movzx %bx, %ebx"); 	//0	_MOVZX_GdEw
asm("movzx %bl, %bx"); 	//0	_MOVZX_GwEb
asm("nop"); 	//0	_NOP
asm("pause"); 	//0	_PAUSE
asm("push %bx"); 	//0	_PUSH_Ew
// 32-bit asm("push %ebx"); 	//0	_PUSH_Ed
asm("push $0x70000000"); 	//0	_PUSH_Id
asm("push $0x7000"); 	//0	_PUSH_Iw
// ??? asm("push "); 	//0	_PUSH_Op16_Sw
// ??? asm("push "); 	//0	_PUSH_Op32_Sw
// 32-bit asm("pusha"); 	//0	_PUSHA_Op16
// 32-bit asm("pusha"); 	//0	_PUSHA_Op32
//asm("pushf "); 	//0	_PUSHF_Fd
//asm("pushf "); 	//0	_PUSHF_Fw
//asm("popf "); 	//0	_POPF_Fd
//asm("popf "); 	//0	_POPF_Fw
asm("pop %bx"); 	//0	_POP_Ew
asm("pop %rbx"); 	//0	_POP_Ew
asm("pop %rbx"); 	//0	_POP_Ew
// 32-bit asm("pop %ebx"); 	//0	_POP_Ed
// ??? asm("pop "); 	//0	_POP_Op16_Sw
// ??? asm("pop "); 	//0	_POP_Op32_Sw
// 32-bit asm("popa"); 	//0	_POPA_Op16
// 32-bit asm("popa"); 	//0	_POPA_Op32
asm("mov $3, %rcx");
asm("rep cmpsb"); 	//0	_REP_CMPSB_XbYb
asm("mov $3, %rcx");
asm("rep cmpsd"); 	//0	_REP_CMPSD_XdYd
asm("mov $3, %rcx");
asm("rep cmpsw"); 	//0	_REP_CMPSW_XwYw
// CPL0 asm("rep insb"); 	//0	_REP_INSB_YbDX
// CPL0 asm("rep insl"); 	//0	_REP_INSD_YdDX
// CPL0 asm("rep insw"); 	//0	_REP_INSW_YwDX
asm("mov $3, %rcx");
asm("rep lodsb"); 	//0	_REP_LODSB_ALXb
asm("mov $3, %rcx");
asm("rep lodsl"); 	//0	_REP_LODSD_EAXXd
asm("mov $3, %rcx");
asm("rep lodsw"); 	//0	_REP_LODSW_AXXw
asm("mov $3, %rcx");
asm("rep movsb"); 	//0	_REP_MOVSB_YbXb
asm("mov $3, %rcx");
asm("rep movsl"); 	//0	_REP_MOVSD_YdXd
asm("mov $3, %rcx");
asm("rep movsw"); 	//0	_REP_MOVSW_YwXw
// CPL0 asm("rep outsb"); 	//0	_REP_OUTSB_DXXb
// CPL0 asm("rep outsl"); 	//0	_REP_OUTSD_DXXd
// CPL0 asm("rep outsw"); 	//0	_REP_OUTSW_DXXw
asm("mov $3, %rcx");
asm("rep scasb"); 	//0	_REP_SCASB_ALYb
asm("mov $3, %rcx");
asm("rep scasl"); 	//0	_REP_SCASD_EAXYd
asm("mov $3, %rcx");
asm("rep scasw"); 	//0	_REP_SCASW_AXYw
asm("mov $3, %rcx");
asm("rep stosb"); 	//0	_REP_STOSB_YbAL
asm("mov $3, %rcx");
asm("rep stosl"); 	//0	_REP_STOSD_YdEAX
asm("mov $3, %rcx");
asm("rep stosw"); 	//0	_REP_STOSW_YwAX
// TODO asm("retf"); 	//0	_RETF_Op16
// TODO asm("retf $0x7000"); 	//0	_RETF_Op16_Iw
// TODO asm("retf"); 	//0	_RETF_Op32
// TODO asm("retf $0x7000"); 	//0	_RETF_Op32_Iw
// TODO asm("ret"); 	//0	_RET_Op16
// TODO asm("ret $0x7000"); 	//0	_RET_Op16_Iw
// TODO asm("ret"); 	//0	_RET_Op32
// TODO asm("ret $0x7000"); 	//0	_RET_Op32_Iw
asm("not %bl"); 	//0	_NOT_Eb
asm("neg %bl"); 	//0	_NEG_Eb
asm("not %bx"); 	//0	_NOT_Ew
asm("neg %bx"); 	//0	_NEG_Ew
asm("not %ebx"); 	//0	_NOT_Ed
asm("neg %ebx"); 	//0	_NEG_Ed
asm("rol %cl, %bl"); 	//0	_ROL_Eb
asm("ror %cl, %bl"); 	//0	_ROR_Eb
asm("rcl %cl, %bl"); 	//0	_RCL_Eb
asm("rcr %cl, %bl"); 	//0	_RCR_Eb
asm("shl %cl, %bl"); 	//0	_SHL_Eb
asm("shr %cl, %bl"); 	//0	_SHR_Eb
asm("sar %cl, %bl"); 	//0	_SAR_Eb
asm("rol %cl, %bx"); 	//0	_ROL_Ew
asm("ror %cl, %bx"); 	//0	_ROR_Ew
asm("rcl %cl, %bx"); 	//0	_RCL_Ew
asm("rcr %cl, %bx"); 	//0	_RCR_Ew
asm("shl %cl, %bx"); 	//0	_SHL_Ew
asm("shr %cl, %bx"); 	//0	_SHR_Ew
asm("sar %cl, %bx"); 	//0	_SAR_Ew
asm("rol %cl, %ebx"); 	//0	_ROL_Ed
asm("ror %cl, %ebx"); 	//0	_ROR_Ed
asm("rcl %cl, %ebx"); 	//0	_RCL_Ed
asm("rcr %cl, %ebx"); 	//0	_RCR_Ed
asm("shl %cl, %ebx"); 	//0	_SHL_Ed
asm("shr %cl, %ebx"); 	//0	_SHR_Ed
asm("sar %cl, %ebx"); 	//0	_SAR_Ed
asm("rol $0x70, %bl"); 	//0	_ROL_EbIb
asm("ror $0x70, %bl"); 	//0	_ROR_EbIb
asm("rcl $0x70, %bl"); 	//0	_RCL_EbIb
asm("rcr $0x70, %bl"); 	//0	_RCR_EbIb
asm("shl $0x70, %bl"); 	//0	_SHL_EbIb
asm("shr $0x70, %bl"); 	//0	_SHR_EbIb
asm("sar $0x70, %bl"); 	//0	_SAR_EbIb
asm("rol $0x70, %bx"); 	//0	_ROL_EwIb
asm("ror $0x70, %bx"); 	//0	_ROR_EwIb
asm("rcl $0x70, %bx"); 	//0	_RCL_EwIb
asm("rcr $0x70, %bx"); 	//0	_RCR_EwIb
asm("shl $0x70, %bx"); 	//0	_SHL_EwIb
asm("shr $0x70, %bx"); 	//0	_SHR_EwIb
asm("sar $0x70, %bx"); 	//0	_SAR_EwIb
asm("rol $0x70, %ebx"); 	//0	_ROL_EdIb
asm("ror $0x70, %ebx"); 	//0	_ROR_EdIb
asm("rcl $0x70, %ebx"); 	//0	_RCL_EdIb
asm("rcr $0x70, %ebx"); 	//0	_RCR_EdIb
asm("shl $0x70, %ebx"); 	//0	_SHL_EdIb
asm("shr $0x70, %ebx"); 	//0	_SHR_EdIb
asm("sar $0x70, %ebx"); 	//0	_SAR_EdIb
asm("setb %bl"); 	//0	_SETB_Eb
asm("setbe %bl"); 	//0	_SETBE_Eb
asm("setl %bl"); 	//0	_SETL_Eb
asm("setle %bl"); 	//0	_SETLE_Eb
asm("setnb %bl"); 	//0	_SETNB_Eb
asm("setnbe %bl"); 	//0	_SETNBE_Eb
asm("setnl %bl"); 	//0	_SETNL_Eb
asm("setnle %bl"); 	//0	_SETNLE_Eb
asm("setno %bl"); 	//0	_SETNO_Eb
asm("setnp %bl"); 	//0	_SETNP_Eb
asm("setns %bl"); 	//0	_SETNS_Eb
asm("setnz %bl"); 	//0	_SETNZ_Eb
asm("seto %bl"); 	//0	_SETO_Eb
asm("setp %bl"); 	//0	_SETP_Eb
asm("sets %bl"); 	//0	_SETS_Eb
asm("setz %bl"); 	//0	_SETZ_Eb
asm("shld %ebx, %ebx"); 	//0	_SHLD_EdGd
asm("shld $0x70, %ebx, %ebx"); 	//0	_SHLD_EdGdIb
asm("shld %bx, %bx"); 	//0	_SHLD_EwGw
asm("shld $0x70, %bx, %bx"); 	//0	_SHLD_EwGwIb
asm("shrd %ebx, %ebx"); 	//0	_SHRD_EdGd
asm("shrd $0x70, %ebx, %ebx"); 	//0	_SHRD_EdGdIb
asm("shrd %bx, %bx"); 	//0	_SHRD_EwGw
asm("shrd $0x70, %bx, %bx"); 	//0	_SHRD_EwGwIb
// SMM asm("rsm"); 	//0	_RSM
// NI asm("salc"); 	//0	_SALC
asm("stc"); 	//0	_STC
asm("std"); 	//0	_STD
// CPL0 asm("sti"); 	//0	_STI
asm("mov $1, %rax");
asm("mov $1, %rbx");
asm("mul %bl"); 	//0	_MUL_ALEb
asm("imul %bl"); 	//0	_IMUL_ALEb
asm("div %bl"); 	//0	_DIV_ALEb
asm("idiv %bl"); 	//0	_IDIV_ALEb
asm("mul %bx"); 	//0	_MUL_AXEw
asm("imul %bx"); 	//0	_IMUL_AXEw
asm("div %bx"); 	//0	_DIV_AXEw
asm("idiv %bx"); 	//0	_IDIV_AXEw
asm("mul %ebx"); 	//0	_MUL_EAXEd
asm("imul %ebx"); 	//0	_IMUL_EAXEd
asm("div %ebx"); 	//0	_DIV_EAXEd
asm("idiv %ebx"); 	//0	_IDIV_EAXEd
asm("verr %bx"); 	//0	_VERR_Ew
asm("verw %bx"); 	//0	_VERW_Ew
asm("xchg %bl, %bl"); 	//0	_XCHG_EbGb
asm("xchg %bx, %bx"); 	//0	_XCHG_EwGw
asm("xchg %ebx, %ebx"); 	//0	_XCHG_EdGd
asm("xchg %ax, %bx"); 	//0	_XCHG_RXAX
asm("xchg %ebx, %eax"); 	//0	_XCHG_ERXEAX
asm("mov %rsi, %rbx");
asm("xlat"); 	//0	_XLAT

// RT asm("sysenter"); 	//BX_ISA_SYSENTER_SYSEXIT	_SYSENTER
// RT asm("sysexit"); 	//BX_ISA_SYSENTER_SYSEXIT	_SYSEXIT
// UD asm("monitor"); 	//BX_ISA_MONITOR_MWAIT	_MONITOR
// UD asm("mwait"); 	//BX_ISA_MONITOR_MWAIT	_MWAIT
// UD asm("monitorx"); 	//BX_ISA_MONITORX_MWAITX	_MONITORX
// UD asm("mwaitx"); 	//BX_ISA_MONITORX_MWAITX	_MWAITX

asm("fwait"); 	//BX_ISA_X87	_FWAIT
asm("fld %st(1)"); 	//BX_ISA_X87	_FLD_STi
asm("flds (%rsi)"); 	//BX_ISA_X87	_FLD_SINGLE_REAL
asm("fldl (%rsi)"); 	//BX_ISA_X87	_FLD_DOUBLE_REAL
asm("fldt (%rsi)"); 	//BX_ISA_X87	_FLD_EXTENDED_REAL
asm("fild (%rsi)"); 	//BX_ISA_X87	_FILD_WORD_INTEGER
asm("fildl (%rsi)"); 	//BX_ISA_X87	_FILD_DWORD_INTEGER
asm("fildq (%rsi)"); 	//BX_ISA_X87	_FILD_QWORD_INTEGER
asm("fbld (%rsi)"); 	//BX_ISA_X87	_FBLD_PACKED_BCD
asm("fst %st(1)"); 	//BX_ISA_X87	_FST_STi
asm("fstp %st(1)"); 	//BX_ISA_X87	_FSTP_STi
asm("fsts (%rsi)"); 	//BX_ISA_X87	_FST_SINGLE_REAL
asm("fstps (%rsi)"); 	//BX_ISA_X87	_FSTP_SINGLE_REAL
asm("fstl (%rsi)"); 	//BX_ISA_X87	_FST_DOUBLE_REAL
asm("fstpl (%rsi)"); 	//BX_ISA_X87	_FSTP_DOUBLE_REAL
asm("fstpt (%rsi)"); 	//BX_ISA_X87	_FSTP_EXTENDED_REAL
asm("fist (%rsi)"); 	//BX_ISA_X87	_FIST_WORD_INTEGER
asm("fistp (%rsi)"); 	//BX_ISA_X87	_FISTP_WORD_INTEGER
asm("fistl (%rsi)"); 	//BX_ISA_X87	_FIST_DWORD_INTEGER
asm("fistpl (%rsi)"); 	//BX_ISA_X87	_FISTP_DWORD_INTEGER
asm("fistpq (%rsi)"); 	//BX_ISA_X87	_FISTP_QWORD_INTEGER
asm("fbstp (%rsi)"); 	//BX_ISA_X87	_FBSTP_PACKED_BCD
asm("fisttp (%rsi)"); 	//BX_ISA_SSE3	_FISTTP_Mw
asm("fisttp (%rsi)"); 	//BX_ISA_SSE3	_FISTTP_Md
asm("fisttp (%rsi)"); 	//BX_ISA_SSE3	_FISTTP_Mq
asm("fninit"); 	//BX_ISA_X87	_FNINIT
asm("fnclex"); 	//BX_ISA_X87	_FNCLEX
asm("fnsave (%rdi)"); 	//BX_ISA_X87	_FNSAVE
asm("frstor (%rdi)"); 	//BX_ISA_X87	_FRSTOR
asm("fnstenv (%rdi)"); 	//BX_ISA_X87	_FNSTENV
asm("fldenv (%rdi)"); 	//BX_ISA_X87	_FLDENV
asm("fnstcw (%rdi)"); 	//BX_ISA_X87	_FNSTCW
asm("fldcw (%rdi)"); 	//BX_ISA_X87	_FLDCW

asm("mov %0, %%rdi"::"m"(mem_addr_fp):);
asm("mov %0, %%rsi"::"m"(mem_addr_fp):);


asm("fnstsw"); 	//BX_ISA_X87	_FNSTSW
asm("fnstsw %ax");
//BX_IA_FNSTSW_AX,BX_ISA_X87,BX_SUPPORT_FPU,Y,,0,
asm("fld1"); 	//BX_ISA_X87	_FLD1
asm("fldl2t"); 	//BX_ISA_X87	_FLDL2T
asm("fldl2e"); 	//BX_ISA_X87	_FLDL2E
asm("fldpi"); 	//BX_ISA_X87	_FLDPI
asm("fldlg2"); 	//BX_ISA_X87	_FLDLG2
asm("fldln2"); 	//BX_ISA_X87	_FLDLN2
asm("fldz"); 	//BX_ISA_X87	_FLDZ
asm("fadd %st(1), %st"); 	//BX_ISA_X87	_FADD_ST0_STj
asm("fadd %st, %st(1)"); 	//BX_ISA_X87	_FADD_STi_ST0
asm("faddp %st, %st(1)"); 	//BX_ISA_X87	_FADDP_STi_ST0
asm("fadds (%rsi)"); 	//BX_ISA_X87	_FADD_SINGLE_REAL
asm("faddl (%rsi)"); 	//BX_ISA_X87	_FADD_DOUBLE_REAL
asm("fiadd (%rsi)"); 	//BX_ISA_X87	_FIADD_WORD_INTEGER
asm("fiaddl (%rsi)"); 	//BX_ISA_X87	_FIADD_DWORD_INTEGER
asm("fmul %st(1), %st"); 	//BX_ISA_X87	_FMUL_ST0_STj
asm("fmul %st, %st(1)"); 	//BX_ISA_X87	_FMUL_STi_ST0
asm("fmulp %st, %st(1)"); 	//BX_ISA_X87	_FMULP_STi_ST0
asm("fmul (%rsi)"); 	//BX_ISA_X87	_FMUL_SINGLE_REAL
asm("fmul (%rsi)"); 	//BX_ISA_X87	_FMUL_DOUBLE_REAL
asm("fimul (%rsi)"); 	//BX_ISA_X87	_FIMUL_WORD_INTEGER
asm("fimull (%rsi)"); 	//BX_ISA_X87	_FIMUL_DWORD_INTEGER
asm("fsub %st(1), %st"); 	//BX_ISA_X87	_FSUB_ST0_STj
asm("fsubr %st(1), %st"); 	//BX_ISA_X87	_FSUBR_ST0_STj
asm("fsub %st, %st(1)"); 	//BX_ISA_X87	_FSUB_STi_ST0
asm("fsubp %st, %st(1)"); 	//BX_ISA_X87	_FSUBP_STi_ST0
asm("fsubr %st, %st(1)"); 	//BX_ISA_X87	_FSUBR_STi_ST0
asm("fsubrp %st, %st(1)"); 	//BX_ISA_X87	_FSUBRP_STi_ST0
asm("fsubs (%rsi)"); 	//BX_ISA_X87	_FSUB_SINGLE_REAL
asm("fsubrs (%rsi)"); 	//BX_ISA_X87	_FSUBR_SINGLE_REAL
asm("fsubl (%rsi)"); 	//BX_ISA_X87	_FSUB_DOUBLE_REAL
asm("fsubrl (%rsi)"); 	//BX_ISA_X87	_FSUBR_DOUBLE_REAL
asm("fisub (%rsi)"); 	//BX_ISA_X87	_FISUB_WORD_INTEGER
asm("fisubr (%rsi)"); 	//BX_ISA_X87	_FISUBR_WORD_INTEGER
asm("fisubl (%rsi)"); 	//BX_ISA_X87	_FISUB_DWORD_INTEGER
asm("fisubrl (%rsi)"); 	//BX_ISA_X87	_FISUBR_DWORD_INTEGER
asm("fdiv %st(1), %st"); 	//BX_ISA_X87	_FDIV_ST0_STj
asm("fdivr %st(1), %st"); 	//BX_ISA_X87	_FDIVR_ST0_STj
asm("fdiv %st, %st(1)"); 	//BX_ISA_X87	_FDIV_STi_ST0
asm("fdivp %st, %st(1)"); 	//BX_ISA_X87	_FDIVP_STi_ST0
asm("fdivr %st, %st(1)"); 	//BX_ISA_X87	_FDIVR_STi_ST0
asm("fdivrp %st, %st(1)"); 	//BX_ISA_X87	_FDIVRP_STi_ST0
asm("fdivs (%rsi)"); 	//BX_ISA_X87	_FDIV_SINGLE_REAL
asm("fdivrs (%rsi)"); 	//BX_ISA_X87	_FDIVR_SINGLE_REAL
asm("fdivl (%rsi)"); 	//BX_ISA_X87	_FDIV_DOUBLE_REAL
asm("fdivrl (%rsi)"); 	//BX_ISA_X87	_FDIVR_DOUBLE_REAL
asm("fidiv (%rsi)"); 	//BX_ISA_X87	_FIDIV_WORD_INTEGER
asm("fidivr (%rsi)"); 	//BX_ISA_X87	_FIDIVR_WORD_INTEGER
asm("fidivl (%rsi)"); 	//BX_ISA_X87	_FIDIV_DWORD_INTEGER
asm("fidivrl (%rsi)"); 	//BX_ISA_X87	_FIDIVR_DWORD_INTEGER
asm("fcom %st(1)"); 	//BX_ISA_X87	_FCOM_STi
asm("fcomp %st(1)"); 	//BX_ISA_X87	_FCOMP_STi
asm("fucom %st(1)"); 	//BX_ISA_X87	_FUCOM_STi
asm("fucomp %st(1)"); 	//BX_ISA_X87	_FUCOMP_STi
asm("fcomi %st(1), %st"); 	//BX_ISA_P6	_FCOMI_ST0_STj
asm("fcomip %st(1), %st"); 	//BX_ISA_P6	_FCOMIP_ST0_STj
asm("fucomi %st(1), %st"); 	//BX_ISA_P6	_FUCOMI_ST0_STj
asm("fucomip %st(1), %st"); 	//BX_ISA_P6	_FUCOMIP_ST0_STj
asm("fcoms (%rsi)"); 	//BX_ISA_X87	_FCOM_SINGLE_REAL
asm("fcomps (%rsi)"); 	//BX_ISA_X87	_FCOMP_SINGLE_REAL
asm("fcoml (%rsi)"); 	//BX_ISA_X87	_FCOM_DOUBLE_REAL
asm("fcompl (%rsi)"); 	//BX_ISA_X87	_FCOMP_DOUBLE_REAL
asm("ficom (%rsi)"); 	//BX_ISA_X87	_FICOM_WORD_INTEGER
asm("ficomp (%rsi)"); 	//BX_ISA_X87	_FICOMP_WORD_INTEGER
asm("ficoml (%rsi)"); 	//BX_ISA_X87	_FICOM_DWORD_INTEGER
asm("ficompl (%rsi)"); 	//BX_ISA_X87	_FICOMP_DWORD_INTEGER
asm("fcmovb %st(1), %st"); 	//BX_ISA_P6	_FCMOVB_ST0_STj
asm("fcmove %st(1), %st"); 	//BX_ISA_P6	_FCMOVE_ST0_STj
asm("fcmovbe %st(1), %st"); 	//BX_ISA_P6	_FCMOVBE_ST0_STj
asm("fcmovu %st(1), %st"); 	//BX_ISA_P6	_FCMOVU_ST0_STj
asm("fcmovnb %st(1), %st"); 	//BX_ISA_P6	_FCMOVNB_ST0_STj
asm("fcmovne %st(1), %st"); 	//BX_ISA_P6	_FCMOVNE_ST0_STj
asm("fcmovnbe %st(1), %st"); 	//BX_ISA_P6	_FCMOVNBE_ST0_STj
asm("fcmovnu %st(1), %st"); 	//BX_ISA_P6	_FCMOVNU_ST0_STj
asm("fcompp"); 	//BX_ISA_X87	_FCOMPP
asm("fucompp"); 	//BX_ISA_X87	_FUCOMPP
asm("fxch %st(1)"); 	//BX_ISA_X87	_FXCH_STi
asm("fnop"); 	//BX_ISA_X87	_FNOP
// NI asm("fplegacy"); 	//BX_ISA_X87	_FPLEGACY
asm("fchs"); 	//BX_ISA_X87	_FCHS
asm("fabs"); 	//BX_ISA_X87	_FABS
asm("ftst"); 	//BX_ISA_X87	_FTST
asm("fxam"); 	//BX_ISA_X87	_FXAM
asm("fdecstp"); 	//BX_ISA_X87	_FDECSTP
asm("fincstp"); 	//BX_ISA_X87	_FINCSTP
asm("ffree %st(1)"); 	//BX_ISA_X87	_FFREE_STi
asm("ffreep %st(1)"); 	//BX_ISA_X87	_FFREEP_STi
asm("f2xm1"); 	//BX_ISA_X87	_F2XM1
asm("fyl2x"); 	//BX_ISA_X87	_FYL2X
asm("fptan"); 	//BX_ISA_X87	_FPTAN
asm("fpatan"); 	//BX_ISA_X87	_FPATAN
asm("fxtract"); 	//BX_ISA_X87	_FXTRACT
asm("fprem1"); 	//BX_ISA_X87	_FPREM1
asm("fprem"); 	//BX_ISA_X87	_FPREM
asm("fyl2xp1"); 	//BX_ISA_X87	_FYL2XP1
asm("fsqrt"); 	//BX_ISA_X87	_FSQRT
asm("fsincos"); 	//BX_ISA_X87	_FSINCOS
asm("frndint"); 	//BX_ISA_X87	_FRNDINT
asm("fscale"); 	//BX_ISA_X87	_FSCALE
asm("fsin"); 	//BX_ISA_X87	_FSIN
asm("fcos"); 	//BX_ISA_X87	_FCOS
// NI asm("fpuesc"); 	//0	_FPUESC
asm("cpuid"); 	//BX_ISA_486	_CPUID
asm("bswap %eax");
//BX_IA_BSWAP_RX,BX_ISA_486,,Y,,0,486 new instructions

asm("bswap %rax");
//BX_IA_BSWAP_ERX,BX_ISA_486,,Y,,42691,486 new instructions

// CPL0 asm("invd"); 	//BX_ISA_486	_INVD
// CPL0 asm("wbinvd"); 	//BX_ISA_486	_WBINVD
asm("xadd %bl, %bl"); 	//BX_ISA_486	_XADD_EbGb
asm("xadd %bx, %bx"); 	//BX_ISA_486	_XADD_EwGw
asm("xadd %ebx, %ebx"); 	//BX_ISA_486	_XADD_EdGd
asm("cmpxchg %bl, %bl"); 	//BX_ISA_486	_CMPXCHG_EbGb
asm("cmpxchg %bx, %bx"); 	//BX_ISA_486	_CMPXCHG_EwGw
asm("cmpxchg %ebx, %ebx"); 	//BX_ISA_486	_CMPXCHG_EdGd
// CPL0 asm("invlpg (%rdi)"); 	//0	_INVLPG
asm("cmpxchg8b (%rdi)"); 	//BX_ISA_PENTIUM	_CMPXCHG8B
// CPL0 asm("wrmsr"); 	//BX_ISA_PENTIUM	_WRMSR
// CPL0 asm("rdmsr"); 	//BX_ISA_PENTIUM	_RDMSR
asm("rdtsc"); 	//BX_ISA_PENTIUM	_RDTSC
asm("punpcklbw %mm0, %mm0"); 	//BX_ISA_MMX	_PUNPCKLBW_PqQd
asm("punpcklwd %mm0, %mm0"); 	//BX_ISA_MMX	_PUNPCKLWD_PqQd
asm("punpckldq %mm0, %mm0"); 	//BX_ISA_MMX	_PUNPCKLDQ_PqQd
asm("packsswb %mm0, %mm0"); 	//BX_ISA_MMX	_PACKSSWB_PqQq
asm("pcmpgtb %mm0, %mm0"); 	//BX_ISA_MMX	_PCMPGTB_PqQq
asm("pcmpgtw %mm0, %mm0"); 	//BX_ISA_MMX	_PCMPGTW_PqQq
asm("pcmpgtd %mm0, %mm0"); 	//BX_ISA_MMX	_PCMPGTD_PqQq
asm("packuswb %mm0, %mm0"); 	//BX_ISA_MMX	_PACKUSWB_PqQq
asm("punpckhbw %mm0, %mm0"); 	//BX_ISA_MMX	_PUNPCKHBW_PqQq
asm("punpckhwd %mm0, %mm0"); 	//BX_ISA_MMX	_PUNPCKHWD_PqQq
asm("punpckhdq %mm0, %mm0"); 	//BX_ISA_MMX	_PUNPCKHDQ_PqQq
asm("packssdw %mm0, %mm0"); 	//BX_ISA_MMX	_PACKSSDW_PqQq
asm("movd %ebx, %mm0"); 	//BX_ISA_MMX	_MOVD_PqEd
asm("movq %mm0, %mm0"); 	//BX_ISA_MMX	_MOVQ_PqQq
asm("pcmpeqb %mm0, %mm0"); 	//BX_ISA_MMX	_PCMPEQB_PqQq
asm("pcmpeqw %mm0, %mm0"); 	//BX_ISA_MMX	_PCMPEQW_PqQq
asm("pcmpeqd %mm0, %mm0"); 	//BX_ISA_MMX	_PCMPEQD_PqQq
asm("emms"); 	//BX_ISA_MMX	_EMMS
asm("movd %mm0, %ebx"); 	//BX_ISA_MMX	_MOVD_EdPq
asm("movq %mm0, %mm0"); 	//BX_ISA_MMX	_MOVQ_QqPq
asm("psrlw %mm0, %mm0"); 	//BX_ISA_MMX	_PSRLW_PqQq
asm("psrld %mm0, %mm0"); 	//BX_ISA_MMX	_PSRLD_PqQq
asm("psrlq %mm0, %mm0"); 	//BX_ISA_MMX	_PSRLQ_PqQq
asm("pmullw %mm0, %mm0"); 	//BX_ISA_MMX	_PMULLW_PqQq
asm("psubusb %mm0, %mm0"); 	//BX_ISA_MMX	_PSUBUSB_PqQq
asm("psubusw %mm0, %mm0"); 	//BX_ISA_MMX	_PSUBUSW_PqQq
asm("pand %mm0, %mm0"); 	//BX_ISA_MMX	_PAND_PqQq
asm("paddusb %mm0, %mm0"); 	//BX_ISA_MMX	_PADDUSB_PqQq
asm("paddusw %mm0, %mm0"); 	//BX_ISA_MMX	_PADDUSW_PqQq
asm("pandn %mm0, %mm0"); 	//BX_ISA_MMX	_PANDN_PqQq
asm("psraw %mm0, %mm0"); 	//BX_ISA_MMX	_PSRAW_PqQq
asm("psrad %mm0, %mm0"); 	//BX_ISA_MMX	_PSRAD_PqQq
asm("pmulhw %mm0, %mm0"); 	//BX_ISA_MMX	_PMULHW_PqQq
asm("psubsb %mm0, %mm0"); 	//BX_ISA_MMX	_PSUBSB_PqQq
asm("psubsw %mm0, %mm0"); 	//BX_ISA_MMX	_PSUBSW_PqQq
asm("por %mm0, %mm0"); 	//BX_ISA_MMX	_POR_PqQq
asm("paddsb %mm0, %mm0"); 	//BX_ISA_MMX	_PADDSB_PqQq
asm("paddsw %mm0, %mm0"); 	//BX_ISA_MMX	_PADDSW_PqQq
asm("pxor %mm0, %mm0"); 	//BX_ISA_MMX	_PXOR_PqQq
asm("psllw %mm0, %mm0"); 	//BX_ISA_MMX	_PSLLW_PqQq
asm("pslld %mm0, %mm0"); 	//BX_ISA_MMX	_PSLLD_PqQq
asm("psllq %mm0, %mm0"); 	//BX_ISA_MMX	_PSLLQ_PqQq
asm("pmaddwd %mm0, %mm0"); 	//BX_ISA_MMX	_PMADDWD_PqQq
asm("psubb %mm0, %mm0"); 	//BX_ISA_MMX	_PSUBB_PqQq
asm("psubw %mm0, %mm0"); 	//BX_ISA_MMX	_PSUBW_PqQq
asm("psubd %mm0, %mm0"); 	//BX_ISA_MMX	_PSUBD_PqQq
asm("paddb %mm0, %mm0"); 	//BX_ISA_MMX	_PADDB_PqQq
asm("paddw %mm0, %mm0"); 	//BX_ISA_MMX	_PADDW_PqQq
asm("paddd %mm0, %mm0"); 	//BX_ISA_MMX	_PADDD_PqQq
asm("psrlw $0x70, %mm0"); 	//BX_ISA_MMX	_PSRLW_NqIb
asm("psraw $0x70, %mm0"); 	//BX_ISA_MMX	_PSRAW_NqIb
asm("psllw $0x70, %mm0"); 	//BX_ISA_MMX	_PSLLW_NqIb
asm("psrld $0x70, %mm0"); 	//BX_ISA_MMX	_PSRLD_NqIb
asm("psrad $0x70, %mm0"); 	//BX_ISA_MMX	_PSRAD_NqIb
asm("pslld $0x70, %mm0"); 	//BX_ISA_MMX	_PSLLD_NqIb
asm("psrlq $0x70, %mm0"); 	//BX_ISA_MMX	_PSRLQ_NqIb
asm("psllq $0x70, %mm0"); 	//BX_ISA_MMX	_PSLLQ_NqIb
asm("movq %mm0, %rbx"); 	//0	_MOVQ_EqPq
// AMD asm("femms"); 	//BX_ISA_3DNOW	_FEMMS
// AMD asm("pf2id %mm0, %mm0"); 	//BX_ISA_3DNOW	_PF2ID_PqQq
// AMD asm("pf2iw %mm0, %mm0"); 	//BX_ISA_3DNOW	_PF2IW_PqQq
// AMD asm("pfacc %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFACC_PqQq
// AMD asm("pfadd %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFADD_PqQq
// AMD asm("pfcmpeq %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFCMPEQ_PqQq
// AMD asm("pfcmpge %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFCMPGE_PqQq
// AMD asm("pfcmpgt %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFCMPGT_PqQq
// AMD asm("pfmax %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFMAX_PqQq
// AMD asm("pfmin %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFMIN_PqQq
// AMD asm("pfmul %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFMUL_PqQq
// AMD asm("pfnacc %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFNACC_PqQq
// AMD asm("pfpnacc %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFPNACC_PqQq
// AMD asm("pfrcp %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFRCP_PqQq
// AMD asm("pfrcpit1 %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFRCPIT1_PqQq
// AMD asm("pfrcpit2 %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFRCPIT2_PqQq
// AMD asm("pfrsqit1 %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFRSQIT1_PqQq
// AMD asm("pfrsqrt %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFRSQRT_PqQq
// AMD asm("pfsub %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFSUB_PqQq
// AMD asm("pfsubr %mm0, %mm0"); 	//BX_ISA_3DNOW	_PFSUBR_PqQq
// AMD asm("pi2fd %mm0, %mm0"); 	//BX_ISA_3DNOW	_PI2FD_PqQq
// AMD asm("pi2fw %mm0, %mm0"); 	//BX_ISA_3DNOW	_PI2FW_PqQq
// AMD asm("pmulhrw %mm0, %mm0"); 	//BX_ISA_3DNOW	_PMULHRW_PqQq
// AMD asm("pswapd %mm0, %mm0"); 	//BX_ISA_3DNOW	_PSWAPD_PqQq
asm("prefetchw (%rsi)"); 	//0	_PREFETCHW_Mb
// CPL0 asm("syscall"); 	//BX_ISA_SYSCALL_SYSRET_LEGACY	_SYSCALL_LEGACY
// CPL0 asm("sysret"); 	//BX_ISA_SYSCALL_SYSRET_LEGACY	_SYSRET_LEGACY
asm("cmovb %bx, %bx"); 	//BX_ISA_P6	_CMOVB_GwEw
asm("cmovbe %bx, %bx"); 	//BX_ISA_P6	_CMOVBE_GwEw
asm("cmovl %bx, %bx"); 	//BX_ISA_P6	_CMOVL_GwEw
asm("cmovle %bx, %bx"); 	//BX_ISA_P6	_CMOVLE_GwEw
asm("cmovnb %bx, %bx"); 	//BX_ISA_P6	_CMOVNB_GwEw
asm("cmovnbe %bx, %bx"); 	//BX_ISA_P6	_CMOVNBE_GwEw
asm("cmovnl %bx, %bx"); 	//BX_ISA_P6	_CMOVNL_GwEw
asm("cmovnle %bx, %bx"); 	//BX_ISA_P6	_CMOVNLE_GwEw
asm("cmovno %bx, %bx"); 	//BX_ISA_P6	_CMOVNO_GwEw
asm("cmovnp %bx, %bx"); 	//BX_ISA_P6	_CMOVNP_GwEw
asm("cmovns %bx, %bx"); 	//BX_ISA_P6	_CMOVNS_GwEw
asm("cmovnz %bx, %bx"); 	//BX_ISA_P6	_CMOVNZ_GwEw
asm("cmovo %bx, %bx"); 	//BX_ISA_P6	_CMOVO_GwEw
asm("cmovp %bx, %bx"); 	//BX_ISA_P6	_CMOVP_GwEw
asm("cmovs %bx, %bx"); 	//BX_ISA_P6	_CMOVS_GwEw
asm("cmovz %bx, %bx"); 	//BX_ISA_P6	_CMOVZ_GwEw
asm("cmovb %ebx, %ebx"); 	//BX_ISA_P6	_CMOVB_GdEd
asm("cmovbe %ebx, %ebx"); 	//BX_ISA_P6	_CMOVBE_GdEd
asm("cmovl %ebx, %ebx"); 	//BX_ISA_P6	_CMOVL_GdEd
asm("cmovle %ebx, %ebx"); 	//BX_ISA_P6	_CMOVLE_GdEd
asm("cmovnb %ebx, %ebx"); 	//BX_ISA_P6	_CMOVNB_GdEd
asm("cmovnbe %ebx, %ebx"); 	//BX_ISA_P6	_CMOVNBE_GdEd
asm("cmovnl %ebx, %ebx"); 	//BX_ISA_P6	_CMOVNL_GdEd
asm("cmovnle %ebx, %ebx"); 	//BX_ISA_P6	_CMOVNLE_GdEd
asm("cmovno %ebx, %ebx"); 	//BX_ISA_P6	_CMOVNO_GdEd
asm("cmovnp %ebx, %ebx"); 	//BX_ISA_P6	_CMOVNP_GdEd
asm("cmovns %ebx, %ebx"); 	//BX_ISA_P6	_CMOVNS_GdEd
asm("cmovnz %ebx, %ebx"); 	//BX_ISA_P6	_CMOVNZ_GdEd
asm("cmovo %ebx, %ebx"); 	//BX_ISA_P6	_CMOVO_GdEd
asm("cmovp %ebx, %ebx"); 	//BX_ISA_P6	_CMOVP_GdEd
asm("cmovs %ebx, %ebx"); 	//BX_ISA_P6	_CMOVS_GdEd
asm("cmovz %ebx, %ebx"); 	//BX_ISA_P6	_CMOVZ_GdEd
// UD asm("rdpmc"); 	//BX_ISA_P6	_RDPMC
// TRAP asm("ud0 %rax, %rax"); 	//0	_UD0
// TRAP asm("ud1 %rax, %rax"); 	//0	_UD1
// TRAP asm("ud2"); 	//0	_UD2

asm("mov %0, %%rdi"::"m"(mem_addr_int):);
asm("mov %0, %%rsi"::"m"(mem_addr_int):);

asm("fxsave (%rdi)"); 	//BX_ISA_SSE	_FXSAVE
asm("fxrstor (%rsi)"); 	//BX_ISA_SSE	_FXRSTOR
asm("stmxcsr (%rdi)"); 	//BX_ISA_SSE	_STMXCSR
asm("ldmxcsr (%rsi)"); 	//BX_ISA_SSE	_LDMXCSR

asm("prefetch (%rsi)"); 	//BX_ISA_SSE	_PREFETCH_Mb
asm("prefetcht0 (%rsi)"); 	//BX_ISA_SSE	_PREFETCHT0_Mb
asm("prefetcht1 (%rsi)"); 	//BX_ISA_SSE	_PREFETCHT1_Mb
asm("prefetcht2 (%rsi)"); 	//BX_ISA_SSE	_PREFETCHT2_Mb
asm("prefetchnta (%rsi)"); 	//BX_ISA_SSE	_PREFETCHNTA_Mb
asm("andps %xmm0, %xmm0"); 	//BX_ISA_SSE	_ANDPS_VpsWps
asm("orps %xmm0, %xmm0"); 	//BX_ISA_SSE	_ORPS_VpsWps
asm("xorps %xmm0, %xmm0"); 	//BX_ISA_SSE	_XORPS_VpsWps
asm("andnps %xmm0, %xmm0"); 	//BX_ISA_SSE	_ANDNPS_VpsWps
asm("movups %xmm0, %xmm0"); 	//BX_ISA_SSE	_MOVUPS_VpsWps
asm("movups %xmm0, %xmm0"); 	//BX_ISA_SSE	_MOVUPS_WpsVps
asm("movss %xmm0, %xmm0"); 	//BX_ISA_SSE	_MOVSS_VssWss
asm("movss %xmm0, %xmm0"); 	//BX_ISA_SSE	_MOVSS_WssVss
asm("movlps (%rsi), %xmm0"); 	//BX_ISA_SSE	_MOVLPS_VpsMq
asm("movlps %xmm0, (%rsi)"); 	//BX_ISA_SSE	_MOVLPS_MqVps
asm("movhps (%rsi), %xmm0"); 	//BX_ISA_SSE	_MOVHPS_VpsMq
asm("movhps %xmm0, (%rsi)"); 	//BX_ISA_SSE	_MOVHPS_MqVps
asm("movaps %xmm0, %xmm0"); 	//BX_ISA_SSE	_MOVAPS_VpsWps
asm("movaps %xmm0, %xmm0"); 	//BX_ISA_SSE	_MOVAPS_WpsVps
asm("movntps %xmm0, (%rsi)"); 	//BX_ISA_SSE	_MOVNTPS_MpsVps
asm("cvtpi2ps %mm0, %xmm0"); 	//BX_ISA_SSE	_CVTPI2PS_VpsQq
asm("cvtsi2ss %ebx, %xmm0"); 	//BX_ISA_SSE	_CVTSI2SS_VssEd
asm("cvttps2pi %xmm0, %mm0"); 	//BX_ISA_SSE	_CVTTPS2PI_PqWps
asm("cvtps2pi %xmm0, %mm0"); 	//BX_ISA_SSE	_CVTPS2PI_PqWps
asm("cvttss2si %xmm0, %ebx"); 	//BX_ISA_SSE	_CVTTSS2SI_GdWss
asm("cvtss2si %xmm0, %ebx"); 	//BX_ISA_SSE	_CVTSS2SI_GdWss
asm("ucomiss %xmm0, %xmm0"); 	//BX_ISA_SSE	_UCOMISS_VssWss
asm("comiss %xmm0, %xmm0"); 	//BX_ISA_SSE	_COMISS_VssWss
asm("movmskps %xmm0, %ebx"); 	//BX_ISA_SSE	_MOVMSKPS_GdUps
asm("movmskpd %xmm0, %ebx"); 	//BX_ISA_SSE2	_MOVMSKPD_GdUpd
asm("rsqrtps %xmm0, %xmm0"); 	//BX_ISA_SSE	_RSQRTPS_VpsWps
asm("rsqrtss %xmm0, %xmm0"); 	//BX_ISA_SSE	_RSQRTSS_VssWss
asm("rcpps %xmm0, %xmm0"); 	//BX_ISA_SSE	_RCPPS_VpsWps
asm("rcpss %xmm0, %xmm0"); 	//BX_ISA_SSE	_RCPSS_VssWss
// AMD asm("pshufw $0x70, %mm0, %mm0"); 	//BX_ISA_SSE/* | BX_ISA_3DNOW */	_PSHUFW_PqQqIb
asm("pshuflw $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE	_PSHUFLW_VdqWdqIb
// AMD asm("pinsrw $0x70, %bx, %mm0"); 	//BX_ISA_SSE/* | BX_ISA_3DNOW */	_PINSRW_PqEwIb
// AMD asm("pextrw $0x70, %mm0, %ebx"); 	//BX_ISA_SSE/* | BX_ISA_3DNOW */	_PEXTRW_GdNqIb
asm("shufps $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE	_SHUFPS_VpsWpsIb
// AMD asm("pmovmskb %mm0, %ebx"); 	//BX_ISA_SSE/* | BX_ISA_3DNOW */	_PMOVMSKB_GdNq
// AMD asm("pminub %mm0, %mm0"); 	//BX_ISA_SSE/* | BX_ISA_3DNOW */	_PMINUB_PqQq
// AMD asm("pmaxub %mm0, %mm0"); 	//BX_ISA_SSE/* | BX_ISA_3DNOW */	_PMAXUB_PqQq
asm("pavgb %mm0, %mm0"); 	//BX_ISA_SSE	_PAVGB_PqQq
asm("pavgw %mm0, %mm0"); 	//BX_ISA_SSE	_PAVGW_PqQq
// AMD asm("pmulhuw %mm0, %mm0"); 	//BX_ISA_SSE/* | BX_ISA_3DNOW */	_PMULHUW_PqQq
// AMD asm("movntq %mm0, (%rsi)"); 	//BX_ISA_SSE/* | BX_ISA_3DNOW */	_MOVNTQ_MqPq
// AMD asm("pminsw %mm0, %mm0"); 	//BX_ISA_SSE/* | BX_ISA_3DNOW */	_PMINSW_PqQq
asm("pmaxsw %mm0, %mm0"); 	//BX_ISA_SSE	_PMAXSW_PqQq
// AMD asm("psadbw %mm0, %mm0"); 	//BX_ISA_SSE/* | BX_ISA_3DNOW */	_PSADBW_PqQq
// AMD asm("maskmovq %mm0, %mm0"); 	//BX_ISA_SSE/* | BX_ISA_3DNOW */	_MASKMOVQ_PqNq
asm("addps %xmm0, %xmm0"); 	//BX_ISA_SSE	_ADDPS_VpsWps
asm("addpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_ADDPD_VpdWpd
asm("addss %xmm0, %xmm0"); 	//BX_ISA_SSE	_ADDSS_VssWss
asm("addsd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_ADDSD_VsdWsd
asm("mulps %xmm0, %xmm0"); 	//BX_ISA_SSE	_MULPS_VpsWps
asm("mulpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MULPD_VpdWpd
asm("mulss %xmm0, %xmm0"); 	//BX_ISA_SSE	_MULSS_VssWss
asm("mulsd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MULSD_VsdWsd
asm("subps %xmm0, %xmm0"); 	//BX_ISA_SSE	_SUBPS_VpsWps
asm("subpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_SUBPD_VpdWpd
asm("subss %xmm0, %xmm0"); 	//BX_ISA_SSE	_SUBSS_VssWss
asm("subsd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_SUBSD_VsdWsd
asm("minps %xmm0, %xmm0"); 	//BX_ISA_SSE	_MINPS_VpsWps
asm("minpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MINPD_VpdWpd
asm("minss %xmm0, %xmm0"); 	//BX_ISA_SSE	_MINSS_VssWss
asm("minsd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MINSD_VsdWsd
asm("divps %xmm0, %xmm0"); 	//BX_ISA_SSE	_DIVPS_VpsWps
asm("divpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_DIVPD_VpdWpd
asm("divss %xmm0, %xmm0"); 	//BX_ISA_SSE	_DIVSS_VssWss
asm("divsd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_DIVSD_VsdWsd
asm("maxps %xmm0, %xmm0"); 	//BX_ISA_SSE	_MAXPS_VpsWps
asm("maxpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MAXPD_VpdWpd
asm("maxss %xmm0, %xmm0"); 	//BX_ISA_SSE	_MAXSS_VssWss
asm("maxsd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MAXSD_VsdWsd
asm("sqrtps %xmm0, %xmm0"); 	//BX_ISA_SSE	_SQRTPS_VpsWps
asm("sqrtpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_SQRTPD_VpdWpd
asm("sqrtss %xmm0, %xmm0"); 	//BX_ISA_SSE	_SQRTSS_VssWss
asm("sqrtsd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_SQRTSD_VsdWsd
asm("cmpps $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE	_CMPPS_VpsWpsIb
asm("cmppd $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CMPPD_VpdWpdIb
asm("cmpss $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE	_CMPSS_VssWssIb
asm("cmpsd $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CMPSD_VsdWsdIb
asm("cvtps2pd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CVTPS2PD_VpdWps
asm("cvtpd2ps %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CVTPD2PS_VpsWpd
asm("cvtss2sd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CVTSS2SD_VsdWss
asm("cvtsd2ss %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CVTSD2SS_VssWsd
asm("movsd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MOVSD_VsdWsd
asm("movsd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MOVSD_WsdVsd
asm("cvtpi2pd %mm0, %xmm0"); 	//BX_ISA_SSE2	_CVTPI2PD_VpdQq
asm("cvtsi2sd %ebx, %xmm0"); 	//BX_ISA_SSE2	_CVTSI2SD_VsdEd
asm("cvttpd2pi %xmm0, %mm0"); 	//BX_ISA_SSE2	_CVTTPD2PI_PqWpd
asm("cvttsd2si %xmm0, %ebx"); 	//BX_ISA_SSE2	_CVTTSD2SI_GdWsd
asm("cvtpd2pi %xmm0, %mm0"); 	//BX_ISA_SSE2	_CVTPD2PI_PqWpd
asm("cvtsd2si %xmm0, %ebx"); 	//BX_ISA_SSE2	_CVTSD2SI_GdWsd
asm("ucomisd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_UCOMISD_VsdWsd
asm("comisd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_COMISD_VsdWsd
asm("cvtdq2ps %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CVTDQ2PS_VpsWdq
asm("cvtps2dq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CVTPS2DQ_VdqWps
asm("cvttps2dq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CVTTPS2DQ_VdqWps
asm("unpckhpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_UNPCKHPD_VpdWdq
asm("unpcklpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_UNPCKLPD_VpdWdq
asm("punpckhdq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PUNPCKHDQ_VdqWdq
asm("punpckldq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PUNPCKLDQ_VdqWdq
asm("movapd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MOVAPD_VpdWpd
asm("movapd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MOVAPD_WpdVpd
asm("movdqa %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MOVDQA_VdqWdq
asm("movdqa %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MOVDQA_WdqVdq
asm("movdqu %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MOVDQU_VdqWdq
asm("movdqu %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MOVDQU_WdqVdq
asm("movhpd %xmm0, (%rsi)"); 	//BX_ISA_SSE2	_MOVHPD_MqVsd
asm("movhpd (%rsi), %xmm0"); 	//BX_ISA_SSE2	_MOVHPD_VsdMq
asm("movlpd %xmm0, (%rsi)"); 	//BX_ISA_SSE2	_MOVLPD_MqVsd
asm("movlpd (%rsi), %xmm0"); 	//BX_ISA_SSE2	_MOVLPD_VsdMq
asm("movntdq %xmm0, (%rsi)"); 	//BX_ISA_SSE2	_MOVNTDQ_MdqVdq
asm("movntpd %xmm0, (%rsi)"); 	//BX_ISA_SSE2	_MOVNTPD_MpdVpd
asm("movupd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MOVUPD_VpdWpd
asm("movupd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MOVUPD_WpdVpd
asm("andnpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_ANDNPD_VpdWpd
asm("andpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_ANDPD_VpdWpd
asm("orpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_ORPD_VpdWpd
asm("xorpd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_XORPD_VpdWpd
asm("pand %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PAND_VdqWdq
asm("pandn %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PANDN_VdqWdq
asm("por %xmm0, %xmm0"); 	//BX_ISA_SSE2	_POR_VdqWdq
asm("pxor %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PXOR_VdqWdq
asm("punpcklbw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PUNPCKLBW_VdqWdq
asm("punpcklwd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PUNPCKLWD_VdqWdq
asm("unpcklps %xmm0, %xmm0"); 	//BX_ISA_SSE2	_UNPCKLPS_VpsWdq
asm("packsswb %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PACKSSWB_VdqWdq
asm("pcmpgtb %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PCMPGTB_VdqWdq
asm("pcmpgtw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PCMPGTW_VdqWdq
asm("pcmpgtd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PCMPGTD_VdqWdq
asm("packuswb %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PACKUSWB_VdqWdq
asm("punpckhbw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PUNPCKHBW_VdqWdq
asm("punpckhwd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PUNPCKHWD_VdqWdq
asm("unpckhps %xmm0, %xmm0"); 	//BX_ISA_SSE2	_UNPCKHPS_VpsWdq
asm("packssdw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PACKSSDW_VdqWdq
asm("punpcklqdq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PUNPCKLQDQ_VdqWdq
asm("punpckhqdq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PUNPCKHQDQ_VdqWdq
asm("movd %ebx, %xmm0"); 	//BX_ISA_SSE2	_MOVD_VdqEd
asm("pshufd $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSHUFD_VdqWdqIb
asm("pshufhw $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSHUFHW_VdqWdqIb
asm("pcmpeqb %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PCMPEQB_VdqWdq
asm("pcmpeqw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PCMPEQW_VdqWdq
asm("pcmpeqd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PCMPEQD_VdqWdq
asm("movd %mm0, (%rdi)"); 	//BX_ISA_SSE2	_MOVD_EdVd
asm("movq %mm0, (%rdi)"); 	//BX_ISA_SSE2	_MOVQ_VqWq
asm("movnti %ebx, (%rsi)"); 	//BX_ISA_SSE2	_MOVNTI_Op32_MdGd
asm("pinsrw $0x70, %ebx, %xmm0"); 	//BX_ISA_SSE2	_PINSRW_VdqEwIb
asm("pextrw $0x70, %xmm0, %ebx"); 	//BX_ISA_SSE2	_PEXTRW_GdUdqIb
asm("shufpd $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE2	_SHUFPD_VpdWpdIb
asm("psrlw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSRLW_VdqWdq
asm("psrld %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSRLD_VdqWdq
asm("psrlq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSRLQ_VdqWdq
asm("paddq %mm0, %mm0"); 	//BX_ISA_SSE2	_PADDQ_PqQq
asm("paddq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PADDQ_VdqWdq
asm("pmullw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PMULLW_VdqWdq
asm("movq (%rdi), %xmm0"); 	//BX_ISA_SSE2	_MOVQ_WqVq
asm("movdq2q %xmm0, %mm0"); 	//BX_ISA_SSE2	_MOVDQ2Q_PqUdq
asm("movq2dq %mm0, %xmm0"); 	//BX_ISA_SSE2	_MOVQ2DQ_VdqQq
asm("pmovmskb %xmm0, %ebx"); 	//BX_ISA_SSE2	_PMOVMSKB_GdUdq
asm("psubusb %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSUBUSB_VdqWdq
asm("psubusw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSUBUSW_VdqWdq
asm("pminub %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PMINUB_VdqWdq
asm("paddusb %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PADDUSB_VdqWdq
asm("paddusw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PADDUSW_VdqWdq
asm("pmaxub %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PMAXUB_VdqWdq
asm("pavgb %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PAVGB_VdqWdq
asm("psraw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSRAW_VdqWdq
asm("psrad %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSRAD_VdqWdq
asm("pavgw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PAVGW_VdqWdq
asm("pmulhuw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PMULHUW_VdqWdq
asm("pmulhw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PMULHW_VdqWdq
asm("cvttpd2dq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CVTTPD2DQ_VqWpd
asm("cvtpd2dq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CVTPD2DQ_VqWpd
asm("cvtdq2pd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_CVTDQ2PD_VpdWq
asm("psubsb %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSUBSB_VdqWdq
asm("psubsw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSUBSW_VdqWdq
asm("pminsw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PMINSW_VdqWdq
asm("paddsb %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PADDSB_VdqWdq
asm("paddsw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PADDSW_VdqWdq
asm("pmaxsw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PMAXSW_VdqWdq
asm("psllw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSLLW_VdqWdq
asm("pslld %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSLLD_VdqWdq
asm("psllq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSLLQ_VdqWdq
asm("pmuludq %mm0, %mm0"); 	//BX_ISA_SSE2	_PMULUDQ_PqQq
asm("pmuludq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PMULUDQ_VdqWdq
asm("pmaddwd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PMADDWD_VdqWdq
asm("psadbw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSADBW_VdqWdq
asm("maskmovdqu %xmm0, %xmm0"); 	//BX_ISA_SSE2	_MASKMOVDQU_VdqUdq
asm("psubb %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSUBB_VdqWdq
asm("psubw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSUBW_VdqWdq
asm("psubd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSUBD_VdqWdq
asm("psubq %mm0, %mm0"); 	//BX_ISA_SSE2	_PSUBQ_PqQq
asm("psubq %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PSUBQ_VdqWdq
asm("paddb %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PADDB_VdqWdq
asm("paddw %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PADDW_VdqWdq
asm("paddd %xmm0, %xmm0"); 	//BX_ISA_SSE2	_PADDD_VdqWdq
asm("psrlw $0x70, %xmm0"); 	//BX_ISA_SSE2	_PSRLW_UdqIb
asm("psraw $0x70, %xmm0"); 	//BX_ISA_SSE2	_PSRAW_UdqIb
asm("psllw $0x70, %xmm0"); 	//BX_ISA_SSE2	_PSLLW_UdqIb
asm("psrld $0x70, %xmm0"); 	//BX_ISA_SSE2	_PSRLD_UdqIb
asm("psrad $0x70, %xmm0"); 	//BX_ISA_SSE2	_PSRAD_UdqIb
asm("pslld $0x70, %xmm0"); 	//BX_ISA_SSE2	_PSLLD_UdqIb
asm("psrlq $0x70, %xmm0"); 	//BX_ISA_SSE2	_PSRLQ_UdqIb
asm("psrldq $0x70, %xmm0"); 	//BX_ISA_SSE2	_PSRLDQ_UdqIb
asm("psllq $0x70, %xmm0"); 	//BX_ISA_SSE2	_PSLLQ_UdqIb
asm("pslldq $0x70, %xmm0"); 	//BX_ISA_SSE2	_PSLLDQ_UdqIb
asm("lfence"); 	//BX_ISA_SSE2	_LFENCE
asm("sfence"); 	//BX_ISA_SSE	_SFENCE
asm("mfence"); 	//BX_ISA_SSE2	_MFENCE
asm("movddup %xmm0, %xmm0"); 	//BX_ISA_SSE3	_MOVDDUP_VpdWq
asm("movsldup %xmm0, %xmm0"); 	//BX_ISA_SSE3	_MOVSLDUP_VpsWps
asm("movshdup %xmm0, %xmm0"); 	//BX_ISA_SSE3	_MOVSHDUP_VpsWps
asm("haddpd %xmm0, %xmm0"); 	//BX_ISA_SSE3	_HADDPD_VpdWpd
asm("haddps %xmm0, %xmm0"); 	//BX_ISA_SSE3	_HADDPS_VpsWps
asm("hsubpd %xmm0, %xmm0"); 	//BX_ISA_SSE3	_HSUBPD_VpdWpd
asm("hsubps %xmm0, %xmm0"); 	//BX_ISA_SSE3	_HSUBPS_VpsWps
asm("addsubpd %xmm0, %xmm0"); 	//BX_ISA_SSE3	_ADDSUBPD_VpdWpd
asm("addsubps %xmm0, %xmm0"); 	//BX_ISA_SSE3	_ADDSUBPS_VpsWps
asm("lddqu (%rsi), %xmm0"); 	//BX_ISA_SSE3	_LDDQU_VdqMdq
asm("pshufb %mm0, %mm0"); 	//BX_ISA_SSSE3	_PSHUFB_PqQq
asm("phaddw %mm0, %mm0"); 	//BX_ISA_SSSE3	_PHADDW_PqQq
asm("phaddd %mm0, %mm0"); 	//BX_ISA_SSSE3	_PHADDD_PqQq
asm("phaddsw %mm0, %mm0"); 	//BX_ISA_SSSE3	_PHADDSW_PqQq
asm("pmaddubsw %mm0, %mm0"); 	//BX_ISA_SSSE3	_PMADDUBSW_PqQq
asm("phsubsw %mm0, %mm0"); 	//BX_ISA_SSSE3	_PHSUBSW_PqQq
asm("phsubw %mm0, %mm0"); 	//BX_ISA_SSSE3	_PHSUBW_PqQq
asm("phsubd %mm0, %mm0"); 	//BX_ISA_SSSE3	_PHSUBD_PqQq
asm("psignb %mm0, %mm0"); 	//BX_ISA_SSSE3	_PSIGNB_PqQq
asm("psignw %mm0, %mm0"); 	//BX_ISA_SSSE3	_PSIGNW_PqQq
asm("psignd %mm0, %mm0"); 	//BX_ISA_SSSE3	_PSIGND_PqQq
asm("pmulhrsw %mm0, %mm0"); 	//BX_ISA_SSSE3	_PMULHRSW_PqQq
asm("pabsb %mm0, %mm0"); 	//BX_ISA_SSSE3	_PABSB_PqQq
asm("pabsw %mm0, %mm0"); 	//BX_ISA_SSSE3	_PABSW_PqQq
asm("pabsd %mm0, %mm0"); 	//BX_ISA_SSSE3	_PABSD_PqQq
asm("palignr $0x70, %mm0, %mm0"); 	//BX_ISA_SSSE3	_PALIGNR_PqQqIb
asm("pshufb %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PSHUFB_VdqWdq
asm("phaddw %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PHADDW_VdqWdq
asm("phaddd %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PHADDD_VdqWdq
asm("phaddsw %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PHADDSW_VdqWdq
asm("pmaddubsw %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PMADDUBSW_VdqWdq
asm("phsubsw %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PHSUBSW_VdqWdq
asm("phsubw %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PHSUBW_VdqWdq
asm("phsubd %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PHSUBD_VdqWdq
asm("psignb %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PSIGNB_VdqWdq
asm("psignw %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PSIGNW_VdqWdq
asm("psignd %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PSIGND_VdqWdq
asm("pmulhrsw %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PMULHRSW_VdqWdq
asm("pabsb %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PABSB_VdqWdq
asm("pabsw %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PABSW_VdqWdq
asm("pabsd %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PABSD_VdqWdq
asm("palignr $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSSE3	_PALIGNR_VdqWdqIb
asm("pblendvb %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PBLENDVB_VdqWdq
asm("blendvps %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_BLENDVPS_VpsWps
asm("blendvpd %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_BLENDVPD_VpdWpd
asm("pmovsxbw %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVSXBW_VdqWq
asm("pmovsxbd %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVSXBD_VdqWd
asm("pmovsxbq %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVSXBQ_VdqWw
asm("pmovsxwd %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVSXWD_VdqWq
asm("pmovsxwq %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVSXWQ_VdqWd
asm("pmovsxdq %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVSXDQ_VdqWq
asm("pmovzxbw %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVZXBW_VdqWq
asm("pmovzxbd %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVZXBD_VdqWd
asm("pmovzxbq %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVZXBQ_VdqWw
asm("pmovzxwd %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVZXWD_VdqWq
asm("pmovzxwq %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVZXWQ_VdqWd
asm("pmovzxdq %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMOVZXDQ_VdqWq
asm("ptest %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PTEST_VdqWdq
asm("pmuldq %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMULDQ_VdqWdq
asm("pcmpeqq %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PCMPEQQ_VdqWdq
asm("packusdw %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PACKUSDW_VdqWdq
asm("pminsb %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMINSB_VdqWdq
asm("pminsd %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMINSD_VdqWdq
asm("pminuw %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMINUW_VdqWdq
asm("pminud %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMINUD_VdqWdq
asm("pmaxsb %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMAXSB_VdqWdq
asm("pmaxsd %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMAXSD_VdqWdq
asm("pmaxuw %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMAXUW_VdqWdq
asm("pmaxud %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMAXUD_VdqWdq
asm("pmulld %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PMULLD_VdqWdq
asm("phminposuw %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PHMINPOSUW_VdqWdq
asm("roundps $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_ROUNDPS_VpsWpsIb
asm("roundpd $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_ROUNDPD_VpdWpdIb
asm("roundss $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_ROUNDSS_VssWssIb
asm("roundsd $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_ROUNDSD_VsdWsdIb
asm("blendps $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_BLENDPS_VpsWpsIb
asm("blendpd $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_BLENDPD_VpdWpdIb
asm("pblendw $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_PBLENDW_VdqWdqIb
asm("pextrb $0x70, %xmm0, %rbx"); 	//BX_ISA_SSE4_1	_PEXTRB_EbdVdqIb
asm("pextrw $0x70, %xmm0, %rbx"); 	//BX_ISA_SSE4_1	_PEXTRW_EwdVdqIb
asm("pextrd $0x70, %xmm0, %ebx"); 	//BX_ISA_SSE4_1	_PEXTRD_EdVdqIb
asm("pextrq $0x70, %xmm0, %rbx"); 	//BX_ISA_SSE4_1	_PEXTRQ_EqVdqIb
asm("extractps $0x70, %xmm0, %ebx"); 	//BX_ISA_SSE4_1	_EXTRACTPS_EdVpsIb
asm("pinsrb $0x70, %ebx, %xmm0"); 	//BX_ISA_SSE4_1	_PINSRB_VdqEbIb
asm("insertps $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_INSERTPS_VpsWssIb
asm("pinsrd $0x70, %ebx, %xmm0"); 	//BX_ISA_SSE4_1	_PINSRD_VdqEdIb
asm("pinsrq $0x70, %rbx, %xmm0"); 	//BX_ISA_SSE4_1	_PINSRQ_VdqEqIb
asm("dpps $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_DPPS_VpsWpsIb
asm("dppd $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_DPPD_VpdWpdIb
asm("mpsadbw $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_1	_MPSADBW_VdqWdqIb
asm("movntdqa (%rsi), %xmm0"); 	//BX_ISA_SSE4_1	_MOVNTDQA_VdqMdq
asm("crc32 %bl, %ebx"); 	//BX_ISA_SSE4_2	_CRC32_GdEb
asm("crc32 %bx, %ebx"); 	//BX_ISA_SSE4_2	_CRC32_GdEw
asm("crc32 %ebx, %ebx"); 	//BX_ISA_SSE4_2	_CRC32_GdEd
asm("crc32 %rbx, %rbx"); 	//BX_ISA_SSE4_2	_CRC32_GdEq
asm("pcmpgtq %xmm0, %xmm0"); 	//BX_ISA_SSE4_2	_PCMPGTQ_VdqWdq
asm("pcmpestrm $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_2	_PCMPESTRM_VdqWdqIb
asm("pcmpestri $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_2	_PCMPESTRI_VdqWdqIb
asm("pcmpistrm $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_2	_PCMPISTRM_VdqWdqIb
asm("pcmpistri $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4_2	_PCMPISTRI_VdqWdqIb
asm("movbe (%rsi), %bx"); 	//BX_ISA_MOVBE	_MOVBE_GwMw
asm("movbe (%rsi), %ebx"); 	//BX_ISA_MOVBE	_MOVBE_GdMd
asm("movbe (%rsi), %rbx"); 	//BX_ISA_MOVBE	_MOVBE_GqMq
asm("movbe %bx, (%rsi)"); 	//BX_ISA_MOVBE	_MOVBE_MwGw
asm("movbe %ebx, (%rsi)"); 	//BX_ISA_MOVBE	_MOVBE_MdGd
asm("movbe %rbx, (%rsi)"); 	//BX_ISA_MOVBE	_MOVBE_MqGq
asm("popcnt %ebx, %ebx"); 	//BX_ISA_SSE4_2	_POPCNT_GdEd
asm("popcnt %bx, %bx"); 	//BX_ISA_SSE4_2	_POPCNT_GwEw
asm("popcnt %rbx, %rbx"); 	//BX_ISA_SSE4_2	_POPCNT_GqEq

asm("mov %0, %%rdi"::"m"(mem_addr_int):);
asm("mov %0, %%rsi"::"m"(mem_addr_int):);
asm("and $0xffffffffffffffc0, %rdi");
asm("xsave (%rdi)"); 	//BX_ISA_XSAVE	_XSAVE
asm("xrstor (%rdi)"); 	//BX_ISA_XSAVE	_XRSTOR
asm("xsavec (%rdi)"); 	//BX_ISA_XSAVEC	_XSAVEC
asm("xrstor (%rdi)"); 	//BX_ISA_XSAVE	_XRSTOR
// CPL0 asm("xsetbv"); 	//BX_ISA_XSAVE	_XSETBV
// CPL0 asm("xgetbv"); 	//BX_ISA_XSAVE	_XGETBV
asm("xsaveopt (%rdi)"); 	//BX_ISA_XSAVEOPT	_XSAVEOPT
asm("xrstor (%rdi)"); 	//BX_ISA_XSAVE	_XRSTOR
// CPL0 asm("xsaves (%rdi)"); 	//BX_ISA_XSAVES	_XSAVES
// CPL0 asm("xrstors (%rsi)"); 	//BX_ISA_XSAVES	_XRSTORS
asm("aesimc %xmm0, %xmm0"); 	//BX_ISA_AES_PCLMULQDQ	_AESIMC_VdqWdq
asm("aeskeygenassist $0x70, %xmm0, %xmm0"); 	//BX_ISA_AES_PCLMULQDQ	_AESKEYGENASSIST_VdqWdqIb
asm("aesenc %xmm0, %xmm0"); 	//BX_ISA_AES_PCLMULQDQ	_AESENC_VdqWdq
asm("aesenclast %xmm0, %xmm0"); 	//BX_ISA_AES_PCLMULQDQ	_AESENCLAST_VdqWdq
asm("aesdec %xmm0, %xmm0"); 	//BX_ISA_AES_PCLMULQDQ	_AESDEC_VdqWdq
asm("aesdeclast %xmm0, %xmm0"); 	//BX_ISA_AES_PCLMULQDQ	_AESDECLAST_VdqWdq
asm("pclmulqdq $0x70, %xmm0, %xmm0"); 	//BX_ISA_AES_PCLMULQDQ	_PCLMULQDQ_VdqWdqIb
// UD asm("sha1nexte %xmm0, %xmm0"); 	//BX_ISA_SHA	_SHA1NEXTE_VdqWdq
// UD asm("sha1msg1 %xmm0, %xmm0"); 	//BX_ISA_SHA	_SHA1MSG1_VdqWdq
// UD asm("sha1msg2 %xmm0, %xmm0"); 	//BX_ISA_SHA	_SHA1MSG2_VdqWdq
// UD asm("sha256rnds2 %xmm0, %xmm0"); 	//BX_ISA_SHA	_SHA256RNDS2_VdqWdq
// UD asm("sha256msg1 %xmm0, %xmm0"); 	//BX_ISA_SHA	_SHA256MSG1_VdqWdq
// UD asm("sha256msg2 %xmm0, %xmm0"); 	//BX_ISA_SHA	_SHA256MSG2_VdqWdq
// UD asm("sha1rnds4 $0x70, %xmm0, %xmm0"); 	//BX_ISA_SHA	_SHA1RNDS4_VdqWdqIb
// NI asm("gf2p8affineqb $0x70, %xmm0, %xmm0"); 	//BX_ISA_GFNI	_GF2P8AFFINEQB_VdqWdqIb
// NI asm("gf2p8affineinvqb $0x70, %xmm0, %xmm0"); 	//BX_ISA_GFNI	_GF2P8AFFINEINVQB_VdqWdqIb
// NI asm("gf2p8mulb %xmm0, %xmm0"); 	//BX_ISA_GFNI	_GF2P8MULB_VdqWdq
asm("lahf");
//BX_IA_LAHF_LM,BX_ISA_LM_LAHF_SAHF,BX_SUPPORT_X86_64,Y,,25,

asm("sahf");
//BX_IA_SAHF_LM,BX_ISA_LM_LAHF_SAHF,BX_SUPPORT_X86_64,Y,,25,

asm("syscall"); 	//0	_SYSCALL
// CPL0 asm("sysret"); 	//0	_SYSRET
asm("add %rbx, %rbx"); 	//0	_ADD_GqEq
asm("or %rbx, %rbx"); 	//0	_OR_GqEq
asm("adc %rbx, %rbx"); 	//0	_ADC_GqEq
asm("sbb %rbx, %rbx"); 	//0	_SBB_GqEq
asm("and %rbx, %rbx"); 	//0	_AND_GqEq
asm("sub %rbx, %rbx"); 	//0	_SUB_GqEq
asm("xor %rbx, %rbx"); 	//0	_XOR_GqEq
asm("cmp %rbx, %rbx"); 	//0	_CMP_GqEq
asm("add %rbx, %rbx"); 	//0	_ADD_EqGq
asm("or %rbx, %rbx"); 	//0	_OR_EqGq
asm("adc %rbx, %rbx"); 	//0	_ADC_EqGq
asm("sbb %rbx, %rbx"); 	//0	_SBB_EqGq
asm("and %rbx, %rbx"); 	//0	_AND_EqGq
asm("sub %rbx, %rbx"); 	//0	_SUB_EqGq
asm("xor %rbx, %rbx"); 	//0	_XOR_EqGq
asm("test %rbx, %rbx"); 	//0	_TEST_EqGq
asm("cmp %rbx, %rbx"); 	//0	_CMP_EqGq
asm("add $0x70000000, %rax"); 	//0	_ADD_RAXId
asm("or $0x70000000, %rax"); 	//0	_OR_RAXId
asm("adc $0x70000000, %rax"); 	//0	_ADC_RAXId
asm("sbb $0x70000000, %rax"); 	//0	_SBB_RAXId
asm("and $0x70000000, %rax"); 	//0	_AND_RAXId
asm("sub $0x70000000, %rax"); 	//0	_SUB_RAXId
asm("xor $0x70000000, %rax"); 	//0	_XOR_RAXId
asm("test $0x70000000, %rax"); 	//0	_TEST_RAXId
asm("cmp $0x70000000, %rax"); 	//0	_CMP_RAXId
asm("add $0x70000000, %rbx"); 	//0	_ADD_EqId
asm("or $0x70000000, %rbx"); 	//0	_OR_EqId
asm("adc $0x70000000, %rbx"); 	//0	_ADC_EqId
asm("sbb $0x70000000, %rbx"); 	//0	_SBB_EqId
asm("and $0x70000000, %rbx"); 	//0	_AND_EqId
asm("sub $0x70000000, %rbx"); 	//0	_SUB_EqId
asm("xor $0x70000000, %rbx"); 	//0	_XOR_EqId
asm("test $0x70000000, %rbx"); 	//0	_TEST_EqId
asm("cmp $0x70000000, %rbx"); 	//0	_CMP_EqId
asm("xchg %rbx, %rbx"); 	//0	_XCHG_EqGq
asm("xchg %rbx, %rax"); 	//0	_XCHG_RRXRAX
asm("lea (%rsi), %rbx"); 	//0	_LEA_GqM
asm("mov %ebx, %ebx"); 	//0	_MOV_Op64_GdEd
asm("mov %ebx, %ebx"); 	//0	_MOV_Op64_EdGd
asm("mov %rbx, %rbx"); 	//0	_MOV_GqEq
asm("mov %rbx, %rbx"); 	//0	_MOV_EqGq
asm("mov $0x70000000, %rbx"); 	//0	_MOV_EqId
// CE asm("mov %ds:var, %rax"); 	//0	_MOV_RAXOq
// CE asm("mov %rax, %ds:var"); 	//0	_MOV_OqRAX
// CE asm("mov %ds:var, %eax"); 	//0	_MOV_EAXOq
// CE asm("mov %eax, %ds:var"); 	//0	_MOV_OqEAX
// CE asm("mov %ds:var, %ax"); 	//0	_MOV_AXOq
// CE asm("mov %ax, %ds:var"); 	//0	_MOV_OqAX
// CE asm("mov %ds:var, %al"); 	//0	_MOV_ALOq
// CE asm("mov %al, %ds:var"); 	//0	_MOV_OqAL

asm("mov %0, %%rdi"::"m"(mem_addr_int):);
asm("mov %0, %%rsi"::"m"(mem_addr_int):);
asm("mov $3, %rcx");
asm("rep movsq"); 	//0	_REP_MOVSQ_YqXq
asm("rep cmpsq"); 	//0	_REP_CMPSQ_XqYq
asm("rep stosq"); 	//0	_REP_STOSQ_YqRAX
asm("rep lodsq"); 	//0	_REP_LODSQ_RAXXq
asm("rep scasq"); 	//0	_REP_SCASQ_RAXYq
asm("call call_Jq \n\t call_Jq:\n\t"); 	//0	_CALL_Jq
asm("jmp jmp_Jq \n\t jmp_Jq:\n\t"); 	//0	_JMP_Jq
asm("jo jo_Jq \n\t jo_Jq:\n\t"); 	//0	_JO_Jq
asm("jno jno_Jq \n\t jno_Jq:\n\t"); 	//0	_JNO_Jq
asm("jb jb_Jq \n\t jb_Jq:\n\t"); 	//0	_JB_Jq
asm("jnb jnb_Jq \n\t jnb_Jq:\n\t"); 	//0	_JNB_Jq
asm("jz jz_Jq \n\t jz_Jq:\n\t"); 	//0	_JZ_Jq
asm("jnz jnz_Jq \n\t jnz_Jq:\n\t"); 	//0	_JNZ_Jq
asm("jbe jbe_Jq \n\t jbe_Jq:\n\t"); 	//0	_JBE_Jq
asm("jnbe jnbe_Jq \n\t jnbe_Jq:\n\t"); 	//0	_JNBE_Jq
asm("js js_Jq \n\t js_Jq:\n\t"); 	//0	_JS_Jq
asm("jns jns_Jq \n\t jns_Jq:\n\t"); 	//0	_JNS_Jq
asm("jp jp_Jq \n\t jp_Jq:\n\t"); 	//0	_JP_Jq
asm("jnp jnp_Jq \n\t jnp_Jq:\n\t"); 	//0	_JNP_Jq
asm("jl jl_Jq \n\t jl_Jq:\n\t"); 	//0	_JL_Jq
asm("jnl jnl_Jq \n\t jnl_Jq:\n\t"); 	//0	_JNL_Jq
asm("jle jle_Jq \n\t jle_Jq:\n\t"); 	//0	_JLE_Jq
asm("jnle jnle_Jq \n\t jnle_Jq:\n\t"); 	//0	_JNLE_Jq
// RT asm("enter $0x1000, $0"); 	//0	_ENTER_Op64_IwIb
// RT asm("leave"); 	//0	_LEAVE_Op64
// CPL0 asm("iret"); 	//0	_IRET_Op64
asm("shld %rbx, %rbx"); 	//0	_SHLD_EqGq
asm("shld $0x70, %rbx, %rbx"); 	//0	_SHLD_EqGqIb
asm("shrd %rbx, %rbx"); 	//0	_SHRD_EqGq
asm("shrd $0x70, %rbx, %rbx"); 	//0	_SHRD_EqGqIb
asm("imul %rbx, %rbx"); 	//0	_IMUL_GqEq
asm("imul $0x70000000, %rbx, %rbx"); 	//0	_IMUL_GqEqId
asm("movzx %bl, %rbx"); 	//0	_MOVZX_GqEb
asm("movzx %bx, %rbx"); 	//0	_MOVZX_GqEw
asm("movsx %bl, %rbx"); 	//0	_MOVSX_GqEb
asm("movsx %bx, %rbx"); 	//0	_MOVSX_GqEw
asm("movsxd %ebx, %rbx"); 	//0	_MOVSXD_GqEd
asm("bswap %rax");
//BX_IA_BSWAP_RRX,0,BX_SUPPORT_X86_64,Y,,2190,

asm("bsf %rbx, %rbx"); 	//0	_BSF_GqEq
asm("bsr %rbx, %rbx"); 	//0	_BSR_GqEq
asm("bt %rbx, %rbx"); 	//0	_BT_EqGq
asm("bts %rbx, %rbx"); 	//0	_BTS_EqGq
asm("btr %rbx, %rbx"); 	//0	_BTR_EqGq
asm("btc %rbx, %rbx"); 	//0	_BTC_EqGq
asm("bt $0x70, %rbx"); 	//0	_BT_EqIb
asm("bts $0x70, %rbx"); 	//0	_BTS_EqIb
asm("btr $0x70, %rbx"); 	//0	_BTR_EqIb
asm("btc $0x70, %rbx"); 	//0	_BTC_EqIb
asm("not %rbx"); 	//0	_NOT_Eq
asm("neg %rbx"); 	//0	_NEG_Eq
asm("rol %cl, %rbx"); 	//0	_ROL_Eq
asm("ror %cl, %rbx"); 	//0	_ROR_Eq
asm("rcl %cl, %rbx"); 	//0	_RCL_Eq
asm("rcr %cl, %rbx"); 	//0	_RCR_Eq
asm("shl %cl, %rbx"); 	//0	_SHL_Eq
asm("shr %cl, %rbx"); 	//0	_SHR_Eq
asm("sar %cl, %rbx"); 	//0	_SAR_Eq
asm("rol $0x70, %rbx"); 	//0	_ROL_EqIb
asm("ror $0x70, %rbx"); 	//0	_ROR_EqIb
asm("rcl $0x70, %rbx"); 	//0	_RCL_EqIb
asm("rcr $0x70, %rbx"); 	//0	_RCR_EqIb
asm("shl $0x70, %rbx"); 	//0	_SHL_EqIb
asm("shr $0x70, %rbx"); 	//0	_SHR_EqIb
asm("sar $0x70, %rbx"); 	//0	_SAR_EqIb

asm("mov $1, %rax");
asm("mov $1, %rbx");
asm("mul %rbx"); 	//0	_MUL_RAXEq
asm("imul %rbx, %rax"); 	//0	_IMUL_RAXEq
asm("div %rbx, %rax"); 	//0	_DIV_RAXEq
asm("idiv %rbx, %rax"); 	//0	_IDIV_RAXEq
asm("inc %rbx"); 	//0	_INC_Eq
asm("dec %rbx"); 	//0	_DEC_Eq
asm("mov %0, %%rbx"::"m"(inner_call_ptr):);
asm("call *%rbx"); 	//0	_CALL_Eq
asm("mov %0, %%rdi"::"m"(mem_addr_int):);
asm("mov %0, %%rsi"::"m"(mem_addr_int):);
asm("mov %rbx, (%rdi)");
asm("call *%cs:(%rdi)"); 	//0	_CALLF_Op64_Ep
asm("movabsq $jmpq_next, %rbx \n\t"
	"jmp *%rbx \n\t"
	"jmpq_next: \n\t"); 	//0	_JMP_Eq
asm("movabsq $jmpq1_next, %rax \n\t"
	"mov %rax, (%rdi) \n\t"
	"jmp *%cs:(%rdi) \n\t"
	"jmpq1_next: \n\t"); 	//0	_JMPF_Op64_Ep
asm("pushf"); 	//0	_PUSHF_Fq
asm("popf"); 	//0	_POPF_Fq
asm("cmpxchg %rbx, %rbx"); 	//0	_CMPXCHG_EqGq
asm("cdqe"); 	//0	_CDQE
asm("cqo"); 	//0	_CQO
asm("xadd %rbx, %rbx"); 	//0	_XADD_EqGq
// RT asm("ret $0x7000"); 	//0	_RET_Op64_Iw
// RT asm("ret"); 	//0	_RET_Op64
// RT asm("retf $0x7000"); 	//0	_RETF_Op64_Iw
// RT asm("retf"); 	//0	_RETF_Op64
asm("cmovo %rbx, %rbx"); 	//0	_CMOVO_GqEq
asm("cmovno %rbx, %rbx"); 	//0	_CMOVNO_GqEq
asm("cmovb %rbx, %rbx"); 	//0	_CMOVB_GqEq
asm("cmovnb %rbx, %rbx"); 	//0	_CMOVNB_GqEq
asm("cmovz %rbx, %rbx"); 	//0	_CMOVZ_GqEq
asm("cmovnz %rbx, %rbx"); 	//0	_CMOVNZ_GqEq
asm("cmovbe %rbx, %rbx"); 	//0	_CMOVBE_GqEq
asm("cmovnbe %rbx, %rbx"); 	//0	_CMOVNBE_GqEq
asm("cmovs %rbx, %rbx"); 	//0	_CMOVS_GqEq
asm("cmovns %rbx, %rbx"); 	//0	_CMOVNS_GqEq
asm("cmovp %rbx, %rbx"); 	//0	_CMOVP_GqEq
asm("cmovnp %rbx, %rbx"); 	//0	_CMOVNP_GqEq
asm("cmovl %rbx, %rbx"); 	//0	_CMOVL_GqEq
asm("cmovnl %rbx, %rbx"); 	//0	_CMOVNL_GqEq
asm("cmovle %rbx, %rbx"); 	//0	_CMOVLE_GqEq
asm("cmovnle %rbx, %rbx"); 	//0	_CMOVNLE_GqEq
asm("push %rbx"); 	//0	_PUSH_Eq
asm("pop %rbx"); 	//0	_POP_Eq
asm("push $0x70000000"); 	//0	_PUSH_Op64_Id
asm("pop %rbx"); 	//0	_POP_Eq
// ??? asm("push "); 	//0	_PUSH_Op64_Sw
// ??? asm("pop "); 	//0	_POP_Op64_Sw
asm("sgdt (%rsi)"); 	//0	_SGDT_Op64_Ms
asm("sidt (%rsi)"); 	//0	_SIDT_Op64_Ms
// CPL0 asm("lgdt (%rsi)"); 	//0	_LGDT_Op64_Ms
// CPL0 asm("lidt (%rsi)"); 	//0	_LIDT_Op64_Ms
asm("mov $0x7000000000, %rax");
//BX_IA_MOV_RRXIq,0,BX_SUPPORT_X86_64,Y,,2237346,

// CPL0 asm("lss (%rsi), %rbx"); 	//0	_LSS_GqMp
// CPL0 asm("lfs (%rsi), %rbx"); 	//0	_LFS_GqMp
// CPL0 asm("lgs (%rsi), %rbx"); 	//0	_LGS_GqMp

asm("mov %0, %%rdi"::"m"(mem_addr_int):);
asm("mov %0, %%rsi"::"m"(mem_addr_int):);

asm("cmpxchg16b (%rdi)"); 	//BX_ISA_CMPXCHG16B	_CMPXCHG16B
asm("mov $3, %rcx");
asm("loopne LOOPNE_Jb \n\t LOOPNE_Jb:\n\t"); 	//0	_LOOPNE_Op64_Jb
asm("mov $3, %rcx");
asm("loope LOOPE_Jb \n\t LOOPE_Jb:\n\t"); 	//0	_LOOPE_Op64_Jb
asm("mov $3, %rcx");
asm("loop LOOP_Jb \n\t LOOP_Jb:\n\t"); 	//0	_LOOP_Op64_Jb
asm("jrcxz jrcxz_Jb \n\t jrcxz_Jb:\n\t"); 	//0	_JRCXZ_Jb
asm("movq (%rdi), %rbx"); 	//0	_MOVQ_EqVq
asm("movq %rbx, %mm0"); 	//0	_MOVQ_PqEq
asm("movq %rbx, %xmm0"); 	//0	_MOVQ_VdqEq
asm("cvtsi2ss %rbx, %xmm0"); 	//0	_CVTSI2SS_VssEq
asm("cvtsi2sd %rbx, %xmm0"); 	//0	_CVTSI2SD_VsdEq
asm("cvttss2si %xmm0, %rbx"); 	//0	_CVTTSS2SI_GqWss
asm("cvttsd2si %xmm0, %rbx"); 	//0	_CVTTSD2SI_GqWsd
asm("cvtss2si %xmm0, %rbx"); 	//0	_CVTSS2SI_GqWss
asm("cvtsd2si %xmm0, %rbx"); 	//0	_CVTSD2SI_GqWsd
asm("movnti %ebx, (%rsi)"); 	//BX_ISA_SSE2	_MOVNTI_Op64_MdGd
asm("movnti %rbx, (%rsi)"); 	//BX_ISA_SSE2	_MOVNTI_MqGq
// CPL0 asm("mov %rbx, %cr0"); 	//0	_MOV_CR0Rq
// CPL0 asm("mov %rbx, %cr2"); 	//0	_MOV_CR2Rq
// CPL0 asm("mov %rbx, %cr3"); 	//0	_MOV_CR3Rq
// CPL0 asm("mov %rbx, %cr4"); 	//0	_MOV_CR4Rq
// CPL0 asm("mov %cr0, %rbx"); 	//0	_MOV_RqCR0
// CPL0 asm("mov %cr2, %rbx"); 	//0	_MOV_RqCR2
// CPL0 asm("mov %cr3, %rbx"); 	//0	_MOV_RqCR3
// CPL0 asm("mov %cr4, %rbx"); 	//0	_MOV_RqCR4
// CPL0 asm("mov %rbx, %db0"); 	//0	_MOV_DqRq
// CPL0 asm("mov %db0, %rbx"); 	//0	_MOV_RqDq
// CPL0 asm("swapgs"); 	//0	_SWAPGS

asm("mov %rsi, %rbx");
asm("xlat"); 	//0	_XLAT
// UD asm("rdfsbase %ebx"); 	//BX_ISA_FSGSBASE	_RDFSBASE_Ed
// UD asm("rdgsbase %ebx"); 	//BX_ISA_FSGSBASE	_RDGSBASE_Ed
// UD asm("rdfsbase %rbx"); 	//BX_ISA_FSGSBASE	_RDFSBASE_Eq
// UD asm("rdgsbase %rbx"); 	//BX_ISA_FSGSBASE	_RDGSBASE_Eq
// UD asm("wrfsbase %ebx"); 	//BX_ISA_FSGSBASE	_WRFSBASE_Ed
// UD asm("wrgsbase %ebx"); 	//BX_ISA_FSGSBASE	_WRGSBASE_Ed
// UD asm("wrfsbase %rbx"); 	//BX_ISA_FSGSBASE	_WRFSBASE_Eq
// UD asm("wrgsbase %rbx"); 	//BX_ISA_FSGSBASE	_WRGSBASE_Eq
asm("rdtscp"); 	//BX_ISA_RDTSCP	_RDTSCP
// VMX asm("vmxon (%rsi)"); 	//BX_ISA_VMX	_VMXON_Mq
// VMX asm("vmxoff"); 	//BX_ISA_VMX	_VMXOFF
// VMX asm("vmcall"); 	//BX_ISA_VMX	_VMCALL
// VMX asm("vmlaunch"); 	//BX_ISA_VMX	_VMLAUNCH
// VMX asm("vmresume"); 	//BX_ISA_VMX	_VMRESUME
// VMX asm("vmclear (%rsi)"); 	//BX_ISA_VMX	_VMCLEAR_Mq
// VMX asm("vmptrld (%rsi)"); 	//BX_ISA_VMX	_VMPTRLD_Mq
// VMX asm("vmptrst (%rsi)"); 	//BX_ISA_VMX	_VMPTRST_Mq
// VMX 32 bit asm("vmread %ebx, %ebx"); 	//BX_ISA_VMX	_VMREAD_EdGd
// VMX 32 bit asm("vmwrite %ebx, %ebx"); 	//BX_ISA_VMX	_VMWRITE_GdEd
// VMX asm("vmread %rbx, %rbx"); 	//BX_ISA_VMX	_VMREAD_EqGq
// VMX asm("vmwrite %rbx, %rbx"); 	//BX_ISA_VMX	_VMWRITE_GqEq
// VMX asm("invept (%rdi), %rax"); 	//BX_ISA_VMX	_INVEPT
// CPL0 asm("invvpid (%rdi), %rax"); 	//BX_ISA_VMX	_INVVPID
// VMX asm("vmfunc"); 	//BX_ISA_VMX	_VMFUNC
// SMX asm("getsec"); 	//BX_ISA_SMX	_GETSEC
// AMD asm("vmrun"); 	//BX_ISA_SVM	_VMRUN
// AMD asm("vmmcall"); 	//BX_ISA_SVM	_VMMCALL
// AMD asm("vmload"); 	//BX_ISA_SVM	_VMLOAD
// AMD asm("vmsave"); 	//BX_ISA_SVM	_VMSAVE
// AMD asm("stgi"); 	//BX_ISA_SVM	_STGI
// AMD asm("clgi"); 	//BX_ISA_SVM	_CLGI
// AMD asm("skinit"); 	//BX_ISA_SVM	_SKINIT
// AMD asm("invlpga"); 	//BX_ISA_SVM	_INVLPGA
// CPL0 asm("invpcid (%rdi), %rax"); 	//BX_ISA_INVPCID	_INVPCID
// UD asm("rdpkru"); 	//BX_ISA_PKU	_RDPKRU
// UD asm("wrpkru"); 	//BX_ISA_PKU	_WRPKRU
// UD asm("rdpid %rbx"); 	//BX_ISA_RDPID	_RDPID_Ed
asm("vzeroupper"); 	//BX_ISA_AVX	_VZEROUPPER
asm("vzeroall"); 	//BX_ISA_AVX	_VZEROALL
asm("vstmxcsr (%rdi)"); 	//BX_ISA_AVX	_VSTMXCSR
asm("vldmxcsr (%rdi)"); 	//BX_ISA_AVX	_VLDMXCSR
asm("vmovaps %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVAPS_VpsWps
asm("vmovaps %ymm0, %ymm0"); 	//BX_ISA_AVX	_V256_VMOVAPS_VpsWps
asm("vmovaps %xmm0, (%rdi)"); 	//BX_ISA_AVX	_V128_VMOVAPS_WpsVps
asm("vmovaps %ymm0, (%rdi)"); 	//BX_ISA_AVX	_V256_VMOVAPS_WpsVps
asm("vmovapd %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVAPD_VpdWpd
asm("vmovapd %ymm0, %ymm0"); 	//BX_ISA_AVX	_V256_VMOVAPD_VpdWpd
asm("vmovapd %xmm0, (%rdi)"); 	//BX_ISA_AVX	_V128_VMOVAPD_WpdVpd
asm("vmovapd %ymm0, (%rdi)"); 	//BX_ISA_AVX	_V256_VMOVAPD_WpdVpd
asm("vmovups %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVUPS_VpsWps
asm("vmovups %ymm0, %ymm0"); 	//BX_ISA_AVX	_V256_VMOVUPS_VpsWps
asm("vmovups %xmm0, (%rdi)"); 	//BX_ISA_AVX	_V128_VMOVUPS_WpsVps
asm("vmovups %ymm0, (%rdi)"); 	//BX_ISA_AVX	_V256_VMOVUPS_WpsVps
asm("vmovupd %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVUPD_VpdWpd
asm("vmovupd %ymm0, %ymm0"); 	//BX_ISA_AVX	_V256_VMOVUPD_VpdWpd
asm("vmovupd %xmm0, (%rdi)"); 	//BX_ISA_AVX	_V128_VMOVUPD_WpdVpd
asm("vmovupd %ymm0, (%rdi)"); 	//BX_ISA_AVX	_V256_VMOVUPD_WpdVpd
asm("vmovdqa %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVDQA_VdqWdq
asm("vmovdqa %xmm0, %xmm0"); 	//BX_ISA_AVX	_V256_VMOVDQA_VdqWdq
asm("vmovdqa %xmm0, (%rdi)"); 	//BX_ISA_AVX	_V128_VMOVDQA_WdqVdq
asm("vmovdqa %xmm0, (%rdi)"); 	//BX_ISA_AVX	_V256_VMOVDQA_WdqVdq
asm("vmovdqu %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVDQU_VdqWdq
asm("vmovdqu %xmm0, %xmm0"); 	//BX_ISA_AVX	_V256_VMOVDQU_VdqWdq
asm("vmovdqu %xmm0, (%rdi)"); 	//BX_ISA_AVX	_V128_VMOVDQU_WdqVdq
asm("vmovdqu %xmm0, (%rdi)"); 	//BX_ISA_AVX	_V256_VMOVDQU_WdqVdq
asm("vmovsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVSD_VsdHpdWsd
asm("vmovss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVSS_VssHpsWss
asm("vmovsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVSD_WsdHpdVsd
asm("vmovss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVSS_WssHpsVss
asm("vmovsd (%rsi), %xmm0"); 	//BX_ISA_AVX	_V128_VMOVSD_VsdWsd
asm("vmovss (%rsi), %xmm0"); 	//BX_ISA_AVX	_V128_VMOVSS_VssWss
asm("vmovsd %xmm0, (%rsi)"); 	//BX_ISA_AVX	_V128_VMOVSD_WsdVsd
asm("vmovss %xmm0, (%rsi)"); 	//BX_ISA_AVX	_V128_VMOVSS_WssVss
asm("vmovlps (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVLPS_VpsHpsMq
asm("vmovhps (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVHPS_VpsHpsMq
asm("vmovlps %xmm0, (%rsi)"); 	//BX_ISA_AVX	_V128_VMOVLPS_MqVps
asm("vmovhps %xmm0, (%rsi)"); 	//BX_ISA_AVX	_V128_VMOVHPS_MqVps
asm("vmovlpd %xmm0, (%rsi)"); 	//BX_ISA_AVX	_V128_VMOVLPD_MqVsd
asm("vmovhpd %xmm0, (%rsi)"); 	//BX_ISA_AVX	_V128_VMOVHPD_MqVsd
asm("vmovlpd (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVLPD_VpdHpdMq
asm("vmovhpd (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVHPD_VpdHpdMq
asm("vmovddup %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVDDUP_VpdWpd
asm("vmovddup %zmm0, %zmm0"); 	//BX_ISA_AVX	_V256_VMOVDDUP_VpdWpd
asm("vmovsldup %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMOVSLDUP_VpsWps
asm("vmovshdup %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMOVSHDUP_VpsWps
asm("vlddqu (%rsi), %xmm0"); 	//BX_ISA_AVX	_VLDDQU_VdqMdq
asm("vmovntdqa (%rsi), %xmm0"); 	//BX_ISA_AVX	_V128_VMOVNTDQA_VdqMdq
asm("vmovntdqa (%rsi), %zmm0"); 	//BX_ISA_AVX2	_V256_VMOVNTDQA_VdqMdq
asm("vmovntps %xmm0, (%rsi)"); 	//BX_ISA_AVX	_V128_VMOVNTPS_MpsVps
asm("vmovntps %ymm0, (%rsi)"); 	//BX_ISA_AVX	_V256_VMOVNTPS_MpsVps
asm("vmovntpd %xmm0, (%rsi)"); 	//BX_ISA_AVX	_V128_VMOVNTPD_MpdVpd
asm("vmovntpd %ymm0, (%rsi)"); 	//BX_ISA_AVX	_V256_VMOVNTPD_MpdVpd
asm("vmovntdq %xmm0, (%rsi)"); 	//BX_ISA_AVX	_V128_VMOVNTDQ_MdqVdq
asm("vmovntdq %ymm0, (%rsi)"); 	//BX_ISA_AVX	_V256_VMOVNTDQ_MdqVdq
asm("vucomiss %xmm0, %xmm0"); 	//BX_ISA_AVX	_VUCOMISS_VssWss
asm("vcomiss %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCOMISS_VssWss
asm("vucomisd %xmm0, %xmm0"); 	//BX_ISA_AVX	_VUCOMISD_VsdWsd
asm("vcomisd %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCOMISD_VsdWsd
asm("vrsqrtss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VRSQRTSS_VssHpsWss
asm("vrsqrtps %xmm0, %xmm0"); 	//BX_ISA_AVX	_VRSQRTPS_VpsWps
asm("vrcpss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VRCPSS_VssHpsWss
asm("vrcpps %xmm0, %xmm0"); 	//BX_ISA_AVX	_VRCPPS_VpsWps
asm("vandps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VANDPS_VpsHpsWps
asm("vandpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VANDPD_VpdHpdWpd
asm("vandnps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VANDNPS_VpsHpsWps
asm("vandnpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VANDNPD_VpdHpdWpd
asm("vorps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VORPS_VpsHpsWps
asm("vorpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VORPD_VpdHpdWpd
asm("vxorps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VXORPS_VpsHpsWps
asm("vxorpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VXORPD_VpdHpdWpd
asm("vpshufd $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSHUFD_VdqWdqIb
asm("vpshufd $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSHUFD_VdqWdqIb
asm("vpshufhw $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSHUFHW_VdqWdqIb
asm("vpshufhw $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSHUFHW_VdqWdqIb
asm("vpshuflw $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSHUFLW_VdqWdqIb
asm("vpshuflw $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSHUFLW_VdqWdqIb
asm("vhaddpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VHADDPD_VpdHpdWpd
asm("vhaddps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VHADDPS_VpsHpsWps
asm("vhsubpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VHSUBPD_VpdHpdWpd
asm("vhsubps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VHSUBPS_VpsHpsWps
asm("vshufps $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VSHUFPS_VpsHpsWpsIb
asm("vshufpd $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VSHUFPD_VpdHpdWpdIb
asm("vaddsubpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VADDSUBPD_VpdHpdWpd
asm("vaddsubps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VADDSUBPS_VpsHpsWps
asm("vroundps $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VROUNDPS_VpsWpsIb
asm("vroundpd $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VROUNDPD_VpdWpdIb
asm("vroundsd $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VROUNDSD_VsdHpdWsdIb
asm("vroundss $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VROUNDSS_VssHpsWssIb
asm("vdpps $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VDPPS_VpsHpsWpsIb
asm("vdppd $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VDPPD_VpdHpdWpdIb
asm("vaddps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VADDPS_VpsHpsWps
asm("vaddpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VADDPD_VpdHpdWpd
asm("vaddss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VADDSS_VssHpsWss
asm("vaddsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VADDSD_VsdHpdWsd
asm("vmulps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMULPS_VpsHpsWps
asm("vmulpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMULPD_VpdHpdWpd
asm("vmulss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMULSS_VssHpsWss
asm("vmulsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMULSD_VsdHpdWsd
asm("vsubps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VSUBPS_VpsHpsWps
asm("vsubpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VSUBPD_VpdHpdWpd
asm("vsubss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VSUBSS_VssHpsWss
asm("vsubsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VSUBSD_VsdHpdWsd
asm("vdivps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VDIVPS_VpsHpsWps
asm("vdivpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VDIVPD_VpdHpdWpd
asm("vdivss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VDIVSS_VssHpsWss
asm("vdivsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VDIVSD_VsdHpdWsd
asm("vmaxps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMAXPS_VpsHpsWps
asm("vmaxpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMAXPD_VpdHpdWpd
asm("vmaxss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMAXSS_VssHpsWss
asm("vmaxsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMAXSD_VsdHpdWsd
asm("vminps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMINPS_VpsHpsWps
asm("vminpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMINPD_VpdHpdWpd
asm("vminss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMINSS_VssHpsWss
asm("vminsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMINSD_VsdHpdWsd
asm("vsqrtps %xmm0, %xmm0"); 	//BX_ISA_AVX	_VSQRTPS_VpsWps
asm("vsqrtpd %xmm0, %xmm0"); 	//BX_ISA_AVX	_VSQRTPD_VpdWpd
asm("vsqrtss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VSQRTSS_VssHpsWss
asm("vsqrtsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VSQRTSD_VsdHpdWsd
asm("vcmpps $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCMPPS_VpsHpsWpsIb
asm("vcmppd $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCMPPD_VpdHpdWpdIb
asm("vcmpss $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCMPSS_VssHpsWssIb
asm("vcmpsd $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCMPSD_VsdHpdWsdIb
asm("vpsrlw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSRLW_VdqHdqWdq
asm("vpsrlw %xmm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSRLW_VdqHdqWdq
asm("vpsrld %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSRLD_VdqHdqWdq
asm("vpsrld %xmm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSRLD_VdqHdqWdq
asm("vpsrlq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSRLQ_VdqHdqWdq
asm("vpsrlq %xmm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSRLQ_VdqHdqWdq
asm("vpsraw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSRAW_VdqHdqWdq
asm("vpsraw %xmm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSRAW_VdqHdqWdq
asm("vpsrad %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSRAD_VdqHdqWdq
asm("vpsrad %xmm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSRAD_VdqHdqWdq
asm("vpsllw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSLLW_VdqHdqWdq
asm("vpsllw %xmm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSLLW_VdqHdqWdq
asm("vpslld %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSLLD_VdqHdqWdq
asm("vpslld %xmm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSLLD_VdqHdqWdq
asm("vpsllq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSLLQ_VdqHdqWdq
asm("vpsllq %xmm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSLLQ_VdqHdqWdq

asm("vpsrlw $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSRLW_UdqIb
asm("vpsrlw $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSRLW_UdqIb
asm("vpsraw $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSRAW_UdqIb
asm("vpsraw $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSRAW_UdqIb
asm("vpsllw $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSLLW_UdqIb
asm("vpsllw $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSLLW_UdqIb
asm("vpsrld $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSRLD_UdqIb
asm("vpsrld $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSRLD_UdqIb
asm("vpsrad $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSRAD_UdqIb
asm("vpsrad $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSRAD_UdqIb
asm("vpslld $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSLLD_UdqIb
asm("vpslld $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSLLD_UdqIb
asm("vpsrlq $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSRLQ_UdqIb
asm("vpsrlq $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSRLQ_UdqIb
asm("vpsllq $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSLLQ_UdqIb
asm("vpsllq $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSLLQ_UdqIb
asm("vpsrldq $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSRLDQ_UdqIb
asm("vpsrldq $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSRLDQ_UdqIb
asm("vpslldq $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSLLDQ_UdqIb
asm("vpslldq $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSLLDQ_UdqIb

asm("vpmovmskb %xmm0, %ebx"); 	//BX_ISA_AVX	_V128_VPMOVMSKB_GdUdq
asm("vpmovmskb %ymm0, %ebx"); 	//BX_ISA_AVX2	_V256_VPMOVMSKB_GdUdq
asm("vmovmskps %xmm0, %ebx"); 	//BX_ISA_AVX	_VMOVMSKPS_GdUps
asm("vmovmskpd %xmm0, %ebx"); 	//BX_ISA_AVX	_VMOVMSKPD_GdUpd
asm("vunpcklpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VUNPCKLPD_VpdHpdWpd
asm("vunpckhpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VUNPCKHPD_VpdHpdWpd
asm("vunpcklps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VUNPCKLPS_VpsHpsWps
asm("vunpckhps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VUNPCKHPS_VpsHpsWps
asm("vpunpckhdq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPUNPCKHDQ_VdqHdqWdq
asm("vpunpckhdq %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPUNPCKHDQ_VdqHdqWdq
asm("vpunpckldq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPUNPCKLDQ_VdqHdqWdq
asm("vpunpckldq %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPUNPCKLDQ_VdqHdqWdq
asm("vpunpcklbw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPUNPCKLBW_VdqHdqWdq
asm("vpunpcklbw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPUNPCKLBW_VdqHdqWdq
asm("vpunpcklwd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPUNPCKLWD_VdqHdqWdq
asm("vpunpcklwd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPUNPCKLWD_VdqHdqWdq
asm("vpunpckhbw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPUNPCKHBW_VdqHdqWdq
asm("vpunpckhbw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPUNPCKHBW_VdqHdqWdq
asm("vpunpckhwd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPUNPCKHWD_VdqHdqWdq
asm("vpunpckhwd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPUNPCKHWD_VdqHdqWdq
asm("vpunpcklqdq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPUNPCKLQDQ_VdqHdqWdq
asm("vpunpcklqdq %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPUNPCKLQDQ_VdqHdqWdq
asm("vpunpckhqdq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPUNPCKHQDQ_VdqHdqWdq
asm("vpunpckhqdq %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPUNPCKHQDQ_VdqHdqWdq
asm("vpcmpeqb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPEQB_VdqHdqWdq
asm("vpcmpeqb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPCMPEQB_VdqHdqWdq
asm("vpcmpeqw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPEQW_VdqHdqWdq
asm("vpcmpeqw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPCMPEQW_VdqHdqWdq
asm("vpcmpeqd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPEQD_VdqHdqWdq
asm("vpcmpeqd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPCMPEQD_VdqHdqWdq
asm("vpcmpeqq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPEQQ_VdqHdqWdq
asm("vpcmpeqq %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPCMPEQQ_VdqHdqWdq
asm("vpcmpgtb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPGTB_VdqHdqWdq
asm("vpcmpgtb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPCMPGTB_VdqHdqWdq
asm("vpcmpgtw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPGTW_VdqHdqWdq
asm("vpcmpgtw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPCMPGTW_VdqHdqWdq
asm("vpcmpgtd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPGTD_VdqHdqWdq
asm("vpcmpgtd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPCMPGTD_VdqHdqWdq
asm("vpcmpgtq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPGTQ_VdqHdqWdq
asm("vpcmpgtq %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPCMPGTQ_VdqHdqWdq
asm("vpsubsb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSUBSB_VdqHdqWdq
asm("vpsubsb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSUBSB_VdqHdqWdq
asm("vpsubsw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSUBSW_VdqHdqWdq
asm("vpsubsw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSUBSW_VdqHdqWdq
asm("vpaddsb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPADDSB_VdqHdqWdq
asm("vpaddsb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPADDSB_VdqHdqWdq
asm("vpaddsw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPADDSW_VdqHdqWdq
asm("vpaddsw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPADDSW_VdqHdqWdq
asm("vpsubusb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSUBUSB_VdqHdqWdq
asm("vpsubusb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSUBUSB_VdqHdqWdq
asm("vpsubusw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSUBUSW_VdqHdqWdq
asm("vpsubusw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSUBUSW_VdqHdqWdq
asm("vpaddusb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPADDUSB_VdqHdqWdq
asm("vpaddusb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPADDUSB_VdqHdqWdq
asm("vpaddusw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPADDUSW_VdqHdqWdq
asm("vpaddusw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPADDUSW_VdqHdqWdq
asm("vpavgb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPAVGB_VdqWdq
asm("vpavgb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPAVGB_VdqWdq
asm("vpavgw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPAVGW_VdqWdq
asm("vpavgw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPAVGW_VdqWdq
asm("vpandn %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPANDN_VdqHdqWdq
asm("vpandn %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPANDN_VdqHdqWdq
asm("vpand %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPAND_VdqHdqWdq
asm("vpand %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPAND_VdqHdqWdq
asm("vpor %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPOR_VdqHdqWdq
asm("vpor %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPOR_VdqHdqWdq
asm("vpxor %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPXOR_VdqHdqWdq
asm("vpxor %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPXOR_VdqHdqWdq
asm("vpmulhrsw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMULHRSW_VdqHdqWdq
asm("vpmulhrsw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMULHRSW_VdqHdqWdq
asm("vpmuldq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMULDQ_VdqHdqWdq
asm("vpmuldq %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMULDQ_VdqHdqWdq
asm("vpmuludq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMULUDQ_VdqHdqWdq
asm("vpmuludq %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMULUDQ_VdqHdqWdq
asm("vpmulld %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMULLD_VdqHdqWdq
asm("vpmulld %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMULLD_VdqHdqWdq
asm("vpmullw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMULLW_VdqHdqWdq
asm("vpmullw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMULLW_VdqHdqWdq
asm("vpmulhw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMULHW_VdqHdqWdq
asm("vpmulhw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMULHW_VdqHdqWdq
asm("vpmulhuw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMULHUW_VdqHdqWdq
asm("vpmulhuw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMULHUW_VdqHdqWdq
asm("vpsadbw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSADBW_VdqHdqWdq
asm("vpsadbw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSADBW_VdqHdqWdq
asm("vmaskmovdqu %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMASKMOVDQU_VdqUdq
asm("vpsubb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSUBB_VdqHdqWdq
asm("vpsubb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSUBB_VdqHdqWdq
asm("vpsubw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSUBW_VdqHdqWdq
asm("vpsubw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSUBW_VdqHdqWdq
asm("vpsubd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSUBD_VdqHdqWdq
asm("vpsubd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSUBD_VdqHdqWdq
asm("vpsubq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSUBQ_VdqHdqWdq
asm("vpsubq %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSUBQ_VdqHdqWdq
asm("vpaddb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPADDB_VdqHdqWdq
asm("vpaddb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPADDB_VdqHdqWdq
asm("vpaddw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPADDW_VdqHdqWdq
asm("vpaddw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPADDW_VdqHdqWdq
asm("vpaddd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPADDD_VdqHdqWdq
asm("vpaddd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPADDD_VdqHdqWdq
asm("vpaddq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPADDQ_VdqHdqWdq
asm("vpaddq %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPADDQ_VdqHdqWdq
asm("vpshufb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSHUFB_VdqHdqWdq
asm("vpshufb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSHUFB_VdqHdqWdq
asm("vphaddw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPHADDW_VdqHdqWdq
asm("vphaddw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPHADDW_VdqHdqWdq
asm("vphaddd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPHADDD_VdqHdqWdq
asm("vphaddd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPHADDD_VdqHdqWdq
asm("vphsubw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPHSUBW_VdqHdqWdq
asm("vphsubw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPHSUBW_VdqHdqWdq
asm("vphsubd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPHSUBD_VdqHdqWdq
asm("vphsubd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPHSUBD_VdqHdqWdq
asm("vphaddsw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPHADDSW_VdqHdqWdq
asm("vphaddsw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPHADDSW_VdqHdqWdq
asm("vphsubsw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPHSUBSW_VdqHdqWdq
asm("vphsubsw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPHSUBSW_VdqHdqWdq
asm("vpmaddwd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMADDWD_VdqHdqWdq
asm("vpmaddwd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMADDWD_VdqHdqWdq
asm("vpmaddubsw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMADDUBSW_VdqHdqWdq
asm("vpmaddubsw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMADDUBSW_VdqHdqWdq
asm("vpsignb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSIGNB_VdqHdqWdq
asm("vpsignb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSIGNB_VdqHdqWdq
asm("vpsignw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSIGNW_VdqHdqWdq
asm("vpsignw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSIGNW_VdqHdqWdq
asm("vpsignd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPSIGND_VdqHdqWdq
asm("vpsignd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPSIGND_VdqHdqWdq
asm("vtestps %xmm0, %xmm0"); 	//BX_ISA_AVX	_VTESTPS_VpsWps
asm("vtestpd %xmm0, %xmm0"); 	//BX_ISA_AVX	_VTESTPD_VpdWpd
asm("vptest %xmm0, %xmm0"); 	//BX_ISA_AVX	_VPTEST_VdqWdq
asm("vbroadcastss (%rsi), %ymm0"); 	//BX_ISA_AVX	_VBROADCASTSS_VpsMss
asm("vbroadcastsd (%rsi), %ymm0"); 	//BX_ISA_AVX	_V256_VBROADCASTSD_VpdMsd
asm("vbroadcastf128 (%rsi), %ymm0"); 	//BX_ISA_AVX	_V256_VBROADCASTF128_VdqMdq
asm("vpabsb %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPABSB_VdqWdq
asm("vpabsb %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPABSB_VdqWdq
asm("vpabsw %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPABSW_VdqWdq
asm("vpabsw %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPABSW_VdqWdq
asm("vpabsd %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPABSD_VdqWdq
asm("vpabsd %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPABSD_VdqWdq
asm("vpacksswb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPACKSSWB_VdqHdqWdq
asm("vpacksswb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPACKSSWB_VdqHdqWdq
asm("vpackuswb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPACKUSWB_VdqHdqWdq
asm("vpackuswb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPACKUSWB_VdqHdqWdq
asm("vpackusdw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPACKUSDW_VdqHdqWdq
asm("vpackusdw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPACKUSDW_VdqHdqWdq
asm("vpackssdw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPACKSSDW_VdqHdqWdq
asm("vpackssdw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPACKSSDW_VdqHdqWdq
asm("vmaskmovps (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMASKMOVPS_VpsHpsMps
asm("vmaskmovpd (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX	_VMASKMOVPD_VpdHpdMpd
asm("vmaskmovps %xmm0, %xmm0, (%rsi)"); 	//BX_ISA_AVX	_VMASKMOVPS_MpsHpsVps
asm("vmaskmovpd %xmm0, %xmm0, (%rsi)"); 	//BX_ISA_AVX	_VMASKMOVPD_MpdHpdVpd
asm("vpmovsxbw %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVSXBW_VdqWq
asm("vpmovsxbd %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVSXBD_VdqWd
asm("vpmovsxbq %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVSXBQ_VdqWw
asm("vpmovsxwd %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVSXWD_VdqWq
asm("vpmovsxwq %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVSXWQ_VdqWd
asm("vpmovsxdq %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVSXDQ_VdqWq
asm("vpmovzxbw %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVZXBW_VdqWq
asm("vpmovzxbd %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVZXBD_VdqWd
asm("vpmovzxbq %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVZXBQ_VdqWw
asm("vpmovzxwd %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVZXWD_VdqWq
asm("vpmovzxwq %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVZXWQ_VdqWd
asm("vpmovzxdq %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMOVZXDQ_VdqWq
asm("vpminsb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMINSB_VdqHdqWdq
asm("vpminsb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMINSB_VdqHdqWdq
asm("vpminsw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMINSW_VdqHdqWdq
asm("vpminsw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMINSW_VdqHdqWdq
asm("vpminsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMINSD_VdqHdqWdq
asm("vpminsd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMINSD_VdqHdqWdq
asm("vpminub %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMINUB_VdqHdqWdq
asm("vpminub %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMINUB_VdqHdqWdq
asm("vpminuw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMINUW_VdqHdqWdq
asm("vpminuw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMINUW_VdqHdqWdq
asm("vpminud %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMINUD_VdqHdqWdq
asm("vpminud %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMINUD_VdqHdqWdq
asm("vpmaxsb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMAXSB_VdqHdqWdq
asm("vpmaxsb %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMAXSB_VdqHdqWdq
asm("vpmaxsw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMAXSW_VdqHdqWdq
asm("vpmaxsw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMAXSW_VdqHdqWdq
asm("vpmaxsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMAXSD_VdqHdqWdq
asm("vpmaxsd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMAXSD_VdqHdqWdq
asm("vpmaxub %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMAXUB_VdqHdqWdq
asm("vpmaxub %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMAXUB_VdqHdqWdq
asm("vpmaxuw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMAXUW_VdqHdqWdq
asm("vpmaxuw %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMAXUW_VdqHdqWdq
asm("vpmaxud %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPMAXUD_VdqHdqWdq
asm("vpmaxud %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMAXUD_VdqHdqWdq
asm("vphminposuw %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPHMINPOSUW_VdqWdq
asm("vpermilps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VPERMILPS_VpsHpsWps
asm("vpermilpd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VPERMILPD_VpdHpdWpd
asm("vpermilps $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VPERMILPS_VpsWpsIb
asm("vpermilpd $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VPERMILPD_VpdWpdIb
asm("vblendps $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VBLENDPS_VpsHpsWpsIb
asm("vblendpd $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VBLENDPD_VpdHpdWpdIb
asm("vpblendw $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPBLENDW_VdqHdqWdqIb
asm("vpblendw $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX2	_V256_VPBLENDW_VdqHdqWdqIb
asm("vpalignr $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPALIGNR_VdqHdqWdqIb
asm("vpalignr $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX2	_V256_VPALIGNR_VdqHdqWdqIb
asm("vinsertps $0x70, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VINSERTPS_VpsWssIb
asm("vextractps $0x70, %xmm0, %ebx"); 	//BX_ISA_AVX	_V128_VEXTRACTPS_EdVpsIb
asm("vperm2f128 $0x70, %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX	_V256_VPERM2F128_VdqHdqWdqIb
asm("vinsertf128 $0x70, %xmm0, %ymm0, %ymm0"); 	//BX_ISA_AVX	_V256_VINSERTF128_VdqHdqWdqIb
asm("vextractf128 $0x70, %ymm0, %xmm0"); 	//BX_ISA_AVX	_V256_VEXTRACTF128_WdqVdqIb
asm("vblendvps %xmm0, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VBLENDVPS_VpsHpsWpsIb  //Check
asm("vblendvpd %xmm0, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VBLENDVPD_VpdHpdWpdIb  //Check
asm("vpblendvb %xmm0, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPBLENDVB_VdqHdqWdqIb  //Check
asm("vpblendvb %ymm0, %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPBLENDVB_VdqHdqWdqIb  //Check
asm("vmpsadbw $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VMPSADBW_VdqHdqWdqIb
asm("vmpsadbw $0x70, %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VMPSADBW_VdqHdqWdqIb
asm("vpcmpestrm $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPESTRM_VdqWdqIb
asm("vpcmpestri $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPESTRI_VdqWdqIb
asm("vpcmpistrm $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPISTRM_VdqWdqIb
asm("vpcmpistri $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCMPISTRI_VdqWdqIb
asm("vaesimc %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VAESIMC_VdqWdq
asm("vaeskeygenassist $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VAESKEYGENASSIST_VdqWdqIb
//asm("vaesenc %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VAESENC_VdqHdqWdq
//asm("vaesenclast %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VAESENCLAST_VdqHdqWdq
//asm("vaesdec %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VAESDEC_VdqHdqWdq
//asm("vaesdeclast %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VAESDECLAST_VdqHdqWdq
//asm("vpclmulqdq $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPCLMULQDQ_VdqHdqWdqIb
//asm("vaesenc %ymm0, %ymm0, %ymm0"); 	//BX_ISA_VAES_VPCLMULQDQ	_V256_VAESENC_VdqHdqWdq
//asm("vaesenclast %ymm0, %ymm0, %ymm0"); 	//BX_ISA_VAES_VPCLMULQDQ	_V256_VAESENCLAST_VdqHdqWdq
//asm("vaesdec %ymm0, %ymm0, %ymm0"); 	//BX_ISA_VAES_VPCLMULQDQ	_V256_VAESDEC_VdqHdqWdq
//asm("vaesdeclast %ymm0, %ymm0, %ymm0"); 	//BX_ISA_VAES_VPCLMULQDQ	_V256_VAESDECLAST_VdqHdqWdq
//asm("vpclmulqdq $0x70, %ymm0, %ymm0, %ymm0"); 	//BX_ISA_VAES_VPCLMULQDQ	_V256_VPCLMULQDQ_VdqHdqWdqIb
// NI asm("vgf2p8affineqb $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_GFNI	_VGF2P8AFFINEQB_VdqHdqWdqIb
// NI asm("vgf2p8affineinvqb $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_GFNI	_VGF2P8AFFINEINVQB_VdqHdqWdqIb
// NI asm("vgf2p8mulb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_GFNI	_VGF2P8MULB_VdqHdqWdq
asm("vmovd %ebx, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVD_VdqEd
asm("vmovq %rbx, %xmm0"); 	//BX_ISA_AVX	_V128_VMOVQ_VdqEq
asm("vmovd %xmm0, (%rdi)"); 	//BX_ISA_AVX	_V128_VMOVD_EdVd
asm("vmovq %xmm0, (%rdi)"); 	//BX_ISA_AVX	_V128_VMOVQ_EqVq
asm("vpinsrb $0x70, %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPINSRB_VdqEbIb
asm("vpinsrw $0x70, %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPINSRW_VdqEwIb
asm("vpextrw $0x70, %xmm0, %ebx"); 	//BX_ISA_AVX	_V128_VPEXTRW_GdUdqIb
asm("vpextrb $0x70, %xmm0, %rbx"); 	//BX_ISA_AVX	_V128_VPEXTRB_EbdVdqIb
asm("vpextrw $0x70, %xmm0, %rbx"); 	//BX_ISA_AVX	_V128_VPEXTRW_EwdVdqIb
asm("vpinsrd $0x70, %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPINSRD_VdqEdIb
asm("vpinsrq $0x70, %rbx, %xmm0, %xmm0"); 	//BX_ISA_AVX	_V128_VPINSRQ_VdqEqIb
asm("vpextrd $0x70, %xmm0, %ebx"); 	//BX_ISA_AVX	_V128_VPEXTRD_EdVdqIb
asm("vpextrq $0x70, %xmm0, %rbx"); 	//BX_ISA_AVX	_V128_VPEXTRQ_EqVdqIb
asm("vcvtps2pd %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTPS2PD_VpdWps
asm("vcvttpd2dq %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTTPD2DQ_VdqWpd
asm("vcvtpd2dq %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTPD2DQ_VdqWpd
asm("vcvtdq2pd %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTDQ2PD_VpdWdq
asm("vcvtpd2ps %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTPD2PS_VpsWpd
asm("vcvtsd2ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTSD2SS_VssWsd
asm("vcvtss2sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTSS2SD_VsdWss
asm("vcvtdq2ps %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTDQ2PS_VpsWdq
asm("vcvtps2dq %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTPS2DQ_VdqWps
asm("vcvttps2dq %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTTPS2DQ_VdqWps
asm("vcvtss2si %xmm0, %ebx"); 	//BX_ISA_AVX	_VCVTSS2SI_GdWss
asm("vcvtss2si %xmm0, %rbx"); 	//BX_ISA_AVX	_VCVTSS2SI_GqWss
asm("vcvtsd2si %xmm0, %ebx"); 	//BX_ISA_AVX	_VCVTSD2SI_GdWsd
asm("vcvtsd2si %xmm0, %rbx"); 	//BX_ISA_AVX	_VCVTSD2SI_GqWsd
asm("vcvttss2si %xmm0, %ebx"); 	//BX_ISA_AVX	_VCVTTSS2SI_GdWss
asm("vcvttss2si %xmm0, %rbx"); 	//BX_ISA_AVX	_VCVTTSS2SI_GqWss
asm("vcvttsd2si %xmm0, %ebx"); 	//BX_ISA_AVX	_VCVTTSD2SI_GdWsd
asm("vcvttsd2si %xmm0, %rbx"); 	//BX_ISA_AVX	_VCVTTSD2SI_GqWsd
asm("vcvtsi2ss %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTSI2SS_VssEd
asm("vcvtsi2ss %rbx, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTSI2SS_VssEq
asm("vcvtsi2sd %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTSI2SD_VsdEd
asm("vcvtsi2sd %rbx, %xmm0, %xmm0"); 	//BX_ISA_AVX	_VCVTSI2SD_VsdEq
asm("vmovq (%rdi), %xmm0"); 	//BX_ISA_AVX	_VMOVQ_WqVq
asm("vmovq %xmm0, (%rdi)"); 	//BX_ISA_AVX	_VMOVQ_VqWq
asm("vcvtph2ps %xmm0, %xmm0"); 	//BX_ISA_AVX_F16C	_VCVTPH2PS_VpsWps
asm("vcvtps2ph $0x70, %xmm0, %xmm0"); 	//BX_ISA_AVX_F16C	_VCVTPS2PH_WpsVpsIb
asm("vpmovsxbw %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVSXBW_VdqWdq
asm("vpmovsxbd %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVSXBD_VdqWq
asm("vpmovsxbq %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVSXBQ_VdqWd
asm("vpmovsxwd %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVSXWD_VdqWdq
asm("vpmovsxwq %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVSXWQ_VdqWq
asm("vpmovsxdq %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVSXDQ_VdqWdq
asm("vpmovzxbw %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVZXBW_VdqWdq
asm("vpmovzxbd %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVZXBD_VdqWq
asm("vpmovzxbq %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVZXBQ_VdqWd
asm("vpmovzxwd %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVZXWD_VdqWdq
asm("vpmovzxwq %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVZXWQ_VdqWq
asm("vpmovzxdq %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPMOVZXDQ_VdqWdq
asm("vperm2i128 $0x70, %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPERM2I128_VdqHdqWdqIb
asm("vinserti128 $0x70, %xmm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VINSERTI128_VdqHdqWdqIb
asm("vextracti128 $0x70, %ymm0, %xmm0"); 	//BX_ISA_AVX2	_V256_VEXTRACTI128_WdqVdqIb
asm("vbroadcasti128 (%rsi), %ymm0"); 	//BX_ISA_AVX2	_V256_VBROADCASTI128_VdqMdq
asm("vpbroadcastb %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VPBROADCASTB_VdqWb
asm("vpbroadcastw %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VPBROADCASTW_VdqWw
asm("vpbroadcastd %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VPBROADCASTD_VdqWd
asm("vpbroadcastq %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VPBROADCASTQ_VdqWq
asm("vbroadcastss %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VBROADCASTSS_VpsWss
asm("vbroadcastsd %xmm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VBROADCASTSD_VpdWsd
asm("vpblendd $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VPBLENDD_VdqHdqWdqIb
// NI asm("vmaskmovd (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VMASKMOVD_VdqHdqMdq
// NI asm("vmaskmovq (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VMASKMOVQ_VdqHdqMdq
// NI asm("vmaskmovd %xmm0, %xmm0, (%rsi)"); 	//BX_ISA_AVX2	_VMASKMOVD_MdqHdqVdq
// NI asm("vmaskmovq %xmm0, %xmm0, (%rsi)"); 	//BX_ISA_AVX2	_VMASKMOVQ_MdqHdqVdq
asm("vgatherdps (%rdi, %ymm0, 1), %ymm1{%k1}"); 	//BX_ISA_AVX2	_VGATHERDPS_VpsHps
asm("vgatherdpd (%rdi, %xmm0, 1), %ymm1{%k1}"); 	//BX_ISA_AVX2	_VGATHERDPD_VpdHpd
asm("vgatherqps (%rdi, %zmm0, 1), %ymm1{%k1}"); 	//BX_ISA_AVX2	_VGATHERQPS_VpsHps
asm("vgatherqpd (%rdi, %ymm0, 1), %ymm1{%k1}"); 	//BX_ISA_AVX2	_VGATHERQPD_VpdHpd
// NI asm("vgatherdd %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VGATHERDD_VdqHdq
// NI asm("vgatherdq %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VGATHERDQ_VdqHdq
// NI asm("vgatherqd %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VGATHERQD_VdqHdq
// NI asm("vgatherqq %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VGATHERQQ_VdqHdq
asm("vpsrlvd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VPSRLVD_VdqHdqWdq
asm("vpsrlvq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VPSRLVQ_VdqHdqWdq
asm("vpsllvd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VPSLLVD_VdqHdqWdq
asm("vpsllvq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VPSLLVQ_VdqHdqWdq
asm("vpermq $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPERMQ_VdqWdqIb
asm("vpermd %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPERMD_VdqHdqWdq
asm("vpermps %ymm0, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPERMPS_VpsHpsWps
asm("vpermpd $0x70, %ymm0, %ymm0"); 	//BX_ISA_AVX2	_V256_VPERMPD_VpdWpdIb
asm("vpsravd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX2	_VPSRAVD_VdqHdqWdq
asm("vfmadd132ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD132PS_VpsHpsWps
asm("vfmadd132pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD132PD_VpdHpdWpd
asm("vfmadd213ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD213PS_VpsHpsWps
asm("vfmadd213pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD213PD_VpdHpdWpd
asm("vfmadd231ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD231PS_VpsHpsWps
asm("vfmadd231pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD231PD_VpdHpdWpd
asm("vfmadd132ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD132SS_VpsHssWss
asm("vfmadd132sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD132SD_VpdHsdWsd
asm("vfmadd213ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD213SS_VpsHssWss
asm("vfmadd213sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD213SD_VpdHsdWsd
asm("vfmadd231ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD231SS_VpsHssWss
asm("vfmadd231sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADD231SD_VpdHsdWsd
asm("vfmaddsub132ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADDSUB132PS_VpsHpsWps
asm("vfmaddsub132pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADDSUB132PD_VpdHpdWpd
asm("vfmaddsub213ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADDSUB213PS_VpsHpsWps
asm("vfmaddsub213pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADDSUB213PD_VpdHpdWpd
asm("vfmaddsub231ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADDSUB231PS_VpsHpsWps
asm("vfmaddsub231pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMADDSUB231PD_VpdHpdWpd
asm("vfmsubadd132ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUBADD132PS_VpsHpsWps
asm("vfmsubadd132pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUBADD132PD_VpdHpdWpd
asm("vfmsubadd213ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUBADD213PS_VpsHpsWps
asm("vfmsubadd213pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUBADD213PD_VpdHpdWpd
asm("vfmsubadd231ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUBADD231PS_VpsHpsWps
asm("vfmsubadd231pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUBADD231PD_VpdHpdWpd
asm("vfmsub132ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB132PS_VpsHpsWps
asm("vfmsub132pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB132PD_VpdHpdWpd
asm("vfmsub213ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB213PS_VpsHpsWps
asm("vfmsub213pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB213PD_VpdHpdWpd
asm("vfmsub231ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB231PS_VpsHpsWps
asm("vfmsub231pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB231PD_VpdHpdWpd
asm("vfmsub132ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB132SS_VpsHssWss
asm("vfmsub132sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB132SD_VpdHsdWsd
asm("vfmsub213ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB213SS_VpsHssWss
asm("vfmsub213sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB213SD_VpdHsdWsd
asm("vfmsub231ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB231SS_VpsHssWss
asm("vfmsub231sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFMSUB231SD_VpdHsdWsd
asm("vfnmadd132ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD132PS_VpsHpsWps
asm("vfnmadd132pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD132PD_VpdHpdWpd
asm("vfnmadd213ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD213PS_VpsHpsWps
asm("vfnmadd213pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD213PD_VpdHpdWpd
asm("vfnmadd231ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD231PS_VpsHpsWps
asm("vfnmadd231pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD231PD_VpdHpdWpd
asm("vfnmadd132ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD132SS_VpsHssWss
asm("vfnmadd132sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD132SD_VpdHsdWsd
asm("vfnmadd213ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD213SS_VpsHssWss
asm("vfnmadd213sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD213SD_VpdHsdWsd
asm("vfnmadd231ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD231SS_VpsHssWss
asm("vfnmadd231sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMADD231SD_VpdHsdWsd
asm("vfnmsub132ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB132PS_VpsHpsWps
asm("vfnmsub132pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB132PD_VpdHpdWpd
asm("vfnmsub213ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB213PS_VpsHpsWps
asm("vfnmsub213pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB213PD_VpdHpdWpd
asm("vfnmsub231ps %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB231PS_VpsHpsWps
asm("vfnmsub231pd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB231PD_VpdHpdWpd
asm("vfnmsub132ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB132SS_VpsHssWss
asm("vfnmsub132sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB132SD_VpdHsdWsd
asm("vfnmsub213ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB213SS_VpsHssWss
asm("vfnmsub213sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB213SD_VpdHsdWsd
asm("vfnmsub231ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB231SS_VpsHssWss
asm("vfnmsub231sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX_FMA	_VFNMSUB231SD_VpdHsdWsd
asm("andn %ebx, %ebx, %ebx"); 	//BX_ISA_BMI1	_ANDN_GdBdEd
asm("andn %rbx, %rbx, %rbx"); 	//BX_ISA_BMI1	_ANDN_GqBqEq
asm("blsi %ebx, %ebx"); 	//BX_ISA_BMI1	_BLSI_BdEd
asm("blsi %rbx, %rbx"); 	//BX_ISA_BMI1	_BLSI_BqEq
asm("blsmsk %ebx, %ebx"); 	//BX_ISA_BMI1	_BLSMSK_BdEd
asm("blsmsk %rbx, %rbx"); 	//BX_ISA_BMI1	_BLSMSK_BqEq
asm("blsr %ebx, %ebx"); 	//BX_ISA_BMI1	_BLSR_BdEd
asm("blsr %rbx, %rbx"); 	//BX_ISA_BMI1	_BLSR_BqEq
asm("bextr %ebx, %ebx, %ebx"); 	//BX_ISA_BMI1	_BEXTR_GdEdBd
asm("bextr %rbx, %rbx, %rbx"); 	//BX_ISA_BMI1	_BEXTR_GqEqBq
asm("mulx %ebx, %ebx, %ebx"); 	//BX_ISA_BMI2	_MULX_GdBdEd
asm("mulx %rbx, %rbx, %rbx"); 	//BX_ISA_BMI2	_MULX_GqBqEq
asm("rorx $0x70, %ebx, %ebx"); 	//BX_ISA_BMI2	_RORX_GdEdIb
asm("rorx $0x70, %rbx, %rbx"); 	//BX_ISA_BMI2	_RORX_GqEqIb
asm("shlx %ebx, %ebx, %ebx"); 	//BX_ISA_BMI2	_SHLX_GdEdBd
asm("shlx %rbx, %rbx, %rbx"); 	//BX_ISA_BMI2	_SHLX_GqEqBq
asm("shrx %ebx, %ebx, %ebx"); 	//BX_ISA_BMI2	_SHRX_GdEdBd
asm("shrx %rbx, %rbx, %rbx"); 	//BX_ISA_BMI2	_SHRX_GqEqBq
asm("sarx %ebx, %ebx, %ebx"); 	//BX_ISA_BMI2	_SARX_GdEdBd
asm("sarx %rbx, %rbx, %rbx"); 	//BX_ISA_BMI2	_SARX_GqEqBq
asm("bzhi %ebx, %ebx, %ebx"); 	//BX_ISA_BMI2	_BZHI_GdBdEd
asm("bzhi %rbx, %rbx, %rbx"); 	//BX_ISA_BMI2	_BZHI_GqBqEq
asm("pext %ebx, %ebx, %ebx"); 	//BX_ISA_BMI2	_PEXT_GdBdEd
asm("pext %rbx, %rbx, %rbx"); 	//BX_ISA_BMI2	_PEXT_GqBqEq
asm("pdep %ebx, %ebx, %ebx"); 	//BX_ISA_BMI2	_PDEP_GdBdEd
asm("pdep %rbx, %rbx, %rbx"); 	//BX_ISA_BMI2	_PDEP_GqBqEq
// UD asm("vfmaddsubps %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDSUBPS_VpsHpsVIbWps
// UD asm("vfmaddsubps (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDSUBPS_VpsHpsWpsVIb
// UD asm("vfmaddsubpd %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDSUBPD_VpdHpdVIbWpd
// UD asm("vfmaddsubpd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDSUBPD_VpdHpdWpdVIb
// UD asm("vfmsubaddps %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBADDPS_VpsHpsVIbWps
// UD asm("vfmsubaddps (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBADDPS_VpsHpsWpsVIb
// UD asm("vfmsubaddpd %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBADDPD_VpdHpdVIbWpd
// UD asm("vfmsubaddpd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBADDPD_VpdHpdWpdVIb
// UD asm("vfmaddps %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDPS_VpsHpsVIbWps
// UD asm("vfmaddps (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDPS_VpsHpsWpsVIb
// UD asm("vfmaddpd %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDPD_VpdHpdVIbWpd
// UD asm("vfmaddpd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDPD_VpdHpdWpdVIb
// UD asm("vfmaddss %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDSS_VssHssVIbWss
// UD asm("vfmaddss (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDSS_VssHssWssVIb
// UD asm("vfmaddsd %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDSD_VsdHsdVIbWsd
// UD asm("vfmaddsd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMADDSD_VsdHsdWsdVIb
// UD asm("vfmsubps %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBPS_VpsHpsVIbWps
// UD asm("vfmsubps (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBPS_VpsHpsWpsVIb
// UD asm("vfmsubpd %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBPD_VpdHpdVIbWpd
// UD asm("vfmsubpd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBPD_VpdHpdWpdVIb
// UD asm("vfmsubss %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBSS_VssHssVIbWss
// UD asm("vfmsubss (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBSS_VssHssWssVIb
// UD asm("vfmsubsd %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBSD_VsdHsdVIbWsd
// UD asm("vfmsubsd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFMSUBSD_VsdHsdWsdVIb
// UD asm("vfnmaddps %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMADDPS_VpsHpsVIbWps
// UD asm("vfnmaddps (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMADDPS_VpsHpsWpsVIb
// UD asm("vfnmaddpd %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMADDPD_VpdHpdVIbWpd
// UD asm("vfnmaddpd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMADDPD_VpdHpdWpdVIb
// UD asm("vfnmaddss %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMADDSS_VssHssVIbWss
// UD asm("vfnmaddss (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMADDSS_VssHssWssVIb
// UD asm("vfnmaddsd %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMADDSD_VsdHsdVIbWsd
// UD asm("vfnmaddsd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMADDSD_VsdHsdWsdVIb
// UD asm("vfnmsubps %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMSUBPS_VpsHpsVIbWps
// UD asm("vfnmsubps (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMSUBPS_VpsHpsWpsVIb
// UD asm("vfnmsubpd %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMSUBPD_VpdHpdVIbWpd
// UD asm("vfnmsubpd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMSUBPD_VpdHpdWpdVIb
// UD asm("vfnmsubss %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMSUBSS_VssHssVIbWss
// UD asm("vfnmsubss (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMSUBSS_VssHssWssVIb
// UD asm("vfnmsubsd %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMSUBSD_VsdHsdVIbWsd
// UD asm("vfnmsubsd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_FMA4	_VFNMSUBSD_VsdHsdWsdVIb
// AMD 
/*
asm("vpcmov %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPCMOV_VdqHdqVIbWdq
asm("vpcmov (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPCMOV_VdqHdqWdqVIb
asm("vpperm %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPPERM_VdqHdqVIbWdq
asm("vpperm (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPPERM_VdqHdqWdqVIb
asm("vpermil2ps %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPERMIL2PS_VdqHdqVIbWdq
asm("vpermil2ps (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPERMIL2PS_VdqHdqWdqVIb
asm("vpermil2pd %xmm0, (%rdi), %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPERMIL2PD_VdqHdqVIbWdq
asm("vpermil2pd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPERMIL2PD_VdqHdqWdqVIb
asm("vpshab %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHAB_VdqHdqWdq
asm("vpshab %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHAB_VdqWdqHdq
asm("vpshaw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHAW_VdqHdqWdq
asm("vpshaw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHAW_VdqWdqHdq
asm("vpshad %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHAD_VdqHdqWdq
asm("vpshad %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHAD_VdqWdqHdq
asm("vpshaq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHAQ_VdqHdqWdq
asm("vpshaq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHAQ_VdqWdqHdq
asm("vprotb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTB_VdqHdqWdq
asm("vprotb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTB_VdqWdqHdq
asm("vprotw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTW_VdqHdqWdq
asm("vprotw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTW_VdqWdqHdq
asm("vprotd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTD_VdqHdqWdq
asm("vprotd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTD_VdqWdqHdq
asm("vprotq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTQ_VdqHdqWdq
asm("vprotq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTQ_VdqWdqHdq
asm("vpshlb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHLB_VdqHdqWdq
asm("vpshlb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHLB_VdqWdqHdq
asm("vpshlw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHLW_VdqHdqWdq
asm("vpshlw %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHLW_VdqWdqHdq
asm("vpshld %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHLD_VdqHdqWdq
asm("vpshld %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHLD_VdqWdqHdq
asm("vpshlq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHLQ_VdqHdqWdq
asm("vpshlq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPSHLQ_VdqWdqHdq
asm("vpmacssww (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMACSSWW_VdqHdqWdqVIb
asm("vpmacsswd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMACSSWD_VdqHdqWdqVIb
asm("vpmacssdql (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMACSSDQL_VdqHdqWdqVIb
asm("vpmacssdd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMACSSDD_VdqHdqWdqVIb
asm("vpmacssdqh (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMACSSDQH_VdqHdqWdqVIb
asm("vpmacsww (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMACSWW_VdqHdqWdqVIb
asm("vpmacswd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMACSWD_VdqHdqWdqVIb
asm("vpmacsdql (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMACSDQL_VdqHdqWdqVIb
asm("vpmacsdd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMACSDD_VdqHdqWdqVIb
asm("vpmacsdqh (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMACSDQH_VdqHdqWdqVIb
asm("vpmadcsswd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMADCSSWD_VdqHdqWdqVIb
asm("vpmadcswd (%rdi), %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPMADCSWD_VdqHdqWdqVIb
asm("vprotb $0x70, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTB_VdqWdqIb
asm("vprotw $0x70, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTW_VdqWdqIb
asm("vprotd $0x70, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTD_VdqWdqIb
asm("vprotq $0x70, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPROTQ_VdqWdqIb
asm("vpcomb $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPCOMB_VdqHdqWdqIb
asm("vpcomw $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPCOMW_VdqHdqWdqIb
asm("vpcomd $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPCOMD_VdqHdqWdqIb
asm("vpcomq $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPCOMQ_VdqHdqWdqIb
asm("vpcomub $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPCOMUB_VdqHdqWdqIb
asm("vpcomuw $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPCOMUW_VdqHdqWdqIb
asm("vpcomud $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPCOMUD_VdqHdqWdqIb
asm("vpcomuq $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPCOMUQ_VdqHdqWdqIb
asm("vfrczps %xmm0, %xmm0"); 	//BX_ISA_XOP	_VFRCZPS_VpsWps
asm("vfrczpd %xmm0, %xmm0"); 	//BX_ISA_XOP	_VFRCZPD_VpdWpd
asm("vfrczss %xmm0, %xmm0"); 	//BX_ISA_XOP	_VFRCZSS_VssWss
asm("vfrczsd %xmm0, %xmm0"); 	//BX_ISA_XOP	_VFRCZSD_VsdWsd
asm("vphaddbw %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDBW_VdqWdq
asm("vphaddbd %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDBD_VdqWdq
asm("vphaddbq %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDBQ_VdqWdq
asm("vphaddwd %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDWD_VdqWdq
asm("vphaddwq %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDWQ_VdqWdq
asm("vphadddq %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDDQ_VdqWdq
asm("vphaddubw %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDUBW_VdqWdq
asm("vphaddubd %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDUBD_VdqWdq
asm("vphaddubq %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDUBQ_VdqWdq
asm("vphadduwd %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDUWD_VdqWdq
asm("vphadduwq %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDUWQ_VdqWdq
asm("vphaddudq %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHADDUDQ_VdqWdq
asm("vphsubbw %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHSUBBW_VdqWdq
asm("vphsubwd %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHSUBWD_VdqWdq
asm("vphsubdq %xmm0, %xmm0"); 	//BX_ISA_XOP	_VPHSUBDQ_VdqWdq
*/

// UD asm("bextr $0x70000000, %ebx, %ebx"); 	//BX_ISA_TBM	_BEXTR_GdEdId
// UD asm("bextr $0x70000000, %rbx, %rbx"); 	//BX_ISA_TBM	_BEXTR_GqEqId
// UD asm("blcfill %ebx, %ebx"); 	//BX_ISA_TBM	_BLCFILL_BdEd
// UD asm("blcfill %rbx, %rbx"); 	//BX_ISA_TBM	_BLCFILL_BqEq
// UD asm("blci %ebx, %ebx"); 	//BX_ISA_TBM	_BLCI_BdEd
// UD asm("blci %rbx, %rbx"); 	//BX_ISA_TBM	_BLCI_BqEq
// UD asm("blcic %ebx, %ebx"); 	//BX_ISA_TBM	_BLCIC_BdEd
// UD asm("blcic %rbx, %rbx"); 	//BX_ISA_TBM	_BLCIC_BqEq
// UD asm("blcmsk %ebx, %ebx"); 	//BX_ISA_TBM	_BLCMSK_BdEd
// UD asm("blcmsk %rbx, %rbx"); 	//BX_ISA_TBM	_BLCMSK_BqEq
// UD asm("blcs %ebx, %ebx"); 	//BX_ISA_TBM	_BLCS_BdEd
// UD asm("blcs %rbx, %rbx"); 	//BX_ISA_TBM	_BLCS_BqEq
// UD asm("blsfill %ebx, %ebx"); 	//BX_ISA_TBM	_BLSFILL_BdEd
// UD asm("blsfill %rbx, %rbx"); 	//BX_ISA_TBM	_BLSFILL_BqEq
// UD asm("blsic %ebx, %ebx"); 	//BX_ISA_TBM	_BLSIC_BdEd
// UD asm("blsic %rbx, %rbx"); 	//BX_ISA_TBM	_BLSIC_BqEq
// UD asm("t1mskc %ebx, %ebx"); 	//BX_ISA_TBM	_T1MSKC_BdEd
// UD asm("t1mskc %rbx, %rbx"); 	//BX_ISA_TBM	_T1MSKC_BqEq
// UD asm("tzmsk %ebx, %ebx"); 	//BX_ISA_TBM	_TZMSK_BdEd
// UD asm("tzmsk %rbx, %rbx"); 	//BX_ISA_TBM	_TZMSK_BqEq
asm("tzcnt %bx, %bx"); 	//BX_ISA_BMI1	_TZCNT_GwEw
asm("tzcnt %ebx, %ebx"); 	//BX_ISA_BMI1	_TZCNT_GdEd
asm("tzcnt %rbx, %rbx"); 	//BX_ISA_BMI1	_TZCNT_GqEq
asm("lzcnt %bx, %bx"); 	//BX_ISA_LZCNT	_LZCNT_GwEw
asm("lzcnt %ebx, %ebx"); 	//BX_ISA_LZCNT	_LZCNT_GdEd
asm("lzcnt %rbx, %rbx"); 	//BX_ISA_LZCNT	_LZCNT_GqEq
// UD asm("movntss %xmm0, (%rsi)"); 	//BX_ISA_SSE4A	_MOVNTSS_MssVss
// UD asm("movntsd %xmm0, (%rsi)"); 	//BX_ISA_SSE4A	_MOVNTSD_MsdVsd
// UD asm("extrq $0x70, $0x70, %xmm0"); 	//BX_ISA_SSE4A	_EXTRQ_UdqIbIb
// UD asm("extrq %xmm0, %xmm0"); 	//BX_ISA_SSE4A	_EXTRQ_VdqUq
// UD asm("insertq $0x70, $0x70, %xmm0, %xmm0"); 	//BX_ISA_SSE4A	_INSERTQ_VdqUqIbIb
// UD asm("insertq %xmm0, %xmm0"); 	//BX_ISA_SSE4A	_INSERTQ_VdqUdq
asm("adcx %ebx, %ebx"); 	//BX_ISA_ADX	_ADCX_GdEd
asm("adox %ebx, %ebx"); 	//BX_ISA_ADX	_ADOX_GdEd
asm("adcx %rbx, %rbx"); 	//BX_ISA_ADX	_ADCX_GqEq
asm("adox %rbx, %rbx"); 	//BX_ISA_ADX	_ADOX_GqEq
// UD asm("stac"); 	//BX_ISA_SMAP	_STAC
// UD asm("clac"); 	//BX_ISA_SMAP	_CLAC
asm("rdrand %bx"); 	//BX_ISA_RDRAND	_RDRAND_Ew
asm("rdrand %ebx"); 	//BX_ISA_RDRAND	_RDRAND_Ed
asm("rdrand %rbx"); 	//BX_ISA_RDRAND	_RDRAND_Eq
asm("rdseed %bx"); 	//BX_ISA_RDSEED	_RDSEED_Ew
asm("rdseed %ebx"); 	//BX_ISA_RDSEED	_RDSEED_Ed
asm("rdseed %rbx"); 	//BX_ISA_RDSEED	_RDSEED_Eq


asm("kaddw %k5, %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KADDW_KGwKHwKEw
asm("kaddq %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KADDQ_KGqKHqKEq
asm("kaddb %k5, %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KADDB_KGbKHbKEb
asm("kaddd %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KADDD_KGdKHdKEd
asm("kandw %k5, %k5, %k5"); 	//BX_ISA_AVX512	_KANDW_KGwKHwKEw
asm("kandq %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KANDQ_KGqKHqKEq
asm("kandb %k5, %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KANDB_KGbKHbKEb
asm("kandd %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KANDD_KGdKHdKEd
asm("kandnw %k5, %k5, %k5"); 	//BX_ISA_AVX512	_KANDNW_KGwKHwKEw
asm("kandnq %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KANDNQ_KGqKHqKEq
asm("kandnb %k5, %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KANDNB_KGbKHbKEb
asm("kandnd %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KANDND_KGdKHdKEd
asm("kmovw %k5, %k5"); 	//BX_ISA_AVX512	_KMOVW_KGwKEw
asm("kmovq %k5, %k5"); 	//BX_ISA_AVX512_BW	_KMOVQ_KGqKEq
asm("kmovb %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KMOVB_KGbKEb
asm("kmovd %k5, %k5"); 	//BX_ISA_AVX512_BW	_KMOVD_KGdKEd
asm("kmovw %k5, %k5"); 	//BX_ISA_AVX512	_KMOVW_KEwKGw
asm("kmovq %k5, %k5"); 	//BX_ISA_AVX512_BW	_KMOVQ_KEqKGq
asm("kmovb %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KMOVB_KEbKGb
asm("kmovd %k5, %k5"); 	//BX_ISA_AVX512_BW	_KMOVD_KEdKGd
asm("kmovb %k5, %ebx"); 	//BX_ISA_AVX512_DQ	_KMOVB_GdKEb
asm("kmovw %k5, %ebx"); 	//BX_ISA_AVX512	_KMOVW_GdKEw
asm("kmovd %k5, %ebx"); 	//BX_ISA_AVX512_BW	_KMOVD_GdKEd
asm("kmovq %k5, %rbx"); 	//BX_ISA_AVX512_BW	_KMOVQ_GqKEq
asm("kmovb %ebx, %k5"); 	//BX_ISA_AVX512_DQ	_KMOVB_KGbEb
asm("kmovw %ebx, %k5"); 	//BX_ISA_AVX512	_KMOVW_KGwEw
asm("kmovd %ebx, %k5"); 	//BX_ISA_AVX512_BW	_KMOVD_KGdEd
asm("kmovq %rbx, %k5"); 	//BX_ISA_AVX512_BW	_KMOVQ_KGqEq
asm("kunpckbw %k5, %k5, %k5"); 	//BX_ISA_AVX512	_KUNPCKBW_KGwKHbKEb
asm("kunpckwd %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KUNPCKWD_KGdKHwKEw
asm("kunpckdq %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KUNPCKDQ_KGqKHdKEd
asm("knotw %k5, %k5"); 	//BX_ISA_AVX512	_KNOTW_KGwKEw
asm("knotq %k5, %k5"); 	//BX_ISA_AVX512_BW	_KNOTQ_KGqKEq
asm("knotb %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KNOTB_KGbKEb
asm("knotd %k5, %k5"); 	//BX_ISA_AVX512_BW	_KNOTD_KGdKEd
asm("korw %k5, %k5, %k5"); 	//BX_ISA_AVX512	_KORW_KGwKHwKEw
asm("korq %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KORQ_KGqKHqKEq
asm("korb %k5, %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KORB_KGbKHbKEb
asm("kord %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KORD_KGdKHdKEd
asm("kortestw %k5, %k5"); 	//BX_ISA_AVX512	_KORTESTW_KGwKEw
asm("kortestq %k5, %k5"); 	//BX_ISA_AVX512_BW	_KORTESTQ_KGqKEq
asm("kortestb %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KORTESTB_KGbKEb
asm("kortestd %k5, %k5"); 	//BX_ISA_AVX512_BW	_KORTESTD_KGdKEd

asm("kshiftlb $0x70, %k5, %k5");
//BX_IA_KSHIFTLB_KGbKEbIb,BX_ISA_AVX512_DQ,BX_SUPPORT_AVX,Y,,0,VexW Aliased

asm("kshiftlw $0x70, %k5, %k5");
//BX_IA_KSHIFTLW_KGwKEwIb,BX_ISA_AVX512,BX_SUPPORT_AVX,Y,,0,VexW Aliased

asm("kshiftld $0x70, %k5, %k5");
//BX_IA_KSHIFTLD_KGdKEdIb,BX_ISA_AVX512_BW,BX_SUPPORT_AVX,Y,,0,VexW Aliased

asm("kshiftlq $0x70, %k5, %k5");
//BX_IA_KSHIFTLQ_KGqKEqIb,BX_ISA_AVX512_BW,BX_SUPPORT_AVX,Y,,0,VexW Aliased

asm("kshiftrb $0x70, %k5, %k5");
//BX_IA_KSHIFTRB_KGbKEbIb,BX_ISA_AVX512_DQ,BX_SUPPORT_AVX,Y,,0,VexW Aliased

asm("kshiftrw $0x70, %k5, %k5");
//BX_IA_KSHIFTRW_KGwKEwIb,BX_ISA_AVX512,BX_SUPPORT_AVX,Y,,0,VexW Aliased

asm("kshiftrd $0x70, %k5, %k5");
//BX_IA_KSHIFTRD_KGdKEdIb,BX_ISA_AVX512_BW,BX_SUPPORT_AVX,Y,,0,VexW Aliased

asm("kshiftrq $0x70, %k5, %k5");
//BX_IA_KSHIFTRQ_KGqKEqIb,BX_ISA_AVX512_BW,BX_SUPPORT_AVX,Y,,0,VexW Aliased

asm("kxnorw %k5, %k5, %k5"); 	//BX_ISA_AVX512	_KXNORW_KGwKHwKEw
asm("kxnorq %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KXNORQ_KGqKHqKEq
asm("kxnorb %k5, %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KXNORB_KGbKHbKEb
asm("kxnord %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KXNORD_KGdKHdKEd
asm("kxorw %k5, %k5, %k5"); 	//BX_ISA_AVX512	_KXORW_KGwKHwKEw
asm("kxorq %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KXORQ_KGqKHqKEq
asm("kxorb %k5, %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KXORB_KGbKHbKEb
asm("kxord %k5, %k5, %k5"); 	//BX_ISA_AVX512_BW	_KXORD_KGdKHdKEd
asm("ktestw %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KTESTW_KGwKEw
asm("ktestq %k5, %k5"); 	//BX_ISA_AVX512_BW	_KTESTQ_KGqKEq
asm("ktestb %k5, %k5"); 	//BX_ISA_AVX512_DQ	_KTESTB_KGbKEb
asm("ktestd %k5, %k5"); 	//BX_ISA_AVX512_BW	_KTESTD_KGdKEd
asm("vaddps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VADDPS_VpsHpsWps
asm("vaddpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VADDPD_VpdHpdWpd
asm("vaddss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VADDSS_VssHpsWss
asm("vaddsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VADDSD_VsdHpdWsd
asm("vaddps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VADDPS_VpsHpsWps_Kmask
asm("vaddpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VADDPD_VpdHpdWpd_Kmask
asm("vaddss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VADDSS_VssHpsWss_Kmask
asm("vaddsd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VADDSD_VsdHpdWsd_Kmask
asm("vsubps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VSUBPS_VpsHpsWps
asm("vsubpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VSUBPD_VpdHpdWpd
asm("vsubss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VSUBSS_VssHpsWss
asm("vsubsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VSUBSD_VsdHpdWsd
asm("vsubps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSUBPS_VpsHpsWps_Kmask
asm("vsubpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSUBPD_VpdHpdWpd_Kmask
asm("vsubss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSUBSS_VssHpsWss_Kmask
asm("vsubsd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSUBSD_VsdHpdWsd_Kmask
asm("vmulps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMULPS_VpsHpsWps
asm("vmulpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMULPD_VpdHpdWpd
asm("vmulss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMULSS_VssHpsWss
asm("vmulsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMULSD_VsdHpdWsd
asm("vmulps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMULPS_VpsHpsWps_Kmask
asm("vmulpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMULPD_VpdHpdWpd_Kmask
asm("vmulss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMULSS_VssHpsWss_Kmask
asm("vmulsd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMULSD_VsdHpdWsd_Kmask
asm("vdivps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VDIVPS_VpsHpsWps
asm("vdivpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VDIVPD_VpdHpdWpd
asm("vdivss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VDIVSS_VssHpsWss
asm("vdivsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VDIVSD_VsdHpdWsd
asm("vdivps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VDIVPS_VpsHpsWps_Kmask
asm("vdivpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VDIVPD_VpdHpdWpd_Kmask
asm("vdivss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VDIVSS_VssHpsWss_Kmask
asm("vdivsd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VDIVSD_VsdHpdWsd_Kmask
asm("vminps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMINPS_VpsHpsWps
asm("vminpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMINPD_VpdHpdWpd
asm("vminss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMINSS_VssHpsWss
asm("vminsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMINSD_VsdHpdWsd
asm("vminps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMINPS_VpsHpsWps_Kmask
asm("vminpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMINPD_VpdHpdWpd_Kmask
asm("vminss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMINSS_VssHpsWss_Kmask
asm("vminsd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMINSD_VsdHpdWsd_Kmask
asm("vmaxps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMAXPS_VpsHpsWps
asm("vmaxpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMAXPD_VpdHpdWpd
asm("vmaxss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMAXSS_VssHpsWss
asm("vmaxsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMAXSD_VsdHpdWsd
asm("vmaxps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMAXPS_VpsHpsWps_Kmask
asm("vmaxpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMAXPD_VpdHpdWpd_Kmask
asm("vmaxss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMAXSS_VssHpsWss_Kmask
asm("vmaxsd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMAXSD_VsdHpdWsd_Kmask
asm("vsqrtps %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VSQRTPS_VpsWps
asm("vsqrtpd %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VSQRTPD_VpdWpd
asm("vsqrtss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VSQRTSS_VssHpsWss
asm("vsqrtsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VSQRTSD_VsdHpdWsd
asm("vsqrtps %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSQRTPS_VpsWps_Kmask
asm("vsqrtpd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSQRTPD_VpdWpd_Kmask
asm("vsqrtss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSQRTSS_VssHpsWss_Kmask
asm("vsqrtsd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSQRTSD_VsdHpdWsd_Kmask
asm("vcmpps $0x70, %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VCMPPS_KGwHpsWpsIb
asm("vcmppd $0x70, %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VCMPPD_KGbHpdWpdIb
asm("vcmpss $0x70, %xmm0, %xmm0, %k5"); 	//BX_ISA_AVX512	_V512_VCMPSS_KGbHssWssIb
asm("vcmpsd $0x70, %xmm0, %xmm0, %k5"); 	//BX_ISA_AVX512	_V512_VCMPSD_KGbHsdWsdIb
asm("vrndscaleps $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRNDSCALEPS_VpsWpsIb_Kmask
asm("vrndscalepd $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRNDSCALEPD_VpdWpdIb_Kmask
asm("vrndscaless $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRNDSCALESS_VssHpsWssIb_Kmask
asm("vrndscalesd $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRNDSCALESD_VsdHpdWsdIb_Kmask
asm("vunpcklps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VUNPCKLPS_VpsHpsWps
asm("vunpcklpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VUNPCKLPD_VpdHpdWpd
asm("vunpcklps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VUNPCKLPS_VpsHpsWps_Kmask
asm("vunpcklpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VUNPCKLPD_VpdHpdWpd_Kmask
asm("vunpckhps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VUNPCKHPS_VpsHpsWps
asm("vunpckhpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VUNPCKHPD_VpdHpdWpd
asm("vunpckhps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VUNPCKHPS_VpsHpsWps_Kmask
asm("vunpckhpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VUNPCKHPD_VpdHpdWpd_Kmask
asm("vpunpckldq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPUNPCKLDQ_VdqHdqWdq
asm("vpunpcklqdq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPUNPCKLQDQ_VdqHdqWdq
asm("vpunpckldq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPUNPCKLDQ_VdqHdqWdq_Kmask
asm("vpunpcklqdq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPUNPCKLQDQ_VdqHdqWdq_Kmask
asm("vpunpckhdq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPUNPCKHDQ_VdqHdqWdq
asm("vpunpckhqdq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPUNPCKHQDQ_VdqHdqWdq
asm("vpunpckhdq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPUNPCKHDQ_VdqHdqWdq_Kmask
asm("vpunpckhqdq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPUNPCKHQDQ_VdqHdqWdq_Kmask
asm("vpmuldq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMULDQ_VdqHdqWdq
asm("vpmuldq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMULDQ_VdqHdqWdq_Kmask
asm("vpmuludq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMULUDQ_VdqHdqWdq
asm("vpmuludq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMULUDQ_VdqHdqWdq_Kmask
asm("vucomiss %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VUCOMISS_VssWss
asm("vcomiss %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCOMISS_VssWss
asm("vucomisd %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VUCOMISD_VsdWsd
asm("vcomisd %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCOMISD_VsdWsd
asm("vcvtss2sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTSS2SD_VsdWss
asm("vcvtsd2ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTSD2SS_VssWsd
asm("vcvtps2pd %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTPS2PD_VpdWps
asm("vcvtpd2ps %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTPD2PS_VpsWpd
asm("vcvtss2sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTSS2SD_VsdWss_Kmask
asm("vcvtsd2ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTSD2SS_VssWsd_Kmask
asm("vcvtps2pd %ymm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTPS2PD_VpdWps_Kmask
asm("vcvtpd2ps %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTPD2PS_VpsWpd_Kmask
asm("vcvtps2dq %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VCVTPS2DQ_VdqWps
asm("vcvtps2dq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTPS2DQ_VdqWps_Kmask
asm("vcvttps2dq %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VCVTTPS2DQ_VdqWps
asm("vcvttps2dq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTTPS2DQ_VdqWps_Kmask
asm("vcvtpd2dq %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTPD2DQ_VdqWpd
asm("vcvtpd2dq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTPD2DQ_VdqWpd_Kmask
asm("vcvttpd2dq %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTTPD2DQ_VdqWpd
asm("vcvttpd2dq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTTPD2DQ_VdqWpd_Kmask
asm("vcvtph2ps %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTPH2PS_VpsWps
asm("vcvtph2ps %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTPH2PS_VpsWps_Kmask
asm("vcvtps2ph $0x70, %zmm0, %ymm0"); 	//BX_ISA_AVX512	_V512_VCVTPS2PH_WpsVpsIb
asm("vcvtps2ph $0x70, %zmm0, %ymm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTPS2PH_WpsVpsIb_Kmask
asm("vmovaps %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVAPS_VpsWps
asm("vmovaps %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVAPS_VpsWps_Kmask
asm("vmovaps %zmm0, (%rdi)"); 	//BX_ISA_AVX512	_V512_VMOVAPS_WpsVps
asm("vmovaps %zmm0, (%rdi){%k1}"); 	//BX_ISA_AVX512	_V512_VMOVAPS_WpsVps_Kmask
asm("vmovapd %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVAPD_VpdWpd
asm("vmovapd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVAPD_VpdWpd_Kmask
asm("vmovapd %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVAPD_WpdVpd
asm("vmovapd %zmm0, (%rdi){%k1}"); 	//BX_ISA_AVX512	_V512_VMOVAPD_WpdVpd_Kmask
asm("vmovups %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVUPS_VpsWps
asm("vmovups %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVUPS_VpsWps_Kmask
asm("vmovups %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVUPS_WpsVps
asm("vmovups %zmm0, (%rdi){%k1}"); 	//BX_ISA_AVX512	_V512_VMOVUPS_WpsVps_Kmask
asm("vmovupd %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVUPD_VpdWpd
asm("vmovupd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVUPD_VpdWpd_Kmask
asm("vmovupd %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVUPD_WpdVpd
asm("vmovupd %zmm0, (%rdi){%k1}"); 	//BX_ISA_AVX512	_V512_VMOVUPD_WpdVpd_Kmask
asm("vmovsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVSD_VsdHpdWsd
asm("vmovss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVSS_VssHpsWss
asm("vmovsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVSD_WsdHpdVsd
asm("vmovss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVSS_WssHpsVss
asm("vmovsd (%rdi), %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVSD_VsdWsd
asm("vmovss (%rdi), %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVSS_VssWss
asm("vmovsd (%rdi), %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVSD_WsdVsd
asm("vmovss (%rdi), %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVSS_WssVss
asm("vmovsd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVSD_VsdHpdWsd_Kmask
asm("vmovss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVSS_VssHpsWss_Kmask
asm("vmovsd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVSD_WsdHpdVsd_Kmask
asm("vmovss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVSS_WssHpsVss_Kmask
asm("vmovsd (%rdi), %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVSD_VsdWsd_Kmask
asm("vmovss (%rdi), %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVSS_VssWss_Kmask
asm("vmovsd %xmm0, (%rdi){%k1}"); 	//BX_ISA_AVX512	_V512_VMOVSD_WsdVsd_Kmask
asm("vmovss %xmm0, (%rdi){%k1}"); 	//BX_ISA_AVX512	_V512_VMOVSS_WssVss_Kmask
asm("vpabsb %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPABSB_VdqWdq
asm("vpabsw %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPABSW_VdqWdq
asm("vpabsd %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPABSD_VdqWdq
asm("vpabsq %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPABSQ_VdqWdq
asm("vpabsb %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPABSB_VdqWdq_Kmask
asm("vpabsw %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPABSW_VdqWdq_Kmask
asm("vpabsd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPABSD_VdqWdq_Kmask
asm("vpabsq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPABSQ_VdqWdq_Kmask
asm("vmovntdqa (%rsi), %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVNTDQA_VdqMdq
asm("vmovntps %zmm0, (%rsi)"); 	//BX_ISA_AVX512	_V512_VMOVNTPS_MpsVps
asm("vmovntpd %zmm0, (%rsi)"); 	//BX_ISA_AVX512	_V512_VMOVNTPD_MpdVpd
asm("vmovntdq %zmm0, (%rsi)"); 	//BX_ISA_AVX512	_V512_VMOVNTDQ_MdqVdq
asm("vpcmpeqb %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512_BW	_V512_VPCMPEQB_KGqHdqWdq
asm("vpcmpeqw %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512_BW	_V512_VPCMPEQW_KGdHdqWdq
asm("vpcmpgtb %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512_BW	_V512_VPCMPGTB_KGqHdqWdq
asm("vpcmpgtw %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512_BW	_V512_VPCMPGTW_KGdHdqWdq
asm("vpcmpeqd %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPEQD_KGwHdqWdq
asm("vpcmpeqq %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPEQQ_KGbHdqWdq
asm("vpcmpgtd %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPGTD_KGwHdqWdq
asm("vpcmpgtq %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPGTQ_KGbHdqWdq
asm("vpsrlw %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSRLW_VdqHdqWdq
asm("vpsrlw %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSRLW_VdqHdqWdq_Kmask
asm("vpsraw %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSRAW_VdqHdqWdq
asm("vpsraw %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSRAW_VdqHdqWdq_Kmask
asm("vpsllw %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSLLW_VdqHdqWdq
asm("vpsllw %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSLLW_VdqHdqWdq_Kmask
asm("vpsrlw $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSRLW_UdqIb
asm("vpsrlw $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSRLW_UdqIb_Kmask
asm("vpsllw $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSLLW_UdqIb
asm("vpsllw $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSLLW_UdqIb_Kmask
asm("vpsraw $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSRAW_UdqIb
asm("vpsraw $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSRAW_UdqIb_Kmask
asm("vpsrld %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRLD_VdqHdqWdq
asm("vpsrlq %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRLQ_VdqHdqWdq
asm("vpsrld %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRLD_VdqHdqWdq_Kmask
asm("vpsrlq %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRLQ_VdqHdqWdq_Kmask
asm("vpslld %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSLLD_VdqHdqWdq
asm("vpsllq %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSLLQ_VdqHdqWdq
asm("vpslld %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSLLD_VdqHdqWdq_Kmask
asm("vpsllq %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSLLQ_VdqHdqWdq_Kmask
asm("vpsrld $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRLD_UdqIb
asm("vpsrld $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRLD_UdqIb_Kmask
asm("vpsrlq $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRLQ_UdqIb
asm("vpsrlq $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRLQ_UdqIb_Kmask
asm("vpslld $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSLLD_UdqIb
asm("vpslld $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSLLD_UdqIb_Kmask
asm("vpsllq $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSLLQ_UdqIb
asm("vpsllq $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSLLQ_UdqIb_Kmask
asm("vpshufb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSHUFB_VdqHdqWdq
asm("vpshufb %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSHUFB_VdqHdqWdq_Kmask
asm("vpermq $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMQ_VdqWdqIb_Kmask
asm("vpermpd $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMPD_VpdWpdIb_Kmask
asm("vshufps $0x70, %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VSHUFPS_VpsHpsWpsIb
asm("vshufpd $0x70, %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VSHUFPD_VpdHpdWpdIb
asm("vshufps $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSHUFPS_VpsHpsWpsIb_Kmask
asm("vshufpd $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSHUFPD_VpdHpdWpdIb_Kmask
asm("vpermilps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPERMILPS_VpsHpsWps
asm("vpermilpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPERMILPD_VpdHpdWpd
asm("vpermilps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMILPS_VpsHpsWps_Kmask
asm("vpermilpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMILPD_VpdHpdWpd_Kmask
asm("vpermilps $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPERMILPS_VpsWpsIb
asm("vpermilpd $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPERMILPD_VpdWpdIb
asm("vpermilps $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMILPS_VpsWpsIb_Kmask
asm("vpermilpd $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMILPD_VpdWpdIb_Kmask
asm("vpshufd $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSHUFD_VdqWdqIb
asm("vpshufd $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSHUFD_VdqWdqIb_Kmask
asm("vpshuflw $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSHUFLW_VdqWdqIb
asm("vpshuflw $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSHUFLW_VdqWdqIb_Kmask
asm("vpshufhw $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSHUFHW_VdqWdqIb
asm("vpshufhw $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSHUFHW_VdqWdqIb_Kmask
asm("vpbroadcastb %ebx, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPBROADCASTB_VdqEb
asm("vpbroadcastb %ebx, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPBROADCASTB_VdqEb_Kmask
asm("vpbroadcastw %ebx, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPBROADCASTW_VdqEw
asm("vpbroadcastw %ebx, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPBROADCASTW_VdqEw_Kmask
asm("vpbroadcastb %xmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPBROADCASTB_VdqWb
asm("vpbroadcastw %xmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPBROADCASTW_VdqWw
asm("vpbroadcastd %xmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPBROADCASTD_VdqWd
asm("vpbroadcastb %xmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPBROADCASTB_VdqWb_Kmask
asm("vpbroadcastw %xmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPBROADCASTW_VdqWw_Kmask
asm("vpbroadcastd %xmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPBROADCASTD_VdqWd_Kmask
asm("vbroadcastss %xmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VBROADCASTSS_VpsWss
asm("vbroadcastss %xmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VBROADCASTSS_VpsWss_Kmask
asm("vmovq (%rdi), %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVQ_WqVq
asm("vmovq %xmm0, (%rdi)"); 	//BX_ISA_AVX512	_V512_VMOVQ_VqWq
asm("vinsertps $0x70, %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VINSERTPS_VpsWssIb
asm("vextractps $0x70, %xmm0, %ebx"); 	//BX_ISA_AVX512	_V512_VEXTRACTPS_EdVpsIb
asm("vmovlps (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVLPS_VpsHpsMq
asm("vmovhps (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVHPS_VpsHpsMq
asm("vmovlps %xmm0, (%rsi)"); 	//BX_ISA_AVX512	_V512_VMOVLPS_MqVps
asm("vmovhps %xmm0, (%rsi)"); 	//BX_ISA_AVX512	_V512_VMOVHPS_MqVps
asm("vmovlpd %xmm0, (%rsi)"); 	//BX_ISA_AVX512	_V512_VMOVLPD_MqVsd
asm("vmovhpd %xmm0, (%rsi)"); 	//BX_ISA_AVX512	_V512_VMOVHPD_MqVsd
asm("vmovlpd (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVLPD_VpdHpdMq
asm("vmovhpd (%rsi), %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVHPD_VpdHpdMq
asm("vmovddup %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVDDUP_VpdWpd
asm("vmovsldup %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVSLDUP_VpsWps
asm("vmovshdup %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVSHDUP_VpsWps
asm("vmovddup %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVDDUP_VpdWpd_Kmask
asm("vmovsldup %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVSLDUP_VpsWps_Kmask
asm("vmovshdup %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVSHDUP_VpsWps_Kmask
asm("vpmovqb %zmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVQB_WdqVdq
asm("vpmovdb %zmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVDB_WdqVdq
asm("vpmovwb %xmm0, %xmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMOVWB_WdqVdq
asm("vpmovdw %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVDW_WdqVdq
asm("vpmovqw %zmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVQW_WdqVdq
asm("vpmovqd %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVQD_WdqVdq
asm("vpmovqb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVQB_WdqVdq_Kmask
asm("vpmovdb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVDB_WdqVdq_Kmask
asm("vpmovwb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMOVWB_WdqVdq_Kmask
asm("vpmovdw %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVDW_WdqVdq_Kmask
asm("vpmovqw %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVQW_WdqVdq_Kmask
asm("vpmovqd %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVQD_WdqVdq_Kmask
asm("vpmovusqb %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVUSQB_WdqVdq
asm("vpmovusdb %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVUSDB_WdqVdq
asm("vpmovuswb %xmm0, %xmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMOVUSWB_WdqVdq
asm("vpmovusdw %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVUSDW_WdqVdq
asm("vpmovusqw %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVUSQW_WdqVdq
asm("vpmovusqd %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVUSQD_WdqVdq
asm("vpmovusqb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVUSQB_WdqVdq_Kmask
asm("vpmovusdb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVUSDB_WdqVdq_Kmask
asm("vpmovuswb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMOVUSWB_WdqVdq_Kmask
asm("vpmovusdw %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVUSDW_WdqVdq_Kmask
asm("vpmovusqw %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVUSQW_WdqVdq_Kmask
asm("vpmovusqd %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVUSQD_WdqVdq_Kmask
asm("vpmovsqb %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVSQB_WdqVdq
asm("vpmovsdb %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVSDB_WdqVdq
asm("vpmovswb %xmm0, %xmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMOVSWB_WdqVdq
asm("vpmovsdw %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVSDW_WdqVdq
asm("vpmovsqw %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVSQW_WdqVdq
asm("vpmovsqd %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVSQD_WdqVdq
asm("vpmovsqb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVSQB_WdqVdq_Kmask
asm("vpmovsdb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVSDB_WdqVdq_Kmask
asm("vpmovswb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMOVSWB_WdqVdq_Kmask
asm("vpmovsdw %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVSDW_WdqVdq_Kmask
asm("vpmovsqw %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVSQW_WdqVdq_Kmask
asm("vpmovsqd %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVSQD_WdqVdq_Kmask
asm("vpmovsxbw %xmm0, %xmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMOVSXBW_VdqWdq
asm("vpmovsxbd %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVSXBD_VdqWdq
asm("vpmovsxbq %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVSXBQ_VdqWdq
asm("vpmovsxwd %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVSXWD_VdqWdq
asm("vpmovsxwq %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVSXWQ_VdqWdq
asm("vpmovsxdq %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVSXDQ_VdqWdq
asm("vpmovsxbw %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMOVSXBW_VdqWdq_Kmask
asm("vpmovsxbd %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVSXBD_VdqWdq_Kmask
asm("vpmovsxbq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVSXBQ_VdqWdq_Kmask
asm("vpmovsxwd %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVSXWD_VdqWdq_Kmask
asm("vpmovsxwq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVSXWQ_VdqWdq_Kmask
asm("vpmovsxdq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVSXDQ_VdqWdq_Kmask
asm("vpmovzxbw %ymm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMOVZXBW_VdqWdq
asm("vpmovzxbd %xmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMOVZXBD_VdqWdq
asm("vpmovzxbq %xmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMOVZXBQ_VdqWdq
asm("vpmovzxwd %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVZXWD_VdqWdq
asm("vpmovzxwq %xmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMOVZXWQ_VdqWdq
asm("vpmovzxdq %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VPMOVZXDQ_VdqWdq
asm("vpmovzxbw %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMOVZXBW_VdqWdq_Kmask
asm("vpmovzxbd %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVZXBD_VdqWdq_Kmask
asm("vpmovzxbq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVZXBQ_VdqWdq_Kmask
asm("vpmovzxwd %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVZXWD_VdqWdq_Kmask
asm("vpmovzxwq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVZXWQ_VdqWdq_Kmask
asm("vpmovzxdq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMOVZXDQ_VdqWdq_Kmask
asm("vpsubb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSUBB_VdqHdqWdq
asm("vpsubsb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSUBSB_VdqHdqWdq
asm("vpsubusb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSUBUSB_VdqHdqWdq
asm("vpsubw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSUBW_VdqHdqWdq
asm("vpsubsw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSUBSW_VdqHdqWdq
asm("vpsubusw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSUBUSW_VdqHdqWdq
asm("vpaddb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPADDB_VdqHdqWdq
asm("vpaddsb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPADDSB_VdqHdqWdq
asm("vpaddusb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPADDUSB_VdqHdqWdq
asm("vpaddw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPADDW_VdqHdqWdq
asm("vpaddsw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPADDSW_VdqHdqWdq
asm("vpaddusw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPADDUSW_VdqHdqWdq
asm("vpsubb %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSUBB_VdqHdqWdq_Kmask
asm("vpsubsb %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSUBSB_VdqHdqWdq_Kmask
asm("vpsubusb %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSUBUSB_VdqHdqWdq_Kmask
asm("vpsubw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSUBW_VdqHdqWdq_Kmask
asm("vpsubsw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSUBSW_VdqHdqWdq_Kmask
asm("vpsubusw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSUBUSW_VdqHdqWdq_Kmask
asm("vpaddb %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPADDB_VdqHdqWdq_Kmask
asm("vpaddsb %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPADDSB_VdqHdqWdq_Kmask
asm("vpaddusb %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPADDUSB_VdqHdqWdq_Kmask
asm("vpaddw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPADDW_VdqHdqWdq_Kmask
asm("vpaddsw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPADDSW_VdqHdqWdq_Kmask
asm("vpaddusw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPADDUSW_VdqHdqWdq_Kmask
asm("vpminsb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMINSB_VdqHdqWdq
asm("vpminub %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMINUB_VdqHdqWdq
asm("vpmaxub %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMAXUB_VdqHdqWdq
asm("vpmaxsb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMAXSB_VdqHdqWdq
asm("vpminsw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMINSW_VdqHdqWdq
asm("vpminuw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMINUW_VdqHdqWdq
asm("vpmaxsw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMAXSW_VdqHdqWdq
asm("vpmaxuw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMAXUW_VdqHdqWdq
asm("vpminsb %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMINSB_VdqHdqWdq_Kmask
asm("vpminub %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMINUB_VdqHdqWdq_Kmask
asm("vpmaxub %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMAXUB_VdqHdqWdq_Kmask
asm("vpmaxsb %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMAXSB_VdqHdqWdq_Kmask
asm("vpminsw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMINSW_VdqHdqWdq_Kmask
asm("vpminuw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMINUW_VdqHdqWdq_Kmask
asm("vpmaxsw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMAXSW_VdqHdqWdq_Kmask
asm("vpmaxuw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMAXUW_VdqHdqWdq_Kmask
asm("vpacksswb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPACKSSWB_VdqHdqWdq
asm("vpacksswb %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPACKSSWB_VdqHdqWdq_Kmask
asm("vpackuswb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPACKUSWB_VdqHdqWdq
asm("vpackuswb %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPACKUSWB_VdqHdqWdq_Kmask
asm("vpackssdw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPACKSSDW_VdqHdqWdq
asm("vpackssdw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPACKSSDW_VdqHdqWdq_Kmask
asm("vpackusdw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPACKUSDW_VdqHdqWdq
asm("vpackusdw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPACKUSDW_VdqHdqWdq_Kmask
asm("vpunpcklbw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPUNPCKLBW_VdqHdqWdq
asm("vpunpcklbw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPUNPCKLBW_VdqHdqWdq_Kmask
asm("vpunpckhbw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPUNPCKHBW_VdqHdqWdq
asm("vpunpckhbw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPUNPCKHBW_VdqHdqWdq_Kmask
asm("vpunpcklwd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPUNPCKLWD_VdqHdqWdq
asm("vpunpcklwd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPUNPCKLWD_VdqHdqWdq_Kmask
asm("vpunpckhwd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPUNPCKHWD_VdqHdqWdq
asm("vpunpckhwd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPUNPCKHWD_VdqHdqWdq_Kmask
asm("vpavgb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPAVGB_VdqHdqWdq
asm("vpavgb %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPAVGB_VdqHdqWdq_Kmask
asm("vpavgw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPAVGW_VdqHdqWdq
asm("vpavgw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPAVGW_VdqHdqWdq_Kmask
asm("vpmaddubsw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMADDUBSW_VdqHdqWdq
asm("vpmaddubsw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMADDUBSW_VdqHdqWdq_Kmask
asm("vpmullw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMULLW_VdqHdqWdq
asm("vpmullw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMULLW_VdqHdqWdq_Kmask
asm("vpmulhw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMULHW_VdqHdqWdq
asm("vpmulhw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMULHW_VdqHdqWdq_Kmask
asm("vpmulhuw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMULHUW_VdqHdqWdq
asm("vpmulhuw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMULHUW_VdqHdqWdq_Kmask
asm("vpmulhrsw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMULHRSW_VdqHdqWdq
asm("vpmulhrsw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMULHRSW_VdqHdqWdq_Kmask
asm("vpsrldq $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSRLDQ_UdqIb
asm("vpslldq $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSLLDQ_UdqIb
asm("vpsadbw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSADBW_VdqHdqWdq
asm("vpmaddwd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMADDWD_VdqHdqWdq
asm("vpmaddwd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPMADDWD_VdqHdqWdq_Kmask
// UD asm("vpmadd52luq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512_IFMA52	_V512_VPMADD52LUQ_VdqHdqWdq
// UD asm("vpmadd52luq %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_IFMA52	_V512_VPMADD52LUQ_VdqHdqWdq_Kmask
// UD asm("vpmadd52huq %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512_IFMA52	_V512_VPMADD52HUQ_VdqHdqWdq
// UD asm("vpmadd52huq %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_IFMA52	_V512_VPMADD52HUQ_VdqHdqWdq_Kmask
// UD asm("vpmultishiftqb %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512_VBMI	_V512_VPMULTISHIFTQB_VdqHdqWdq
// UD asm("vpmultishiftqb %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI	_V512_VPMULTISHIFTQB_VdqHdqWdq_Kmask
// UD asm("vpermb %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI	_V512_VPERMB_VdqHdqWdq_Kmask
asm("vpermw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPERMW_VdqHdqWdq_Kmask
// UD asm("vpermt2b %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI	_V512_VPERMT2B_VdqHdqWdq_Kmask
asm("vpermt2w %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPERMT2W_VdqHdqWdq_Kmask
// UD asm("vpermi2b %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI	_V512_VPERMI2B_VdqHdqWdq_Kmask
asm("vpermi2w %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPERMI2W_VdqHdqWdq_Kmask
asm("vinsertf32x4 $0x70, %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VINSERTF32x4_VpsHpsWpsIb
asm("vinsertf64x2 $0x70, %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VINSERTF64x2_VpdHpdWpdIb
asm("vinsertf32x4 $0x70, %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VINSERTF32x4_VpsHpsWpsIb_Kmask
asm("vinsertf64x2 $0x70, %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VINSERTF64x2_VpdHpdWpdIb_Kmask
asm("vinsertf32x8 $0x70, %ymm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VINSERTF32x8_VpsHpsWpsIb
asm("vinsertf64x4 $0x70, %ymm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VINSERTF64x4_VpdHpdWpdIb
asm("vinsertf32x8 $0x70, %ymm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VINSERTF32x8_VpsHpsWpsIb_Kmask
asm("vinsertf64x4 $0x70, %ymm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VINSERTF64x4_VpdHpdWpdIb_Kmask
asm("vinserti32x4 $0x70, %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VINSERTI32x4_VdqHdqWdqIb
asm("vinserti64x2 $0x70, %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VINSERTI64x2_VdqHdqWdqIb
asm("vinserti32x4 $0x70, %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VINSERTI32x4_VdqHdqWdqIb_Kmask
asm("vinserti64x2 $0x70, %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VINSERTI64x2_VdqHdqWdqIb_Kmask
asm("vinserti32x8 $0x70, %ymm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VINSERTI32x8_VdqHdqWdqIb
asm("vinserti64x4 $0x70, %ymm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VINSERTI64x4_VdqHdqWdqIb
asm("vinserti32x8 $0x70, %ymm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VINSERTI32x8_VdqHdqWdqIb_Kmask
asm("vinserti64x4 $0x70, %ymm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VINSERTI64x4_VdqHdqWdqIb_Kmask
asm("vextractf32x4 $0x70, %zmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VEXTRACTF32x4_WpsVpsIb
asm("vextractf64x2 $0x70, %zmm0, %xmm0"); 	//BX_ISA_AVX512_DQ	_V512_VEXTRACTF64x2_WpdVpdIb
asm("vextractf32x4 $0x70, %zmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VEXTRACTF32x4_WpsVpsIb_Kmask
asm("vextractf64x2 $0x70, %zmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VEXTRACTF64x2_WpdVpdIb_Kmask
asm("vextractf32x8 $0x70, %zmm0, %ymm0"); 	//BX_ISA_AVX512_DQ	_V512_VEXTRACTF32x8_WpsVpsIb
asm("vextractf64x4 $0x70, %zmm0, %ymm0"); 	//BX_ISA_AVX512	_V512_VEXTRACTF64x4_WpdVpdIb
asm("vextractf32x8 $0x70, %zmm0, %ymm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VEXTRACTF32x8_WpsVpsIb_Kmask
asm("vextractf64x4 $0x70, %zmm0, %ymm0{%k1}"); 	//BX_ISA_AVX512	_V512_VEXTRACTF64x4_WpdVpdIb_Kmask
asm("vextracti32x4 $0x70, %zmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VEXTRACTI32x4_WdqVdqIb
asm("vextracti64x2 $0x70, %zmm0, %xmm0"); 	//BX_ISA_AVX512_DQ	_V512_VEXTRACTI64x2_WdqVdqIb
asm("vextracti32x4 $0x70, %zmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VEXTRACTI32x4_WdqVdqIb_Kmask
asm("vextracti64x2 $0x70, %zmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VEXTRACTI64x2_WdqVdqIb_Kmask
asm("vextracti32x8 $0x70, %zmm0, %ymm0"); 	//BX_ISA_AVX512_DQ	_V512_VEXTRACTI32x8_WdqVdqIb
asm("vextracti64x4 $0x70, %zmm0, %ymm0"); 	//BX_ISA_AVX512	_V512_VEXTRACTI64x4_WdqVdqIb
asm("vextracti32x8 $0x70, %zmm0, %ymm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VEXTRACTI32x8_WdqVdqIb_Kmask
asm("vextracti64x4 $0x70, %zmm0, %ymm0{%k1}"); 	//BX_ISA_AVX512	_V512_VEXTRACTI64x4_WdqVdqIb_Kmask
asm("vbroadcastf32x2 %xmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTF32x2_VpsWq
asm("vbroadcastsd %xmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VBROADCASTSD_VpdWsd
asm("vbroadcastf32x2 %xmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTF32x2_VpsWq_Kmask
asm("vbroadcastsd %xmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VBROADCASTSD_VpdWsd_Kmask
asm("vbroadcasti32x2 %xmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTI32x2_VdqWq
asm("vpbroadcastq %xmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPBROADCASTQ_VdqWq
asm("vbroadcasti32x2 %xmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTI32x2_VdqWq_Kmask
asm("vpbroadcastq %xmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPBROADCASTQ_VdqWq_Kmask
asm("vbroadcastf32x4 (%rdi), %zmm0"); 	//BX_ISA_AVX512	_V512_VBROADCASTF32x4_VpsWps
asm("vbroadcastf64x2 (%rdi), %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTF64x2_VpdWpd
asm("vbroadcastf32x4 (%rdi), %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VBROADCASTF32x4_VpsWps_Kmask
asm("vbroadcastf64x2 (%rdi), %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTF64x2_VpdWpd_Kmask
asm("vbroadcastf32x8 (%rdi), %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTF32x8_VpsWps
asm("vbroadcastf64x4 (%rdi), %zmm0"); 	//BX_ISA_AVX512	_V512_VBROADCASTF64x4_VpdWpd
asm("vbroadcastf32x8 (%rdi), %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTF32x8_VpsWps_Kmask
asm("vbroadcastf64x4 (%rdi), %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VBROADCASTF64x4_VpdWpd_Kmask
asm("vbroadcasti32x4 (%rdi), %zmm0"); 	//BX_ISA_AVX512	_V512_VBROADCASTI32x4_VdqWdq
asm("vbroadcasti64x2 (%rdi), %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTI64x2_VdqWdq
asm("vbroadcasti32x4 (%rdi), %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VBROADCASTI32x4_VdqWdq_Kmask
asm("vbroadcasti64x2 (%rdi), %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTI64x2_VdqWdq_Kmask
asm("vbroadcasti32x8 (%rdi), %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTI32x8_VdqWdq
asm("vbroadcasti64x4 (%rdi), %zmm0"); 	//BX_ISA_AVX512	_V512_VBROADCASTI64x4_VdqWdq
asm("vbroadcasti32x8 (%rdi), %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VBROADCASTI32x8_VdqWdq_Kmask
asm("vbroadcasti64x4 (%rdi), %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VBROADCASTI64x4_VdqWdq_Kmask
asm("vpmulld %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMULLD_VdqHdqWdq
asm("vpmullq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VPMULLQ_VdqHdqWdq
asm("vpmulld %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMULLD_VdqHdqWdq_Kmask
asm("vpmullq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VPMULLQ_VdqHdqWdq_Kmask
asm("vpaddd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPADDD_VdqHdqWdq
asm("vpaddq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPADDQ_VdqHdqWdq
asm("vpaddd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPADDD_VdqHdqWdq_Kmask
asm("vpaddq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPADDQ_VdqHdqWdq_Kmask
asm("vpsubd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSUBD_VdqHdqWdq
asm("vpsubq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSUBQ_VdqHdqWdq
asm("vpsubd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSUBD_VdqHdqWdq_Kmask
asm("vpsubq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSUBQ_VdqHdqWdq_Kmask
asm("vpandd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPANDD_VdqHdqWdq
asm("vpandq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPANDQ_VdqHdqWdq
asm("vpandd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPANDD_VdqHdqWdq_Kmask
asm("vpandq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPANDQ_VdqHdqWdq_Kmask
asm("vpandnd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPANDND_VdqHdqWdq
asm("vpandnq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPANDNQ_VdqHdqWdq
asm("vpandnd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPANDND_VdqHdqWdq_Kmask
asm("vpandnq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPANDNQ_VdqHdqWdq_Kmask
asm("vpord %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPORD_VdqHdqWdq
asm("vporq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPORQ_VdqHdqWdq
asm("vpord %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPORD_VdqHdqWdq_Kmask
asm("vporq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPORQ_VdqHdqWdq_Kmask
asm("vpxord %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPXORD_VdqHdqWdq
asm("vpxorq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPXORQ_VdqHdqWdq
asm("vpxord %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPXORD_VdqHdqWdq_Kmask
asm("vpxorq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPXORQ_VdqHdqWdq_Kmask
asm("vandps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VANDPS_VpsHpsWps
asm("vandpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VANDPD_VpdHpdWpd
asm("vandps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VANDPS_VpsHpsWps_Kmask
asm("vandpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VANDPD_VpdHpdWpd_Kmask
asm("vandnps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VANDNPS_VpsHpsWps
asm("vandnpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VANDNPD_VpdHpdWpd
asm("vandnps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VANDNPS_VpsHpsWps_Kmask
asm("vandnpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VANDNPD_VpdHpdWpd_Kmask
asm("vorps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VORPS_VpsHpsWps
asm("vorpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VORPD_VpdHpdWpd
asm("vorps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VORPS_VpsHpsWps_Kmask
asm("vorpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VORPD_VpdHpdWpd_Kmask
asm("vxorps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VXORPS_VpsHpsWps
asm("vxorpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VXORPD_VpdHpdWpd
asm("vxorps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VXORPS_VpsHpsWps_Kmask
asm("vxorpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VXORPD_VpdHpdWpd_Kmask
asm("vpmaxsd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMAXSD_VdqHdqWdq
asm("vpmaxsq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMAXSQ_VdqHdqWdq
asm("vpmaxsd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMAXSD_VdqHdqWdq_Kmask
asm("vpmaxsq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMAXSQ_VdqHdqWdq_Kmask
asm("vpmaxud %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMAXUD_VdqHdqWdq
asm("vpmaxuq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMAXUQ_VdqHdqWdq
asm("vpmaxud %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMAXUD_VdqHdqWdq_Kmask
asm("vpmaxuq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMAXUQ_VdqHdqWdq_Kmask
asm("vpminsd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMINSD_VdqHdqWdq
asm("vpminsq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMINSQ_VdqHdqWdq
asm("vpminsd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMINSD_VdqHdqWdq_Kmask
asm("vpminsq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMINSQ_VdqHdqWdq_Kmask
asm("vpminud %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMINUD_VdqHdqWdq
asm("vpminuq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPMINUQ_VdqHdqWdq
asm("vpminud %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMINUD_VdqHdqWdq_Kmask
asm("vpminuq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPMINUQ_VdqHdqWdq_Kmask
asm("valignd $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VALIGND_VdqHdqWdqIb_Kmask
asm("valignq $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VALIGNQ_VdqHdqWdqIb_Kmask
asm("vpalignr $0x70, %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPALIGNR_VdqHdqWdqIb
asm("vpalignr $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPALIGNR_VdqHdqWdqIb_Kmask
asm("vdbpsadbw $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VDBPSADBW_VdqHdqWdqIb_Kmask
asm("vpsrlvw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSRLVW_VdqHdqWdq
asm("vpsrlvd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRLVD_VdqHdqWdq
asm("vpsrlvq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRLVQ_VdqHdqWdq
asm("vpsravw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSRAVW_VdqHdqWdq
asm("vpsravd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRAVD_VdqHdqWdq
asm("vpsravq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRAVQ_VdqHdqWdq
asm("vpsllvw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPSLLVW_VdqHdqWdq
asm("vpsllvd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSLLVD_VdqHdqWdq
asm("vpsllvq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSLLVQ_VdqHdqWdq
asm("vprolvd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPROLVD_VdqHdqWdq
asm("vprolvq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPROLVQ_VdqHdqWdq
asm("vprorvd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPRORVD_VdqHdqWdq
asm("vprorvq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPRORVQ_VdqHdqWdq
asm("vpsrlvw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSRLVW_VdqHdqWdq_Kmask
asm("vpsrlvd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRLVD_VdqHdqWdq_Kmask
asm("vpsrlvq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRLVQ_VdqHdqWdq_Kmask
asm("vpsravw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSRAVW_VdqHdqWdq_Kmask
asm("vpsravd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRAVD_VdqHdqWdq_Kmask
asm("vpsravq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRAVQ_VdqHdqWdq_Kmask
asm("vpsllvw %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VPSLLVW_VdqHdqWdq_Kmask
asm("vpsllvd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSLLVD_VdqHdqWdq_Kmask
asm("vpsllvq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSLLVQ_VdqHdqWdq_Kmask
asm("vprolvd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPROLVD_VdqHdqWdq_Kmask
asm("vprolvq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPROLVQ_VdqHdqWdq_Kmask
asm("vprorvd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPRORVD_VdqHdqWdq_Kmask
asm("vprorvq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPRORVQ_VdqHdqWdq_Kmask
asm("vpsrad %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRAD_VdqHdqWdq
asm("vpsraq %xmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRAQ_VdqHdqWdq
asm("vpsrad %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRAD_VdqHdqWdq_Kmask
asm("vpsraq %xmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRAQ_VdqHdqWdq_Kmask
asm("vpsrad $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRAD_UdqIb
asm("vpsraq $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPSRAQ_UdqIb
asm("vprord $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPRORD_UdqIb
asm("vprorq $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPRORQ_UdqIb
asm("vprold $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPROLD_UdqIb
asm("vprolq $0x70, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPROLQ_UdqIb
asm("vpsrad $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRAD_UdqIb_Kmask
asm("vpsraq $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPSRAQ_UdqIb_Kmask
asm("vprord $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPRORD_UdqIb_Kmask
asm("vprorq $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPRORQ_UdqIb_Kmask
asm("vprold $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPROLD_UdqIb_Kmask
asm("vprolq $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPROLQ_UdqIb_Kmask
asm("vmovdqu8 %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VMOVDQU8_VdqWdq
asm("vmovdqu16 %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VMOVDQU16_VdqWdq
asm("vmovdqu8 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VMOVDQU8_VdqWdq_Kmask
asm("vmovdqu16 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VMOVDQU16_VdqWdq_Kmask
asm("vmovdqu8 %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VMOVDQU8_WdqVdq
// NI asm("vmovdqu18 %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VMOVDQU18_WdqVdq
asm("vmovdqu8 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VMOVDQU8_WdqVdq_Kmask
asm("vmovdqu16 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_BW	_V512_VMOVDQU16_WdqVdq_Kmask
asm("vmovdqu32 %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVDQU32_VdqWdq
asm("vmovdqu64 %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVDQU64_VdqWdq
asm("vmovdqu32 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVDQU32_VdqWdq_Kmask
asm("vmovdqu64 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVDQU64_VdqWdq_Kmask
asm("vmovdqu32 %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVDQU32_WdqVdq
asm("vmovdqu64 %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVDQU64_WdqVdq
asm("vmovdqu32 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVDQU32_WdqVdq_Kmask
asm("vmovdqu64 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVDQU64_WdqVdq_Kmask
asm("vmovdqa32 %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVDQA32_VdqWdq
asm("vmovdqa64 %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVDQA64_VdqWdq
asm("vmovdqa32 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVDQA32_VdqWdq_Kmask
asm("vmovdqa64 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVDQA64_VdqWdq_Kmask
asm("vmovdqa32 %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVDQA32_WdqVdq
asm("vmovdqa64 %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VMOVDQA64_WdqVdq
asm("vmovdqa32 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVDQA32_WdqVdq_Kmask
asm("vmovdqa64 %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VMOVDQA64_WdqVdq_Kmask
asm("vrangeps $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VRANGEPS_VpsHpsWpsIb_Kmask
asm("vrangepd $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VRANGEPD_VpdHpdWpdIb_Kmask
asm("vrangess $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VRANGESS_VssHpsWssIb_Kmask
asm("vrangesd $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VRANGESD_VsdHpdWsdIb_Kmask
asm("vgetexpps %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VGETEXPPS_VpsWps_Kmask
asm("vgetexppd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VGETEXPPD_VpdWpd_Kmask
asm("vgetexpss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VGETEXPSS_VssHpsWss_Kmask
asm("vgetexpsd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VGETEXPSD_VsdHpdWsd_Kmask
asm("vgetmantps $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VGETMANTPS_VpsWpsIb_Kmask
asm("vgetmantpd $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VGETMANTPD_VpdWpdIb_Kmask
asm("vgetmantss $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VGETMANTSS_VssHpsWssIb_Kmask
asm("vgetmantsd $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VGETMANTSD_VsdHpdWsdIb_Kmask
asm("vscalefps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VSCALEFPS_VpsHpsWps
asm("vscalefpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VSCALEFPD_VpdHpdWpd
asm("vscalefss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VSCALEFSS_VssHpsWss
asm("vscalefsd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VSCALEFSD_VsdHpdWsd
asm("vscalefps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSCALEFPS_VpsHpsWps_Kmask
asm("vscalefpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSCALEFPD_VpdHpdWpd_Kmask
asm("vscalefss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSCALEFSS_VssHpsWss_Kmask
asm("vscalefsd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSCALEFSD_VsdHpdWsd_Kmask
asm("vrcp14ps %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRCP14PS_VpsWps_Kmask
asm("vrcp14pd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRCP14PD_VpdWpd_Kmask
asm("vrcp14ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRCP14SS_VssHpsWss_Kmask
asm("vrcp14sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRCP14SD_VsdHpdWsd_Kmask
asm("vrsqrt14ps %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRSQRT14PS_VpsWps_Kmask
asm("vrsqrt14pd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRSQRT14PD_VpdWpd_Kmask
asm("vrsqrt14ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRSQRT14SS_VssHpsWss_Kmask
asm("vrsqrt14sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VRSQRT14SD_VsdHpdWsd_Kmask
asm("vcvtps2uqq %xmm0, %xmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTPS2UQQ_VdqWps
asm("vcvtpd2uqq %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTPD2UQQ_VdqWpd
asm("vcvtps2uqq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTPS2UQQ_VdqWps_Kmask
asm("vcvtpd2uqq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTPD2UQQ_VdqWpd_Kmask
asm("vcvttps2uqq %xmm0, %xmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTTPS2UQQ_VdqWps
asm("vcvttpd2uqq %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTTPD2UQQ_VdqWpd
asm("vcvttps2uqq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTTPS2UQQ_VdqWps_Kmask
asm("vcvttpd2uqq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTTPD2UQQ_VdqWpd_Kmask
asm("vcvtps2qq %xmm0, %xmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTPS2QQ_VdqWps
asm("vcvtpd2qq %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTPD2QQ_VdqWpd
asm("vcvtps2qq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTPS2QQ_VdqWps_Kmask
asm("vcvtpd2qq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTPD2QQ_VdqWpd_Kmask
asm("vcvttps2qq %xmm0, %xmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTTPS2QQ_VdqWps
asm("vcvttpd2qq %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTTPD2QQ_VdqWpd
asm("vcvttps2qq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTTPS2QQ_VdqWps_Kmask
asm("vcvttpd2qq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTTPD2QQ_VdqWpd_Kmask
asm("vcvttps2udq %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VCVTTPS2UDQ_VdqWps
asm("vcvttpd2udq %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTTPD2UDQ_VdqWpd
asm("vcvttps2udq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTTPS2UDQ_VdqWps_Kmask
asm("vcvttpd2udq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTTPD2UDQ_VdqWpd_Kmask
asm("vcvtps2udq %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VCVTPS2UDQ_VdqWps
asm("vcvtpd2udq %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTPD2UDQ_VdqWpd
asm("vcvtps2udq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTPS2UDQ_VdqWps_Kmask
asm("vcvtpd2udq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTPD2UDQ_VdqWpd_Kmask
asm("vcvtudq2pd %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTUDQ2PD_VpdWdq
asm("vcvtuqq2pd %xmm0, %xmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTUQQ2PD_VpdWdq
asm("vcvtudq2pd %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTUDQ2PD_VpdWdq_Kmask
asm("vcvtuqq2pd %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTUQQ2PD_VpdWdq_Kmask
asm("vcvtudq2ps %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTUDQ2PS_VpsWdq
asm("vcvtuqq2ps %xmm0, %xmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTUQQ2PS_VpsWdq
asm("vcvtudq2ps %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTUDQ2PS_VpsWdq_Kmask
asm("vcvtuqq2ps %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTUQQ2PS_VpsWdq_Kmask
asm("vcvtdq2pd %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTDQ2PD_VpdWdq
asm("vcvtqq2pd %zmm0, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTQQ2PD_VpdWdq
asm("vcvtdq2pd %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTDQ2PD_VpdWdq_Kmask
asm("vcvtqq2pd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTQQ2PD_VpdWdq_Kmask
asm("vcvtdq2ps %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTDQ2PS_VpsWdq
asm("vcvtqq2ps %xmm0, %xmm0"); 	//BX_ISA_AVX512_DQ	_V512_VCVTQQ2PS_VpsWdq
asm("vcvtdq2ps %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCVTDQ2PS_VpsWdq_Kmask
asm("vcvtqq2ps %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VCVTQQ2PS_VpsWdq_Kmask
asm("vfmadd132ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADD132PS_VpsHpsWps
asm("vfmadd132pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADD132PD_VpdHpdWpd
asm("vfmadd213ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADD213PS_VpsHpsWps
asm("vfmadd213pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADD213PD_VpdHpdWpd
asm("vfmadd231ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADD231PS_VpsHpsWps
asm("vfmadd231pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADD231PD_VpdHpdWpd
asm("vfmadd132ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD132PS_VpsHpsWps_Kmask
asm("vfmadd132pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD132PD_VpdHpdWpd_Kmask
asm("vfmadd213ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD213PS_VpsHpsWps_Kmask
asm("vfmadd213pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD213PD_VpdHpdWpd_Kmask
asm("vfmadd231ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD231PS_VpsHpsWps_Kmask
asm("vfmadd231pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD231PD_VpdHpdWpd_Kmask
asm("vfmadd132ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMADD132SS_VpsHssWss
asm("vfmadd132sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMADD132SD_VpdHsdWsd
asm("vfmadd213ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMADD213SS_VpsHssWss
asm("vfmadd213sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMADD213SD_VpdHsdWsd
asm("vfmadd231ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMADD231SS_VpsHssWss
asm("vfmadd231sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMADD231SD_VpdHsdWsd
asm("vfmadd132ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD132SS_VpsHssWss_Kmask
asm("vfmadd132sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD132SD_VpdHsdWsd_Kmask
asm("vfmadd213ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD213SS_VpsHssWss_Kmask
asm("vfmadd213sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD213SD_VpdHsdWsd_Kmask
asm("vfmadd231ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD231SS_VpsHssWss_Kmask
asm("vfmadd231sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADD231SD_VpdHsdWsd_Kmask
asm("vfmaddsub132ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADDSUB132PS_VpsHpsWps
asm("vfmaddsub132pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADDSUB132PD_VpdHpdWpd
asm("vfmaddsub213ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADDSUB213PS_VpsHpsWps
asm("vfmaddsub213pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADDSUB213PD_VpdHpdWpd
asm("vfmaddsub231ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADDSUB231PS_VpsHpsWps
asm("vfmaddsub231pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMADDSUB231PD_VpdHpdWpd
asm("vfmaddsub132ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADDSUB132PS_VpsHpsWps_Kmask
asm("vfmaddsub132pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADDSUB132PD_VpdHpdWpd_Kmask
asm("vfmaddsub213ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADDSUB213PS_VpsHpsWps_Kmask
asm("vfmaddsub213pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADDSUB213PD_VpdHpdWpd_Kmask
asm("vfmaddsub231ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADDSUB231PS_VpsHpsWps_Kmask
asm("vfmaddsub231pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMADDSUB231PD_VpdHpdWpd_Kmask
asm("vfmsubadd132ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUBADD132PS_VpsHpsWps
asm("vfmsubadd132pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUBADD132PD_VpdHpdWpd
asm("vfmsubadd213ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUBADD213PS_VpsHpsWps
asm("vfmsubadd213pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUBADD213PD_VpdHpdWpd
asm("vfmsubadd231ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUBADD231PS_VpsHpsWps
asm("vfmsubadd231pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUBADD231PD_VpdHpdWpd
asm("vfmsubadd132ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUBADD132PS_VpsHpsWps_Kmask
asm("vfmsubadd132pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUBADD132PD_VpdHpdWpd_Kmask
asm("vfmsubadd213ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUBADD213PS_VpsHpsWps_Kmask
asm("vfmsubadd213pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUBADD213PD_VpdHpdWpd_Kmask
asm("vfmsubadd231ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUBADD231PS_VpsHpsWps_Kmask
asm("vfmsubadd231pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUBADD231PD_VpdHpdWpd_Kmask
asm("vfmsub132ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB132PS_VpsHpsWps
asm("vfmsub132pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB132PD_VpdHpdWpd
asm("vfmsub213ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB213PS_VpsHpsWps
asm("vfmsub213pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB213PD_VpdHpdWpd
asm("vfmsub231ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB231PS_VpsHpsWps
asm("vfmsub231pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB231PD_VpdHpdWpd
asm("vfmsub132ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB132PS_VpsHpsWps_Kmask
asm("vfmsub132pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB132PD_VpdHpdWpd_Kmask
asm("vfmsub213ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB213PS_VpsHpsWps_Kmask
asm("vfmsub213pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB213PD_VpdHpdWpd_Kmask
asm("vfmsub231ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB231PS_VpsHpsWps_Kmask
asm("vfmsub231pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB231PD_VpdHpdWpd_Kmask
asm("vfmsub132ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB132SS_VpsHssWss
asm("vfmsub132sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB132SD_VpdHsdWsd
asm("vfmsub213ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB213SS_VpsHssWss
asm("vfmsub213sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB213SD_VpdHsdWsd
asm("vfmsub231ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB231SS_VpsHssWss
asm("vfmsub231sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFMSUB231SD_VpdHsdWsd
asm("vfmsub132ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB132SS_VpsHssWss_Kmask
asm("vfmsub132sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB132SD_VpdHsdWsd_Kmask
asm("vfmsub213ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB213SS_VpsHssWss_Kmask
asm("vfmsub213sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB213SD_VpdHsdWsd_Kmask
asm("vfmsub231ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB231SS_VpsHssWss_Kmask
asm("vfmsub231sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFMSUB231SD_VpdHsdWsd_Kmask
asm("vfnmadd132ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD132PS_VpsHpsWps
asm("vfnmadd132pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD132PD_VpdHpdWpd
asm("vfnmadd213ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD213PS_VpsHpsWps
asm("vfnmadd213pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD213PD_VpdHpdWpd
asm("vfnmadd231ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD231PS_VpsHpsWps
asm("vfnmadd231pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD231PD_VpdHpdWpd
asm("vfnmadd132ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD132PS_VpsHpsWps_Kmask
asm("vfnmadd132pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD132PD_VpdHpdWpd_Kmask
asm("vfnmadd213ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD213PS_VpsHpsWps_Kmask
asm("vfnmadd213pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD213PD_VpdHpdWpd_Kmask
asm("vfnmadd231ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD231PS_VpsHpsWps_Kmask
asm("vfnmadd231pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD231PD_VpdHpdWpd_Kmask
asm("vfnmadd132ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD132SS_VpsHssWss
asm("vfnmadd132sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD132SD_VpdHsdWsd
asm("vfnmadd213ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD213SS_VpsHssWss
asm("vfnmadd213sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD213SD_VpdHsdWsd
asm("vfnmadd231ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD231SS_VpsHssWss
asm("vfnmadd231sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMADD231SD_VpdHsdWsd
asm("vfnmadd132ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD132SS_VpsHssWss_Kmask
asm("vfnmadd132sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD132SD_VpdHsdWsd_Kmask
asm("vfnmadd213ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD213SS_VpsHssWss_Kmask
asm("vfnmadd213sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD213SD_VpdHsdWsd_Kmask
asm("vfnmadd231ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD231SS_VpsHssWss_Kmask
asm("vfnmadd231sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMADD231SD_VpdHsdWsd_Kmask
asm("vfnmsub132ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB132PS_VpsHpsWps
asm("vfnmsub132pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB132PD_VpdHpdWpd
asm("vfnmsub213ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB213PS_VpsHpsWps
asm("vfnmsub213pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB213PD_VpdHpdWpd
asm("vfnmsub231ps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB231PS_VpsHpsWps
asm("vfnmsub231pd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB231PD_VpdHpdWpd
asm("vfnmsub132ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB132PS_VpsHpsWps_Kmask
asm("vfnmsub132pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB132PD_VpdHpdWpd_Kmask
asm("vfnmsub213ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB213PS_VpsHpsWps_Kmask
asm("vfnmsub213pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB213PD_VpdHpdWpd_Kmask
asm("vfnmsub231ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB231PS_VpsHpsWps_Kmask
asm("vfnmsub231pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB231PD_VpdHpdWpd_Kmask
asm("vfnmsub132ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB132SS_VpsHssWss
asm("vfnmsub132sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB132SD_VpdHsdWsd
asm("vfnmsub213ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB213SS_VpsHssWss
asm("vfnmsub213sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB213SD_VpdHsdWsd
asm("vfnmsub231ss %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB231SS_VpsHssWss
asm("vfnmsub231sd %xmm0, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VFNMSUB231SD_VpdHsdWsd
asm("vfnmsub132ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB132SS_VpsHssWss_Kmask
asm("vfnmsub132sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB132SD_VpdHsdWsd_Kmask
asm("vfnmsub213ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB213SS_VpsHssWss_Kmask
asm("vfnmsub213sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB213SD_VpdHsdWsd_Kmask
asm("vfnmsub231ss %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB231SS_VpsHssWss_Kmask
asm("vfnmsub231sd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFNMSUB231SD_VpdHsdWsd_Kmask
asm("vpcmpb $0x70, %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPB_KGqHdqWdqIb
asm("vpcmpw $0x70, %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPW_KGdHdqWdqIb
asm("vpcmpub $0x70, %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPUB_KGqHdqWdqIb
asm("vpcmpuw $0x70, %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPUW_KGdHdqWdqIb
asm("vpcmpd $0x70, %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPD_KGwHdqWdqIb
asm("vpcmpq $0x70, %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPQ_KGbHdqWdqIb
asm("vpcmpud $0x70, %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPUD_KGwHdqWdqIb
asm("vpcmpuq $0x70, %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPCMPUQ_KGbHdqWdqIb
asm("vptestmb %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512_BW	_V512_VPTESTMB_KGqHdqWdq
asm("vptestmw %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512_BW	_V512_VPTESTMW_KGdHdqWdq
asm("vptestnmb %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512_BW	_V512_VPTESTNMB_KGqHdqWdq
asm("vptestnmw %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512_BW	_V512_VPTESTNMW_KGdHdqWdq
asm("vptestmd %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPTESTMD_KGwHdqWdq
asm("vptestmq %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPTESTMQ_KGbHdqWdq
asm("vptestnmd %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPTESTNMD_KGwHdqWdq
asm("vptestnmq %zmm0, %zmm0, %k5"); 	//BX_ISA_AVX512	_V512_VPTESTNMQ_KGbHdqWdq
asm("vpternlogd $0x70, %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPTERNLOGD_VdqHdqWdqIb
asm("vpternlogq $0x70, %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPTERNLOGQ_VdqHdqWdqIb
asm("vpternlogd $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPTERNLOGD_VdqHdqWdqIb_Kmask
asm("vpternlogq $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPTERNLOGQ_VdqHdqWdqIb_Kmask

asm("vgatherdps (%rdi, %zmm0, 1), %zmm1{%k1}"); 	//BX_ISA_AVX512	_V512_VGATHERDPS_VpsVSib
asm("vgatherdpd (%rdi, %xmm0, 1), %xmm1{%k1}"); 	//BX_ISA_AVX512	_V512_VGATHERDPD_VpdVSib
asm("vgatherqps (%rdi, %xmm0, 1), %xmm1{%k1}"); 	//BX_ISA_AVX512	_V512_VGATHERQPS_VpsVSib
asm("vgatherqpd (%rdi, %ymm0, 1), %ymm1{%k1}"); 	//BX_ISA_AVX512	_V512_VGATHERQPD_VpdVSib
// NI asm("vgatherdd (%rdi, %zmm0, 1), %xmm0"); 	//BX_ISA_AVX512	_V512_VGATHERDD_VdqVSib
// NI asm("vgatherdq (%rdi, %zmm0, 1), %xmm0"); 	//BX_ISA_AVX512	_V512_VGATHERDQ_VdqVSib
// NI asm("vgatherqd (%rdi, %zmm0, 1), %xmm0"); 	//BX_ISA_AVX512	_V512_VGATHERQD_VdqVSib
// NI asm("vgatherqq (%rdi, %zmm0, 1), %xmm0"); 	//BX_ISA_AVX512	_V512_VGATHERQQ_VdqVSib
asm("vscatterdps %zmm0, (%rdi, %zmm0, 1){%k1}"); 	//BX_ISA_AVX512	_V512_VSCATTERDPS_VSibVps
asm("vscatterdpd %ymm0, (%rdi, %xmm0, 1){%k1}"); 	//BX_ISA_AVX512	_V512_VSCATTERDPD_VSibVpd
asm("vscatterqps %ymm0, (%rdi, %zmm0, 1){%k1}"); 	//BX_ISA_AVX512	_V512_VSCATTERQPS_VSibVps
asm("vscatterqpd %zmm0, (%rdi, %zmm0, 1){%k1}"); 	//BX_ISA_AVX512	_V512_VSCATTERQPD_VSibVpd
// NI asm("vscatterdd (%rdi, %zmm0, 1), %mm0"); 	//BX_ISA_AVX512	_V512_VSCATTERDD_VSibVdq
// NI asm("vscatterdq (%rdi, %zmm0, 1), %mm0"); 	//BX_ISA_AVX512	_V512_VSCATTERDQ_VSibVdq
// NI asm("vscatterqd (%rdi, %zmm0, 1), %mm0"); 	//BX_ISA_AVX512	_V512_VSCATTERQD_VSibVdq
// NI asm("vscatterqq (%rdi, %zmm0, 1), %mm0"); 	//BX_ISA_AVX512	_V512_VSCATTERQQ_VSibVdq
asm("vblendmps %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VBLENDMPS_VpsHpsWps
asm("vblendmpd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VBLENDMPD_VpdHpdWpd
asm("vpblendmd %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPBLENDMD_VdqHdqWdq
asm("vpblendmq %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPBLENDMQ_VdqHdqWdq
asm("vpblendmb %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPBLENDMB_VdqHdqWdq
asm("vpblendmw %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPBLENDMW_VdqHdqWdq
asm("vshufi32x4 $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSHUFI32x4_VdqHdqWdqIb_Kmask
asm("vshufi64x2 $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSHUFI64x2_VdqHdqWdqIb_Kmask
asm("vshuff32x4 $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSHUFF32x4_VpsHpsWpsIb_Kmask
asm("vshuff64x2 $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VSHUFF64x2_VpdHpdWpdIb_Kmask
asm("vexpandps %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VEXPANDPS_VpsWps
asm("vexpandpd %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VEXPANDPD_VpdWpd
asm("vexpandps %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VEXPANDPS_VpsWps_Kmask
asm("vexpandpd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VEXPANDPD_VpdWpd_Kmask
asm("vcompressps %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VCOMPRESSPS_WpsVps
asm("vcompresspd %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VCOMPRESSPD_WpdVpd
asm("vcompressps %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCOMPRESSPS_WpsVps_Kmask
asm("vcompresspd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VCOMPRESSPD_WpdVpd_Kmask
// UD asm("vpexpandb %xmm0, %xmm0"); 	//BX_ISA_AVX512_VBMI2	_V512_VPEXPANDB_VdqWdq
// UD asm("vpexpandw %xmm0, %xmm0"); 	//BX_ISA_AVX512_VBMI2	_V512_VPEXPANDW_VdqWdq
// UD asm("vpexpandb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPEXPANDB_VdqWdq_Kmask
// UD asm("vpexpandw %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPEXPANDW_VdqWdq_Kmask
asm("vpexpandd %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPEXPANDD_VdqWdq
asm("vpexpandq %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPEXPANDQ_VdqWdq
asm("vpexpandd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPEXPANDD_VdqWdq_Kmask
asm("vpexpandq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPEXPANDQ_VdqWdq_Kmask
// UD asm("vpcompressb %xmm0, %xmm0"); 	//BX_ISA_AVX512_VBMI2	_V512_VPCOMPRESSB_WdqVdq
// UD asm("vpcompressw %xmm0, %xmm0"); 	//BX_ISA_AVX512_VBMI2	_V512_VPCOMPRESSW_WdqVdq
// UD asm("vpcompressb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPCOMPRESSB_WdqVdq_Kmask
// UD asm("vpcompressw %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPCOMPRESSW_WdqVdq_Kmask
asm("vpcompressd %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPCOMPRESSD_WdqVdq
asm("vpcompressq %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VPCOMPRESSQ_WdqVdq
asm("vpcompressd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPCOMPRESSD_WdqVdq_Kmask
asm("vpcompressq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPCOMPRESSQ_WdqVdq_Kmask
asm("vfixupimmss $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFIXUPIMMSS_VssHssWssIb_Kmask
asm("vfixupimmsd $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFIXUPIMMSD_VsdHsdWsdIb_Kmask
asm("vfixupimmps $0x70, %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFIXUPIMMPS_VpsHpsWpsIb
asm("vfixupimmpd $0x70, %zmm0, %zmm0, %zmm0"); 	//BX_ISA_AVX512	_V512_VFIXUPIMMPD_VpdHpdWpdIb
asm("vfixupimmps $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFIXUPIMMPS_VpsHpsWpsIb_Kmask
asm("vfixupimmpd $0x70, %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VFIXUPIMMPD_VpdHpdWpdIb_Kmask
asm("vfpclassps $0x70, %zmm0, %k5{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VFPCLASSPS_KGwWpsIb_Kmask
asm("vfpclasspd $0x70, %zmm0, %k5{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VFPCLASSPD_KGbWpdIb_Kmask
asm("vfpclassss $0x70, %xmm0, %k5{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VFPCLASSSS_KGbWssIb_Kmask
asm("vfpclasssd $0x70, %xmm0, %k5{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VFPCLASSSD_KGbWsdIb_Kmask
asm("vreduceps $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VREDUCEPS_VpsWpsIb_Kmask
asm("vreducepd $0x70, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VREDUCEPD_VpdWpdIb_Kmask
asm("vreducess $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VREDUCESS_VssHpsWssIb_Kmask
asm("vreducesd $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_DQ	_V512_VREDUCESD_VsdHpdWsdIb_Kmask
asm("vpermt2d %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMT2D_VdqHdqWdq_Kmask
asm("vpermt2q %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMT2Q_VdqHdqWdq_Kmask
asm("vpermi2d %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMI2D_VdqHdqWdq_Kmask
asm("vpermi2q %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMI2Q_VdqHdqWdq_Kmask
asm("vpermt2ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMT2PS_VpsHpsWps_Kmask
asm("vpermt2pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMT2PD_VpdHpdWpd_Kmask
asm("vpermi2ps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMI2PS_VpsHpsWps_Kmask
asm("vpermi2pd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMI2PD_VpdHpdWpd_Kmask
asm("vpermd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMD_VdqHdqWdq_Kmask
asm("vpermq %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMQ_VdqHdqWdq_Kmask
asm("vpermps %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMPS_VpsHpsWps_Kmask
asm("vpermpd %zmm0, %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPERMPD_VpdHpdWpd_Kmask
asm("vpconflictd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_CD	_V512_VPCONFLICTD_VdqWdq_Kmask
asm("vpconflictq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_CD	_V512_VPCONFLICTQ_VdqWdq_Kmask
asm("vplzcntd %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_CD	_V512_VPLZCNTD_VdqWdq_Kmask
asm("vplzcntq %zmm0, %zmm0{%k1}"); 	//BX_ISA_AVX512_CD	_V512_VPLZCNTQ_VdqWdq_Kmask
asm("vpmovm2b %k5, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMOVM2B_VdqKEq
asm("vpmovm2w %k5, %zmm0"); 	//BX_ISA_AVX512_BW	_V512_VPMOVM2W_VdqKEd
asm("vpmovm2d %k5, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VPMOVM2D_VdqKEw
asm("vpmovm2q %k5, %zmm0"); 	//BX_ISA_AVX512_DQ	_V512_VPMOVM2Q_VdqKEb
asm("vpmovb2m %zmm0, %k5"); 	//BX_ISA_AVX512_BW	_V512_VPMOVB2M_KGqWdq
asm("vpmovw2m %zmm0, %k5"); 	//BX_ISA_AVX512_BW	_V512_VPMOVW2M_KGdWdq
asm("vpmovd2m %zmm0, %k5"); 	//BX_ISA_AVX512_DQ	_V512_VPMOVD2M_KGwWdq
asm("vpmovq2m %zmm0, %k5"); 	//BX_ISA_AVX512_DQ	_V512_VPMOVQ2M_KGbWdq
// NI asm("vpopcntb %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_BITALG	_V512_VPOPCNTB_VdqWdq_Kmask
// NI asm("vpopcntw %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_BITALG	_V512_VPOPCNTW_VdqWdq_Kmask
// NI asm("vpopcntd %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VPOPCNTDQ	_V512_VPOPCNTD_VdqWdq_Kmask
// NI asm("vpopcntq %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VPOPCNTDQ	_V512_VPOPCNTQ_VdqWdq_Kmask
// NI asm("vpshrd $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHRD_VdqHdqWdqIb_Kmask
// NI asm("vpshrq $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHRQ_VdqHdqWdqIb_Kmask
// NI asm("vpshrdv %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHRDV_VdqHdqWdq_Kmask
// NI asm("vpshrqv %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHRQV_VdqHdqWdq_Kmask
// ??? asm("vpshld $0x70, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHLD_VdqHdqWdqIb_Kmask
// ??? asm("vpshlq $0x70, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHLQ_VdqHdqWdqIb_Kmask
// NI asm("vpshldv %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHLDV_VdqHdqWdq_Kmask
// NI asm("vpshlqv %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHLQV_VdqHdqWdq_Kmask
asm("vpbroadcastd %ebx, %zmm0"); 	//BX_ISA_AVX512	_V512_VPBROADCASTD_VdqEd
asm("vpbroadcastq %rbx, %zmm0"); 	//BX_ISA_AVX512	_V512_VPBROADCASTQ_VdqEq
asm("vpbroadcastd %ebx, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPBROADCASTD_VdqEd_Kmask
asm("vpbroadcastq %rbx, %zmm0{%k1}"); 	//BX_ISA_AVX512	_V512_VPBROADCASTQ_VdqEq_Kmask
asm("vcvtss2si %xmm0, %ebx"); 	//BX_ISA_AVX512	_V512_VCVTSS2SI_GdWss
asm("vcvtss2si %xmm0, %rbx"); 	//BX_ISA_AVX512	_V512_VCVTSS2SI_GqWss
asm("vcvtsd2si %xmm0, %ebx"); 	//BX_ISA_AVX512	_V512_VCVTSD2SI_GdWsd
asm("vcvtsd2si %xmm0, %rbx"); 	//BX_ISA_AVX512	_V512_VCVTSD2SI_GqWsd
asm("vcvttss2si %xmm0, %ebx"); 	//BX_ISA_AVX512	_V512_VCVTTSS2SI_GdWss
asm("vcvttss2si %xmm0, %rbx"); 	//BX_ISA_AVX512	_V512_VCVTTSS2SI_GqWss
asm("vcvttsd2si %xmm0, %ebx"); 	//BX_ISA_AVX512	_V512_VCVTTSD2SI_GdWsd
asm("vcvttsd2si %xmm0, %rbx"); 	//BX_ISA_AVX512	_V512_VCVTTSD2SI_GqWsd
asm("vmovd (%rdi), %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVD_VdqEd
asm("vmovq (%rdi), %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVQ_VdqEq
asm("vmovd (%rdi), %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVD_EdVd
asm("vmovq (%rdi), %xmm0"); 	//BX_ISA_AVX512	_V512_VMOVQ_EqVq
asm("vcvtsi2ss %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTSI2SS_VssEd
asm("vcvtsi2ss %rbx, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTSI2SS_VssEq
asm("vcvtsi2sd %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTSI2SD_VsdEd
asm("vcvtsi2sd %rbx, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTSI2SD_VsdEq
asm("vcvtusi2ss %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTUSI2SS_VssEd
asm("vcvtusi2ss %rbx, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTUSI2SS_VssEq
asm("vcvtusi2sd %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTUSI2SD_VsdEd
asm("vcvtusi2sd %rbx, %xmm0, %xmm0"); 	//BX_ISA_AVX512	_V512_VCVTUSI2SD_VsdEq
asm("vcvtss2usi %xmm0, %ebx"); 	//BX_ISA_AVX512	_V512_VCVTSS2USI_GdWss
asm("vcvtss2usi %xmm0, %rbx"); 	//BX_ISA_AVX512	_V512_VCVTSS2USI_GqWss
asm("vcvtsd2usi %xmm0, %ebx"); 	//BX_ISA_AVX512	_V512_VCVTSD2USI_GdWsd
asm("vcvtsd2usi %xmm0, %rbx"); 	//BX_ISA_AVX512	_V512_VCVTSD2USI_GqWsd
asm("vcvttss2usi %xmm0, %ebx"); 	//BX_ISA_AVX512	_V512_VCVTTSS2USI_GdWss
asm("vcvttss2usi %xmm0, %rbx"); 	//BX_ISA_AVX512	_V512_VCVTTSS2USI_GqWss
asm("vcvttsd2usi %xmm0, %ebx"); 	//BX_ISA_AVX512	_V512_VCVTTSD2USI_GdWsd
asm("vcvttsd2usi %xmm0, %rbx"); 	//BX_ISA_AVX512	_V512_VCVTTSD2USI_GqWsd
asm("vpinsrb $0x70, %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX512_BW	_V512_VPINSRB_VdqEbIb
asm("vpinsrw $0x70, %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX512_BW	_V512_VPINSRW_VdqEwIb
asm("vpextrw $0x70, %xmm0, %ebx"); 	//BX_ISA_AVX512_BW	_V512_VPEXTRW_GdUdqIb
asm("vpextrb $0x70, %xmm0, %rbx"); 	//BX_ISA_AVX512_BW	_V512_VPEXTRB_EbdVdqIb
asm("vpextrw $0x70, %xmm0, %rbx"); 	//BX_ISA_AVX512_BW	_V512_VPEXTRW_EwdVdqIb
asm("vpinsrd $0x70, %ebx, %xmm0, %xmm0"); 	//BX_ISA_AVX512_DQ	_V512_VPINSRD_VdqEdIb
asm("vpinsrq $0x70, %rbx, %xmm0, %xmm0"); 	//BX_ISA_AVX512_DQ	_V512_VPINSRQ_VdqEqIb
asm("vpextrd $0x70, %xmm0, %ebx"); 	//BX_ISA_AVX512_DQ	_V512_VPEXTRD_EdVdqIb
asm("vpextrq $0x70, %xmm0, %rbx"); 	//BX_ISA_AVX512_DQ	_V512_VPEXTRQ_EqVdqIb
asm("vpbroadcastmb2q %k5, %xmm0"); 	//BX_ISA_AVX512	_V512_VPBROADCASTMB2Q_VdqKEb
// REP ERR asm("vpbroadcastmw2d %k5, %xmm0"); 	//BX_ISA_AVX512	_V512_VPBROADCASTMW2D_VdqKEw

//goto end;
// NI asm("vpdpbusd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VNNI	_V512_VPDPBUSD_VdqHdqWdq_Kmask
// NI asm("vpdpbusds %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VNNI	_V512_VPDPBUSDS_VdqHdqWdq_Kmask
// NI asm("vpdpwssd %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VNNI	_V512_VPDPWSSD_VdqHdqWdq_Kmask
// NI asm("vpdpwssds %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VNNI	_V512_VPDPWSSDS_VdqHdqWdq_Kmask
// NI asm("vpshufbitqmb %xmm0, %xmm0, %k5{%k1}"); 	//BX_ISA_AVX512_BITALG	_V512_VPSHUFBITQMB_KGqHdqWdq_Kmask
// NI asm("vpshrw $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHRW_VdqHdqWdqIb_Kmask
// NI asm("vpshrwv %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHRWV_VdqHdqWdq_Kmask
// ??? asm("vpshlw $0x70, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHLW_VdqHdqWdqIb_Kmask
// NI asm("vpshlwv %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_AVX512_VBMI2	_V512_VPSHLWV_VdqHdqWdq_Kmask
//asm("vaesenc %zmm0, %zmm0, %zmm0"); 	//BX_ISA_VAES_VPCLMULQDQ	_V512_VAESENC_VdqHdqWdq
//asm("vaesenclast %zmm0, %zmm0, %zmm0"); 	//BX_ISA_VAES_VPCLMULQDQ	_V512_VAESENCLAST_VdqHdqWdq
//asm("vaesdec %zmm0, %zmm0, %zmm0"); 	//BX_ISA_VAES_VPCLMULQDQ	_V512_VAESDEC_VdqHdqWdq
//asm("vaesdeclast %zmm0, %zmm0, %zmm0"); 	//BX_ISA_VAES_VPCLMULQDQ	_V512_VAESDECLAST_VdqHdqWdq
//asm("vpclmulqdq $0x70, %zmm0, %zmm0, %zmm0"); 	//BX_ISA_VAES_VPCLMULQDQ	_V512_VPCLMULQDQ_VdqHdqWdqIb
// NI asm("vgf2p8affineqb $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_GFNI	_V512_VGF2P8AFFINEQB_VdqHdqWdqIb_Kmask
// UD asm("vgf2p8affineinvqb $0x70, %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_GFNI	_V512_VGF2P8AFFINEINVQB_VdqHdqWdqIb_Kmask
//asm("vgf2p8mulb %xmm0, %xmm0, %xmm0{%k1}"); 	//BX_ISA_GFNI	_V512_VGF2P8MULB_VdqHdqWdq_Kmask
// mismatch = 15

end:

asm("pop %rcx");
asm("pop %rcx");
asm("pop %rax");
asm("pop %rbx");
asm("pop %rdi");
asm("pop %rsi");

//asm("mov %0, %%rdi"::"m"(fpu_state_save):);
//asm("xrstor (%rdi)");

//asm("ud2");
}

char app_name[32];
char app_name_test[32];
int num=0;
int sum(int a)
{
	int i,sum=0;
	for(i=0;i<=a;i++)
		sum+=i;
	return sum;
}

int main(int argc,char *argv[])
{
	int result = 20;
	unsigned long cpu=3;  
	cpu_set_t mask;
	cpu_set_t get;
	struct sigaction s;
	
	s.sa_sigaction = fault_handler;
	s.sa_flags = SA_SIGINFO | SA_ONSTACK;
	sigfillset(&s.sa_mask);
	sigaction(SIGSEGV, &s, NULL);

	CPU_ZERO(&mask);
	CPU_SET(cpu,&mask);
	if(sched_setaffinity(0,sizeof(mask),&mask)==-1)
	{
		printf("Warning:could not set CPU affinity\n");
		return 0;
	}
	sample_start(cpu,app_name_test);
	//result=sum(100);
	instruction_coverage();
	sample_stop(cpu,(char*)0);
	//printf("The result is %d\n", result);
	return 0;
}

