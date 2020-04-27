#include <stdio.h>

void inner_call()
{
	
}

void jmp_far()
{
	//asm()  comment by yanfeng
}

// add by yanfeng
void start_sample()
{
        asm volatile (
                //"mov $102, %%rax\n\t"
                "mov $0x1dab0011, %%eax\n\t"
                "vmcall\n\t"
                :
                :
                :"eax"
        );

}

void stop_sample()
{
        asm volatile (
                //"mov $103, %%rax\n\t"
                "mov $0x1dabFF99, %%eax\n\t"
                "vmcall\n\t"
                :
                :
                :"eax"
        );
        asm volatile (
                //"mov $104, %%rax\n\t"
                "mov $0x1dab5533, %%eax\n\t"
                "vmcall\n\t"
                :
                :
                :"eax"
        );
}
// add by yanfeng done

int instruction_coverage()
{
	void *mem_addr = malloc(0x8000);

asm("push %esi");
asm("push %edi");
asm("push %ebx");
asm("push %eax");
asm("push %ecx");
asm("pushf");

((int *)mem_addr)[0] = (int)inner_call;
((int *)mem_addr)[2] = 0;
((int *)mem_addr)[3] = 1;

asm("mov %0, %%edi"::"r"(mem_addr):);
asm("mov %0, %%esi"::"r"(mem_addr):);

asm("aaa"); 	//0	_AAA
asm("aad"); 	//0	_AAD
asm("aam"); 	//0	_AAM
asm("aas"); 	//0	_AAS
asm("daa"); 	//0	_DAA
asm("das"); 	//0	_DAS

asm("xor %eax, %eax");
asm("bound %ax, 8(%esi)"); 	//0	_BOUND_GwMa
asm("bound %eax, 8(%esi)"); 	//0	_BOUND_GdMa
asm("arpl %ax, %ax"); 	//0	_ARPL_EwGw
asm("mov %0, %%eax"::"r"(inner_call):);
asm("call *%eax"); 	//0	_CALL_Ed

// 16 bit asm("call *%cs:(%dx)"); 	//0	_CALLF_Op16_Ap
asm("call %cs:inner_call"); 	//0	_CALLF_Op32_Ap
// 16 bit asm("call %eax"); 	//0	_CALLF_Op16_Ep
asm("call *%cs:(%edi)"); 	//0	_CALLF_Op32_Ep

asm("enter $0x1000, $0x0"); 	//0	_ENTER_Op16_IwIb
asm("enter $0x1000, $0x1"); 	//0	_ENTER_Op32_IwIb
asm("leave"); 	//0	_LEAVE_Op16
asm("leave"); 	//0	_LEAVE_Op32


asm("jmp %cs:jmpf1_next \n\t"
"jmpf1_next: \n\t"); //0	_JMPF_Ap

// 16-bit asm("jmp %ebx"); 	//0	_JMPF_Op16_Ep
asm("movl $jmpf2_next, 20(%edi) \n\t"
"jmp *%cs:20(%edi) \n\t"
"jmpf2_next: \n\t"); 	//0	_JMPF_Op32_Ep

asm("jcxz jcxz_Jb \n\t jcxz_Jb:\n\t"); 	//0	_JCXZ_Jb
asm("jecxz jecxz_Jb \n\t jecxz_Jb:\n\t"); 	//0	_JECXZ_Jb
// 16-bit asm("loop LOOP_Jb \n\t LOOP_Jb:\n\t"); 	//0	_LOOP_Op16_Jb
// 16-bit asm("loope LOOPE_Jb \n\t LOOPE_Jb:\n\t"); 	//0	_LOOPE_Op16_Jb
// 16-bit asm("loopne LOOPNE_Jb \n\t LOOPNE_Jb:\n\t"); 	//0	_LOOPNE_Op16_Jb
asm("loop LOOP_Jb \n\t LOOP_Jb:\n\t"); 	//0	_LOOP_Op32_Jb
asm("loope LOOPE_Jb \n\t LOOPE_Jb:\n\t"); 	//0	_LOOPE_Op32_Jb
asm("loopne LOOPNE_Jb \n\t LOOPNE_Jb:\n\t"); 	//0	_LOOPNE_Op32_Jb
asm("jb jb_Jw \n\t jb_Jw:\n\t"); 	//0	_JB_Jw
asm("jbe jbe_Jw \n\t jbe_Jw:\n\t"); 	//0	_JBE_Jw
asm("jl jl_Jw \n\t jl_Jw:\n\t"); 	//0	_JL_Jw
asm("jle jle_Jw \n\t jle_Jw:\n\t"); 	//0	_JLE_Jw
asm("jnb jnb_Jw \n\t jnb_Jw:\n\t"); 	//0	_JNB_Jw
asm("jnbe jnbe_Jw \n\t jnbe_Jw:\n\t"); 	//0	_JNBE_Jw
asm("jnl jnl_Jw \n\t jnl_Jw:\n\t"); 	//0	_JNL_Jw
asm("jnle jnle_Jw \n\t jnle_Jw:\n\t"); 	//0	_JNLE_Jw
asm("jno jno_Jw \n\t jno_Jw:\n\t"); 	//0	_JNO_Jw
asm("jnp jnp_Jw \n\t jnp_Jw:\n\t"); 	//0	_JNP_Jw
asm("jns jns_Jw \n\t jns_Jw:\n\t"); 	//0	_JNS_Jw
asm("jnz jnz_Jw \n\t jnz_Jw:\n\t"); 	//0	_JNZ_Jw
asm("jo jo_Jw \n\t jo_Jw:\n\t"); 	//0	_JO_Jw
asm("jp jp_Jw \n\t jp_Jw:\n\t"); 	//0	_JP_Jw
asm("js js_Jw \n\t js_Jw:\n\t"); 	//0	_JS_Jw
asm("jz jz_Jw \n\t jz_Jw:\n\t"); 	//0	_JZ_Jw
asm("jb jb_Jd \n\t jb_Jd:\n\t"); 	//0	_JB_Jd
asm("jbe jbe_Jd \n\t jbe_Jd:\n\t"); 	//0	_JBE_Jd
asm("jl jl_Jd \n\t jl_Jd:\n\t"); 	//0	_JL_Jd
asm("jle jle_Jd \n\t jle_Jd:\n\t"); 	//0	_JLE_Jd
asm("jnb jnb_Jd \n\t jnb_Jd:\n\t"); 	//0	_JNB_Jd
asm("jnbe jnbe_Jd \n\t jnbe_Jd:\n\t"); 	//0	_JNBE_Jd
asm("jnl jnl_Jd \n\t jnl_Jd:\n\t"); 	//0	_JNL_Jd
asm("jnle jnle_Jd \n\t jnle_Jd:\n\t"); 	//0	_JNLE_Jd
asm("jno jno_Jd \n\t jno_Jd:\n\t"); 	//0	_JNO_Jd
asm("jnp jnp_Jd \n\t jnp_Jd:\n\t"); 	//0	_JNP_Jd
asm("jns jns_Jd \n\t jns_Jd:\n\t"); 	//0	_JNS_Jd
asm("jnz jnz_Jd \n\t jnz_Jd:\n\t"); 	//0	_JNZ_Jd
asm("jo jo_Jd \n\t jo_Jd:\n\t"); 	//0	_JO_Jd
asm("jp jp_Jd \n\t jp_Jd:\n\t"); 	//0	_JP_Jd
asm("js js_Jd \n\t js_Jd:\n\t"); 	//0	_JS_Jd
asm("jz jz_Jd \n\t jz_Jd:\n\t"); 	//0	_JZ_Jd

asm("mov %ds, %ax");
asm("mov %ax, 32(%esi)");
asm("movl $0, 36(%esi)");
//asm("lds 32(%esi), %eax"); 	//0	_LDS_GdMp
//asm("lds 32(%esi), %bx"); 	//0	_LDS_GwMp

asm("mov %es, %ax");
asm("mov %ax, 32(%esi)");
asm("movl $0, 36(%esi)");
//asm("les 32(%esi), %eax"); 	//0	_LES_GdMp
//asm("les 32(%esi), %ax"); 	//0	_LES_GwMp

asm("into"); 	//0	_INTO

asm("pusha");
asm("popa");

	free(mem_addr);

asm("popf");
asm("pop %ecx");
asm("pop %eax");
asm("pop %ebx");
asm("pop %edi");
asm("pop %esi");
}
int main()
{
	instruction_coverage();
	return 0;
}
