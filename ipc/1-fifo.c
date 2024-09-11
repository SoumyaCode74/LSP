#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char ** argv){
	char myfifo[] = "/home/vboxuser/LSP/ipc/fifo_file";
	unlink(myfifo);
	if(mkfifo(myfifo, 0666) == -1){
		perror("Pipe not created");
		return -1;
	}
	int fifo_fd = open(myfifo, O_RDWR | O_NONBLOCK);
	if(fifo_fd == -1){
		perror("File error");
		return -1;
	}
	char msg[] = "Write to FIFO\n";
	printf("no. of bytes written: %d\n", write(fifo_fd, msg, sizeof(msg)));
	printf("last position: %d\n", lseek(fifo_fd, 0, SEEK_END));
	close(fifo_fd);
	return 0;
}
