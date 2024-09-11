#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
    static int proc_cnt = 0;
    if (argc > 1){
        if(strstr(argv[1], "-f")){
            int pid = 2;
            for(int i = 1; i <= atoi(argv[2]); i++){
                pid = fork();
                switch (pid)
                {
                case 0:
                    /* code */
                    proc_cnt += 1;
                    printf("Child process count: %d\n", proc_cnt);                    
                    printf("Value of pid = %d in child process: %d\n", pid, proc_cnt);
                    printf("Child process running! PID: %d\n", getpid());
                    printf("Parent of this child: %d\n", getppid());
                    break;
                case -1:
                    printf("Child process not created\n");
                    break;
                default:
                    wait(NULL);
                    printf("Child process ended\n");
                    printf("Parent process running! PID: %d\n", getpid());
                }
            }
        }
    }
        else{
            switch(fork()){
                case 0:
                    printf("Only 1 child process created and running! PID %d\n", getpid());
                    printf("My parent process is: %d\n", getppid());
                    break;
                case -1:
                    printf("No child created! This process is infertile! :\(\n");
                    break;
                default:
                    printf("Parent running: %d\n", getpid());
            }
        }    
}