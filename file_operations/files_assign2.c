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
	int fd = open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
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

int file_set_cursor(int fd, long long bytes_to_adjust){
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
    char message[] = "This course is all about Linux system programming. The instructor of this course is Rohan\n";
    char file_contents[sizeof(message)+50] = {0};
    int fd = file_open("./author.txt"), bytes_written;
    bytes_written = file_write(fd, message, sizeof(message));
    file_set_cursor(fd, -1*(7));
    char name[] = "Mohan";
    file_write(fd, name, sizeof(name) - 1); // To avoid double NULL terminators of char array
    int current_cursor_pos = lseek(fd, 0, SEEK_CUR);
    file_set_cursor(fd, -1*current_cursor_pos);
    file_read(fd, file_contents, sizeof(file_contents));
    write(1, file_contents, sizeof(file_contents));
    file_close(fd);
    return 0;
}