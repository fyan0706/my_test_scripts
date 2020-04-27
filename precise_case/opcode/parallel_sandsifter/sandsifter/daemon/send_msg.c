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

int fd_mem;
int fd_sem;
int fd_cbuf;
struct sf_msg *p_shmem;
sem_t *psem;
sem_t *pmutex;
struct circ_buf *p_cbuf;

int send_msg(struct sf_msg *msg)
{
	int ret=0;
	printf("%s,%d.\n",__FILE__,__LINE__);

	sem_wait(pmutex);
	if (CIRC_SPACE(p_cbuf->head, p_cbuf->tail, NODE_NUMBER) >= 1) {
		/* insert one item into the buffer */
		struct sf_msg *item = &p_shmem[p_cbuf->head];

		memcpy( item, msg,sizeof(struct sf_msg) );

		p_cbuf->head = (p_cbuf->head + 1) & (NODE_NUMBER - 1);
		printf("%s,%d,msg->tag=%d,msg->cur_job_id=%d.\n",__FILE__,__LINE__,msg->tag,msg->cur_job_id);
		sem_post(psem);
	}
	else
	{
		ret=1;
	}

	sem_post(pmutex);
	return ret;
}

int main(int argc, char *argv[])
{
	struct sf_msg msg={0};
	int job=0;

	if(argc == 2)
		job = atoi(argv[1]);
	printf("job=%d\n",job);

	fd_mem=open(SHARE_MEM_FILE,O_CREAT|O_RDWR,00777 );
	p_shmem = (struct sf_msg*)mmap(NULL,sizeof(struct sf_msg)*NODE_NUMBER,PROT_READ|PROT_WRITE,MAP_SHARED,fd_mem,0);
	close( fd_mem );

	fd_cbuf=open(SHARE_CBUF_FILE,O_CREAT|O_RDWR,00777);
	p_cbuf = (struct circ_buf *) mmap( NULL,sizeof(struct circ_buf),PROT_READ|PROT_WRITE,MAP_SHARED,fd_cbuf,0 );
	close( fd_cbuf );

	psem = sem_open(SHARE_SEM_FILE, 0);
	if(SEM_FAILED == psem)
	{
		perror("sem_open");
	}

	pmutex = sem_open(SHARE_MEM_MUTEX, 0);
	if(SEM_FAILED == pmutex)
	{
		perror("sem_open");
	}


	if(argc != 2)
	{
		msg.tag=2;
		msg.cur_job_id=1000000;
	}
	else
	{
		msg.tag=3;
		msg.cur_job_id=job;
	}

	if(0 != send_msg(&msg))
	{
		printf("send_msg failed\n");
	}
}
