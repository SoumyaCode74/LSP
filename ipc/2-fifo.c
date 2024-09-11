#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

int main(void){
	char myfifo[] = "/home/vboxuser/LSP/ipc/fifo_file";
	switch(fork()){
		case -1:
			return -1;
		case 0:
			printf("Child process PID: %d\n", getpid());
			if(execl("./1-fifo", "./1-fifo", NULL) == -1){
				perror("Process error");
				return -1;
			}
		default:
			wait(NULL);
			int fd = open(myfifo, O_RDWR | O_NONBLOCK);
			int no_of_bytes_in_pipe = 0;
			ioctl(fd, FIONREAD, &no_of_bytes_in_pipe);
			char msg[no_of_bytes_in_pipe];
			read(fd, msg, no_of_bytes_in_pipe);
			if(strstr(msg, "Write to FIFO\n")){
				printf("Write/Read FIFO successful! Expected: %s, Actual: Write to FIFO\n", msg);
			}
			else{
				printf("Write/Read FIFO failed! Expected: %s, Actual: Write to FIFO\n", msg);
			}
			return 0;		
		}
}
			
