#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void signal_handler(int signo){
	if(signo == SIGINT){
		printf("^C generated. Exiting...\n");
		exit(5);
	}
	if(signo == SIGSEGV){
		printf("Caught segmentation fault\n");
	}
}

int main(void){
	int sigerr = signal(SIGINT, signal_handler) || signal(SIGSEGV, signal_handler);
	if(sigerr == SIG_ERR){
		printf("Signal could not be handled\n");
		exit(2);
	}
	int arr[2] = {1, 2};
	if(kill(getpid(), SIGSEGV) == -1){
		perror("Signal not sent");
	}
	if(kill(getpid(), SIGINT) == -1){
		perror("SIGINT error");
	}
	printf("The value of arr[10] is: %d\n", arr[-1]);
	return 0;
}
