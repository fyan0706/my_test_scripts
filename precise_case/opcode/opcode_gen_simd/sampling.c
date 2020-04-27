#include<stdio.h>
#include"sampling.h"
#include <signal.h>




void sample_start_mtr(void)
{
    asm volatile (
        "mov $102, %%rax\n\t"
        ".byte 0x0f\n\t"
        ".byte 0x01\n\t"
        ".byte 0xc1\n\t"
        :
        :
        :"rax"
    );
}



void sample_stop_mtr(void)
{
    asm volatile (
        "mov $103, %%rax\n\t"
        ".byte 0x0f\n\t"
        ".byte 0x01\n\t"
        ".byte 0xc1\n\t"
        :
        :
        :"rax"
    );
}



void signal_handler(int a, siginfo_t *b, void *c)
{
    sample_stop_mtr();
}



void signal_init(void)
{
    struct sigaction s;

    s.sa_sigaction = signal_handler;
    s.sa_flags = SA_SIGINFO | SA_ONSTACK;

    sigfillset(&s.sa_mask);


    sigaction(SIGILL, &s, NULL);
    sigaction(SIGSEGV, &s, NULL);
    sigaction(SIGFPE, &s, NULL);
    sigaction(SIGBUS, &s, NULL);
    sigaction(SIGTRAP, &s, NULL);
}





