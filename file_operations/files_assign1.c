#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int file_read(int fd, char * buf, int bytes_to_read){
	int bytes_read = read(fd, buf, bytes_to_read);
	switch(bytes_read){
			case -1:
				printf("File could not be read! Exiting program...\n");
				exit(1);
				break;
			case 0:
				printf("End of file reached, no bytes read\n");
				break;
			default:
				printf("Number of bytes read: %d\n", bytes_read);
	}			
	return bytes_read;
}

int file_write(int fd, char * buf, int bytes_to_write){
	int bytes_written = write(fd, buf, bytes_to_write);
	switch (bytes_written)
	{
	case -1:
		/* code */
		printf("File could not be written to! Exiting application!\n");
		exit(1);
	default:
		printf("Number of bytes written: %d\n", bytes_written);
	}
	return bytes_written;
}

int file_open(char *name){
	/* Open a file in read-write mode with */
	int fd = open(name, O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
	switch(fd){
		case -1:
			printf("File could not be opened!\n");
			exit(1);
		default:
			printf("File opened with file descriptor: %d\n", fd);
	}
	return fd;
}

int file_close(int fd){
	switch ((close(fd))){
		case -1:
			printf("File could not be closed!\n");
			exit(1);
		default:
			printf("File closed!\n");
	}
	return 0;
}

int file_set_cursor(int fd, int bytes_to_adjust){
	int final_position = lseek(fd, bytes_to_adjust, SEEK_CUR);
	switch (final_position)
	{
	case -1:
		printf("Position could not be set\n");
		exit(1);
		break;
	
	default:
		return final_position;
	}
}

int main(){
	char message[] = "Hello from Linux, this is Soumyadeep :)\n";
	write(1, message, sizeof(message));
	return 0;
}