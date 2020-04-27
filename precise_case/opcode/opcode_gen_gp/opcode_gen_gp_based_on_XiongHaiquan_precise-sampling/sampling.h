#include <linux/types.h>
#include <linux/kvm.h>
#define KVM_HC_PCM_SAMPLE_START 102
#define KVM_HC_PCM_SAMPLE_STOP 103
#define KVM_HYPERCALL ".byte 0x0f,0x01,0xc1"//vmcall指令的机器码
static inline long kvm_hypercall0(unsigned int nr)
{
        long ret;
        asm volatile(KVM_HYPERCALL
                     : "=a"(ret)
                     : "a"(nr)//传递vmcall调用号，与eax寄存器绑定，本例中使用102和103两个系统调用号
                     : "memory");
        return ret;
}

static inline long kvm_hypercall1(unsigned int nr, unsigned long p1)
{
        long ret;
        asm volatile(KVM_HYPERCALL
                     : "=a"(ret)
                     : "a"(nr), "b"(p1)
                     : "memory");
        return ret;
}

static inline long kvm_hypercall2(unsigned int nr, unsigned long p1,
                                  unsigned long p2)
{
        long ret;
        asm volatile(KVM_HYPERCALL
                     : "=a"(ret)
                     : "a"(nr), "b"(p1), "c"(p2)
                     : "memory");
        return ret;
}


static inline long kvm_hypercall3(unsigned int nr, unsigned long p1,
                                  unsigned long p2, unsigned long p3)
{
        long ret;
        asm volatile(KVM_HYPERCALL
                     : "=a"(ret)
                     : "a"(nr), "b"(p1), "c"(p2), "d"(p3)
                     : "memory");
        return ret;
}

static inline long kvm_hypercall4(unsigned int nr, unsigned long p1,
                                  unsigned long p2, unsigned long p3,
                                  unsigned long p4)
{
        long ret;
        asm volatile(KVM_HYPERCALL
                     : "=a"(ret)
                     : "a"(nr), "b"(p1), "c"(p2), "d"(p3), "S"(p4)
                     : "memory");
        return ret;
}

//static void kvm_sample_hypercall (unsigned long action);
extern void sample_start(unsigned long,char[]);
extern void sample_stop(unsigned long,char[]);

