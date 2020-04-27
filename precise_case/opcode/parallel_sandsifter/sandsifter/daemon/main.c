#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "../circ_buf.h"


#define TOTAL_RANGE_LEN (256*256)
#define STEP_LEN (4)
#define TOTAL_PROCESSES (60)

enum ps_status{
  PS_IDLE,
  PS_RUNNING,
  PS_STUCK
};

struct step_process_status{
    char start[31];
    char end[31];
    char app_name[100];
    char cmd[200];
    unsigned int cur_step;
    int skiped_steps;
    unsigned char last_inject_bytes[16];
    //length of last injected instruction bytes, -1 means has not received any injections from sandsifter;
    int last_inj_bytes_len;
    //counter for process status change into PS_STUCK which means failure.
    unsigned int total_failed_count;
    char last_failed_start[31];
    //counter for testing last start bytes.
    int last_start_test_count;
    unsigned int inst_count;
    unsigned int inst_count_since_last_message;
    unsigned int inst_count_no_changed_count;
    //the time at which current process started or receive a message, this is used to determine if current process is stuck or not.
    struct timespec  time_value;
    enum ps_status status;
};

static struct timespec  last_check_time={0};

/*
 * @brief Get last instruction bytes
 * @param file_name[in] - log file name
 * @param p_last_inst[in|out] - instruction bytes
 * @retval -2 log file exist, but data corrupted.
 * @retval -1 no corresponding log file
 * @retval 1  corresponding rang has been finished.
 * @retval 0  success get instruction bytes. 
 */
int get_last_instruction(char* file_name,char* p_last_inst)
{
    
	FILE* fp=NULL;
    char minus_3_line[4096]={0};
    char minus_2_line[4096]={0};
    char minus_1_line[4096]={0};
    char last_line[4096]={0};
    char *p_cur_line[]={last_line,minus_1_line,minus_2_line,minus_3_line};
    int i=0;
    int j=0;
    int cur_line=0;
    char *sig_str[]={"sigill ","sigsegv","sigfpe ","sigbus ","sigtrap"};
    char last_inst[30]={0};
    char *p = NULL;

    fp=fopen(file_name,"r");
    if(NULL != fp)
    {
    	while(!feof(fp))  
    	{
            memcpy(minus_3_line,minus_2_line,sizeof(minus_3_line));
            memcpy(minus_2_line,minus_1_line,sizeof(minus_2_line));
            memcpy(minus_1_line,last_line,sizeof(minus_1_line));
            if(!fgets(last_line,sizeof(last_line),fp))
                break;
            if((0 == strcmp(last_line,"lazarus\n")) || (0 == strcmp(minus_1_line,"lazarus\n")))
            {
                return 1;
            }
    	}
    	fclose(fp);
    }
    else
    {
        //printf("Can't open %s file.\n",file_name);
        return -1;
    }

#if 0
    printf("minus_3_line:%s\n",minus_3_line);
    printf("minus_2_line:%s\n",minus_2_line);
    printf("minus_1_line:%s\n",minus_1_line);
    printf("last_line:%s\n",last_line);
#endif    

    for(cur_line=0;cur_line<sizeof(p_cur_line)/sizeof(p_cur_line[0]);cur_line++)
    {
        for(i=0;i<sizeof(sig_str)/sizeof(sig_str[0]);i++)
        {
            if(p = strstr(p_cur_line[cur_line]+77,sig_str[i]))
            {
                break;
            }
        }
        
        if(sizeof(sig_str)/sizeof(sig_str[0]) == i)
        {
            //printf("Error:Not found last instruction!,file_name=[%s]\n",file_name);
        }
        else
        {
            i=0;
            j=0;
            
            while(p[10+i])
            {
                if(isxdigit(p[10+i]))
                {
                    if(j>=sizeof(last_inst))
                    {
                        printf("Error:Too many instruction bytes!,j=%d,sizeof(last_inst)=%ld\n",j,sizeof(last_inst));
                        return -2;
                    }
                    last_inst[j]=p[10+i];
                    j++;
                }
                i++;
            }
            if(0 == strlen(last_inst) || 0 != (strlen(last_inst)%2))
            {
                printf("Invalid instruction:[%s]\n",last_inst);
                continue;
            }

            memcpy(p_last_inst,last_inst,31);
            return 0;
        }
    }
    
	return -2;
}

