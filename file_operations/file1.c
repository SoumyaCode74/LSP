#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    char buf[] = "Hello screen!\n";
    char buf_read[sizeof(buf)] = {0};
    printf("Bytes to write\n");
    write(1, buf, sizeof(buf));
    int fd = open("./file1.txt", O_CREAT | O_RDWR | O_TRUNC, 0744);
    if(fd == -1)
        printf("File not created!");
    else{
        printf("File created with file descriptor value: %d\n", fd);
    }
    int bytes_written = write(fd, buf, sizeof(buf));
    printf("=========CURSOR POSITIONS==========\n");
    printf("After writing to file: %d\n", lseek(fd, 0, SEEK_CUR));
    printf("After resetting cursor to the beginning: %d\n", lseek(fd, -1*bytes_written, SEEK_CUR));
    // fd = open("./file1.txt", O_RDONLY);    
    printf("no. of bytes read: %ld\n", read(fd, buf_read, sizeof(buf_read)));
    printf("After reading from file: %d\n", lseek(fd, 0, SEEK_CUR));
    write(1, buf_read, sizeof(buf_read));
    close(fd);
    execlp("cat", "./file1.txt");
    return 0;
}