#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

void sigint_handler(int signo){
	if(signo == SIGINT){
		printf("Let's go home!\n");
		exit(0);
	}
}

int main(void){
	int cnt = 1;
	if(signal(SIGINT, sigint_handler) == SIG_ERR){
		printf("Signal handler could not be assigned! Exiting...\n");
		perror("Signal call error");
		return -1;
	}
	while(1){
		if(cnt % 2){
			printf("Hello Soumyadeep!\n");
		}
		else{
			printf("How are you?\n");
		}
		cnt++;
		sleep(2);
	}
	return 0;
}