static int ProcessIsRun(char *proc)
{
    FILE* fp = NULL; 
    unsigned char count = 1; 
    unsigned char BUFSZ = 100; 
    char buf[BUFSZ]; 
    char command[150]; 
 
    sprintf(command, "pidof -x %s > /dev/null", proc); 

    if(0 == system(command))
    {
        return 0;
    }

    return -1;
}

void increment_instruction(char inst[31], int *p_max_index)
{
    char bytes[16]={0};
    int i=0;
    int j=0;
    int m=0;
    char n[3]={0};
    int max_index=*p_max_index;
    
    for(i=0;i<=max_index;i++)
    {
        n[0]=inst[j++];
        n[1]=inst[j++];
        m=strtol(n,NULL,16);
        bytes[i]=m&0xFF;
        //printf("%02X\n",bytes[i]&0xFF);
    }

    max_index=((max_index+1)/2-1);

    bytes[max_index]++;
    
    while (max_index>=0 && bytes[max_index]==0) {
        max_index--;
        if (max_index>=0) {
            bytes[max_index]++;
        }
    }

    for(i=0;i<=max_index;i++)
    {
        sprintf(n,"%02X",bytes[i]&0xFF);
        strcpy(inst+i*2,n);
    }

    max_index=((max_index+1)*2-1);
    
    *p_max_index = max_index;
    
}

/*
 * @brief Create new process
 * @param cur_step[in] - current step number.
 * @retval 1 current step has been finished.
 * @retval 0 created new process. 
 */
int run_new_process(unsigned int cur_step,struct step_process_status *ps)
{
    char log_file_name[100]={0};
    int log_file_status=0;
    char last_inst[31]={0};    
    struct timespec  time_value;
    char cmd[200]={0};
    char original_start[31]={0};
    int i=0;

    sprintf(original_start,"%02X%02X00000000000000000000000000",cur_step>>8,cur_step&0xFF);
    sprintf(ps->app_name,"./injector_%02d",cur_step);
#if 0
    if(-1 == ps->last_inj_bytes_len)
    {
        sprintf(log_file_name,"log_file_%d",cur_step);
        log_file_status = get_last_instruction(log_file_name, last_inst);   

        if(1 == log_file_status)
        {
            printf("step %d has been finished\n",cur_step);
            return 1;
        }

        sprintf(ps->app_name,"./injector_%02d",cur_step);
        ps->cur_step=cur_step;

        if(0 != log_file_status)
        {
            unsigned int new_step = cur_step;

            //if data corrupted and failed several times, skip this value.
            if(-2 == log_file_status && ps->total_failed_count>2)
            {
                ps->skiped_steps++;
                new_step = cur_step+ps->skiped_steps;
                printf("new start step for %d step stage:%d.\n",cur_step,new_step);
            }
            sprintf(ps->start,"%02X%02X00000000000000000000000000",new_step>>8,new_step&0xFF);
        }
        else
        {
            memcpy(ps->start,last_inst,30);
        }

        if(0 == memcmp(ps->start,ps->last_failed_start,30))
        {
            ps->last_start_test_count++;
        }
        else
        {
            memcpy(ps->last_failed_start,ps->start,30);
            ps->last_start_test_count=0;
        }

        if(ps->last_start_test_count>0)
        {
            int max_index=0;
            printf("Process %s failed at %s for %d times, move to next instruction,total_failed_count=%d.\n",
                ps->app_name,ps->start,ps->last_start_test_count,ps->total_failed_count);
            max_index=strlen(last_inst)-1;
            increment_instruction(last_inst,&max_index);               
            memcpy(ps->start,last_inst,max_index+1);
        }
    }
    else
    {
        char bytes[16]={0};
        int j=0;
        int m=0;
        int max_index = ps->last_inj_bytes_len;

		while (max_index>=0 && ps->last_inject_bytes[max_index]==0) {
			max_index--;
			if (max_index>=0) {
				ps->last_inject_bytes[max_index]++;
			}
		}

        for(i=0;i<=max_index;i++)
        {
            sprintf(ps->start+i*2,"%02X",ps->last_inject_bytes[i]&0xFF);
        }
    }
    
    for(i=0;i<sizeof(ps->start)-1;i++)
    {
        if(0 == ps->start[i])
        {
            ps->start[i]='0';
        }
    }
#endif
    sprintf(ps->start,"%02X%02X00000000000000000000000000",cur_step>>8,cur_step&0xFF);
    sprintf(ps->end,"%02X%02XFFFFFFFFFFFFFFFFFFFFFFFFFF",(cur_step + STEP_LEN-1)>>8,(cur_step + STEP_LEN-1)&0xFF);

    //printf("%s,%d,cur_step=%d,start=[%s],end=[%s]\n",__FILE__,__LINE__,cur_step,ps->start,ps->end);

    if(-1 == ProcessIsRun(ps->app_name))
    {
        sprintf(cmd,"cp ../injector ./injector_%02d",cur_step);
        system(cmd);
        sprintf(ps->cmd,"nice -n 19 ./injector_%02d  -P2 -t -0 -z %02X -i %s -e %s &",cur_step,cur_step,ps->start,ps->end);  
        //printf("ps->cmd=[%s]\n",ps->cmd);
        system(ps->cmd);
    }
    ps->status=PS_RUNNING;
    return 0;
}

