/*
 * See Documentation/circular-buffers.txt for more information.
 */

#ifndef _LINUX_CIRC_BUF_H
#define _LINUX_CIRC_BUF_H 1

struct circ_buf {
	char *buf;
	int head;
	int tail;
};

/* Return count in buffer.  */
#define CIRC_CNT(head,tail,size) (((head) - (tail)) & ((size)-1))

/* Return space available, 0..size-1.  We always leave one free char
   as a completely full buffer has head == tail, which is the same as
   empty.  */
#define CIRC_SPACE(head,tail,size) CIRC_CNT((tail),((head)+1),(size))

/* Return count up to the end of the buffer.  Carefully avoid
   accessing head and tail more than once, so they can change
   underneath us without returning inconsistent results.  */
#define CIRC_CNT_TO_END(head,tail,size) \
	({int end = (size) - (tail); \
	  int n = ((head) + end) & ((size)-1); \
	  n < end ? n : end;})

/* Return space available up to the end of the buffer.  */
#define CIRC_SPACE_TO_END(head,tail,size) \
	({int end = (size) - 1 - (head); \
	  int n = (end + (tail)) & ((size)-1); \
	  n <= end ? n : end+1;})

#define SHARE_MEM_FILE ("/tmp/mem_file")
#define SHARE_MEM_MUTEX ("/share_mem_mutex")
#define SHARE_SEM_FILE ("/sem_file")
#define SHARE_CBUF_FILE ("/tmp/circle_buf")
#define NODE_NUMBER (4194304)

struct sf_msg{
    unsigned int tag; //0:normal injection bytes. 1:finished. 2:query all processes status. 3: query specific process status. 4:process exit message 
    int cur_job_id;
    unsigned int inst_count;
    unsigned char inj_bytes[16];
    int len;
    //int head;
    //int tail;
};

#endif /* _LINUX_CIRC_BUF_H  */
