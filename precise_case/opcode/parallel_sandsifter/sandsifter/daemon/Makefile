CCFLAGS= -O0 -g
CC=gcc

all:start_test send_msg

start_test:main.c
	$(CC) $< -o $@ -lpthread -g
send_msg:send_msg.c
	$(CC) $< -o $@ -lpthread -g

.PHONEY:clean
clean:
	rm -f start_test send_msg
