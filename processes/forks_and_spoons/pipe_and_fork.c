#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(void){
    /* Challenge: How to transfer data from parent process to child process?
     * Task: Write a program in C to transfer 1 byte of data from parent process to child process and vice-versa
     * Action: 
     * 1. Create an integer array of 2 cells. 
     * 2. Create a pipe with the integer array for file descriptors
     * 3. Write to the pipe from the parent process
     * 4. Fork and move into child process
     * 5. Read from pipe in child process
     * 6. Write back to pipe 1 byte data in child process
     * 7. Read from pipe in parent process and validate the transaction
     * 8. Close the pipe from both ends
     * Result: The C program
    */
   int pfd[2];  /// Integer array for pipe file descriptors
   if(pipe(pfd) == -1){     // Create the pipe with the pfd array
        exit(-1);
   }
   /* Write to the pipe from parent before forking */
    if(write(pfd[1], "A", 1) == -1){
        perror("Error occured");
        printf("Write not possible to Pipe. Exiting...\n");
        exit(-1);
   }
   /* Create the child process */
   int child_pid = fork();
   int child_proc_status = 0;
   char byte_from_child = 0;
   char read_byte_from_child = 0;   
   switch(child_pid){
        /* Enter the child process */
        case 0:
            if(read(pfd[0], &read_byte_from_child, 1) == -1){
                printf("Read from pipe failed\n");
                exit(3);
            }
            if(read_byte_from_child == 'A'){
                printf("Read from pipe successful! Expected: %c, Actual: %c\n", 'A', read_byte_from_child);
            }
            if(write(pfd[1], "B", 1) == -1){
                printf("Write to pipe failed\n");
                exit(4);
            }
            exit(5);
        case -1:
            printf("Child process not created\n");
            exit(-1);
        default:
            /* Wait for child process to complete*/
            waitpid(child_pid, &child_proc_status, 0);
            printf("Exit status from child: %d\n", (child_proc_status / 256));
            /* Read data from pipe */
            if(read(pfd[0], &byte_from_child, 1) == -1){
                printf("Read from pipe failed!\n");
                exit(-1);
            }
            if(byte_from_child == 'B'){
                printf("Write to pipe from child successful! Expected: %c, Actual: %c\n", 'B', byte_from_child);
            }
   }
}