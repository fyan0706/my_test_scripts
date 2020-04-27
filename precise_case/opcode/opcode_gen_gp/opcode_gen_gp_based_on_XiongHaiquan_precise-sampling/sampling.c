#include"sampling.h"

void sample_start(unsigned long cpu,char name[])
{
		kvm_hypercall2(KVM_HC_PCM_SAMPLE_START,cpu,(unsigned long)name);
}
void sample_stop(unsigned long cpu,char name[])
{
		kvm_hypercall2(KVM_HC_PCM_SAMPLE_STOP,cpu,(unsigned long)name);
}