int fd_mem;
int fd_sem;
int fd_cbuf;
sem_t* psem;
sem_t* pmutex;
struct sf_msg *p_shmem;
struct circ_buf *p_cbuf;

int receive_msg(struct sf_msg *item)
{
    int ret=0;
    int val=0;
    sem_getvalue(psem,&val);
    //printf("%s,%d,main.c psem's val=%d.\n",__FILE__,__LINE__,val);s
    if(0 == sem_trywait(psem))
    {
        //printf("%s,%d\n",__FILE__,__LINE__);
        if (CIRC_CNT(p_cbuf->head, p_cbuf->tail, NODE_NUMBER) >= 1) {
            /* extract one item from the buffer */
            memcpy(item,&p_shmem[p_cbuf->tail],sizeof(struct sf_msg));
            //printf("head=%d,tail=%d,p_cbuf->head=%d,p_cbuf->tail=%d\n",item->head,item->tail,p_cbuf->head,p_cbuf->tail);
            p_cbuf->tail = (p_cbuf->tail + 1) & (NODE_NUMBER - 1);
        }
        else
        {
            ret = 1;
        }
    }
    else
    {
        ret=1;
    }

    return ret;
}

int main(void)
{
    struct step_process_status ps[TOTAL_PROCESSES]={0};
    unsigned int cur_step=0;
    struct sched_param param;
    sched_setscheduler( 0, SCHED_FIFO, &param);  

    unlink(SHARE_MEM_FILE);
	fd_mem=open(SHARE_MEM_FILE,O_CREAT|O_RDWR|O_TRUNC,00777);
    ftruncate(fd_mem,sizeof(struct sf_msg)*NODE_NUMBER);
	p_shmem = (struct sf_msg*) mmap( NULL,sizeof(struct sf_msg)*NODE_NUMBER,PROT_READ|PROT_WRITE,MAP_SHARED,fd_mem,0 );
	close( fd_mem );

    unlink(SHARE_CBUF_FILE);
	fd_cbuf=open(SHARE_CBUF_FILE,O_CREAT|O_RDWR|O_TRUNC,00777);
	ftruncate(fd_cbuf,sizeof(struct circ_buf));
	p_cbuf = (struct circ_buf *) mmap( NULL,sizeof(struct circ_buf),PROT_READ|PROT_WRITE,MAP_SHARED,fd_cbuf,0 );
	close( fd_cbuf );

    sem_unlink(SHARE_SEM_FILE);
	psem = sem_open(SHARE_SEM_FILE, O_CREAT | O_EXCL, 0644, 0);
	if(SEM_FAILED == psem)
	{
		perror("sem_open");
	}
    
	sem_unlink(SHARE_MEM_MUTEX);
	pmutex= sem_open(SHARE_MEM_MUTEX, O_CREAT | O_EXCL, 0644, 1);
	if(SEM_FAILED == pmutex)
	{
		perror("sem_open");
	}
	p_cbuf->head=0;
	p_cbuf->tail=0;

    clock_gettime(CLOCK_REALTIME, &last_check_time);

    while(1)
    {
        char cmd[200]={0};
        struct sf_msg msg={0};
        struct timespec  time_value;
        signed long long i;
        signed long long j;
#if 1
        //printf("try to create new process\n");
        for(i=0;i<TOTAL_PROCESSES;i++)
        {
            if(PS_IDLE == ps[i].status && 65536 > cur_step)
            {
                memset(&ps[i],0,sizeof(ps[i]));

                if(0 == run_new_process(cur_step,&ps[i]))
                {
                    cur_step+=STEP_LEN;
                }
                else
                {
                    cur_step+=STEP_LEN;
                }
            }
        }
#endif

        clock_gettime(CLOCK_REALTIME, &time_value);

        if((last_check_time.tv_sec+5)< time_value.tv_sec)
        {
            for(i=0;i<TOTAL_PROCESSES;i++)
            {
                if(-1 == ProcessIsRun(ps[i].app_name))
                {
                    sprintf(cmd,"rm -f %s  >/dev/null 2>&1",ps[i].app_name);
                    system(cmd);
                    ps[i].status = PS_IDLE;
                }
            }
            memcpy(&last_check_time,&time_value,sizeof(struct timespec));
        }

        sleep(1);
        
#if 0
        if(i == TOTAL_PROCESSES)
        {
            printf("All processes are running now\n");
            if(0 != ProcessIsRun(ps[i].app_name))
            {
                sprintf(start,"%02X0000000000000000000000000000",i*STEP_LEN);
                sprintf(end,"%02XFFFFFFFFFFFFFFFFFFFFFFFFFFFF",(i+1)*STEP_LEN-1);
                sprintf(cmd,"./injector_%02d  -P2 -t -0 -z %02X -i %s -e %s &",i*STEP_LEN,i*STEP_LEN,start,end);
                //system(cmd);
                printf("cmd=[%s]\n",cmd);
                system(cmd);
            }                
            exit(1);
        }
        else
        {
            cur_step+=STEP_LEN;
        }
#endif        
    }

#if 0    
#define STEP_LEN (32)
#if (0!= (256%STEP_LEN))
#error "Wrong STEP_LEN value"
#endif

    char last_inst[30]={0};
    int i = 0;
    int err=0;
    char cur_log_file_name[100]={0};
    char log_file_names[256/STEP_LEN][100]={0};
    char cmd[100]={0};

    for(i=0;i<256/STEP_LEN;i++)
    {
        sprintf(log_file_names[i],"log_file_%02d",i*STEP_LEN);
        printf("log_file_names[%d]=[%s]\n",i,log_file_names[i]);
    }

    for(i=0;i<256/STEP_LEN;i++)
    {
        sprintf(cmd,"cp ../injector ./injector_%02d",i*STEP_LEN);
        system(cmd);
    }

    for(i=0;i<256/STEP_LEN;i++)
    {
        char start[31]={0};
        char end[31]={0};

        sprintf(cmd,"injector_%02d",i*STEP_LEN);
        if(0 != ProcessIsRun(cmd))
        {
            sprintf(start,"%02X0000000000000000000000000000",i*STEP_LEN);
            sprintf(end,"%02XFFFFFFFFFFFFFFFFFFFFFFFFFFFF",(i+1)*STEP_LEN-1);
            sprintf(cmd,"./injector_%02d  -P2 -t -0 -z %02X -i %s -e %s &",i*STEP_LEN,i*STEP_LEN,start,end);
            //system(cmd);
            printf("cmd=[%s]\n",cmd);
            system(cmd);
        }
    }

    strcpy(cur_log_file_name,"../log_file_64");

    if(0 == (err = get_last_instruction(cur_log_file_name,last_inst)))
    {
        printf("last instruction is [%s]\n",last_inst);
    }
    else
    {
        printf("Error:log file \"%s\" not exist or corruptted.\n",cur_log_file_name);
    }
#endif    

#if 0
                            char str[100]={0};
                            unsigned long long total=TOTAL_RANGE_LEN;
                            unsigned int count=0;
                            
                            do
                            {
                                strcat(str,"%02X");
                                count++;
                            }while(1!=(total=(total/256)));
                            for(j=0;j<30-count*2;j++)
                            {
                                strcat(str,"0");
                            }
                            printf("str=[%s]\n",str);
                            exit(1);
#endif

}


