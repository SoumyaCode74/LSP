#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]){
	int val1 = 111;
	if(argc > 1){
		if(strstr(argv[1], "c")){
			int id = fork();
			switch(id){
				case -1:
					printf("No child process created!\n");
					break;
				case 0:
					printf("Child process running with PID: %d\n", getpid());
//					printf("Parent process running with PID: %d\n", getppid());
					val1 *= 2;
					printf("val1=%d\n", val1);
					printf("Parent process id: %d\n", getppid());
					break;
				default:
					printf("Parent process running with PID: %d\n", getpid());
					val1 += 2;
					printf("val1=%d\n", val1);
					return 0;
					
				}
		}
	}
	else{
		printf("Only 1 process running. No child process to create\n");
	}
}


