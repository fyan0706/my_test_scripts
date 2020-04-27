#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>
#define __USE_GNU
#include<sched.h>
#include "sampling.h"

#define filename(x) strrchr(x,'/')?strrchr(x,'/')+1:x
char app_name[32];
char app_name_test[32];
int num=0;

int test(void);
void signal_init(void);

int main(int argc,char *argv[])
{
    signal_init();

    sample_start_mtr();

    test();

    sample_stop_mtr();

    return 0;
}

