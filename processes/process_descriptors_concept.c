#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	unsigned char proc_name[50];
}PCB;

typedef struct proc{
	unsigned int p_id;
	PCB * process_control_block;
}process_t;

void main(int argc, char **argv){
	if(argc > 1){
		process_t no_of_processes[atoi(argv[1])];
		for(int i = 0; i < atoi(argv[1]); i++){
			PCB block;
			strcpy(block.proc_name, argv[i+2]);
			no_of_processes[i].p_id = (i+3);
			no_of_processes[i].process_control_block = &block;
			printf("Process id: %d\n", no_of_processes[i].p_id);
			printf("Process name: %s\n", no_of_processes[i].process_control_block->proc_name);
		}
		exit(1);
	}
	else{
		printf("Insufficient arguments passed! Exiting program...\n");
		exit(2);
	}
}
	
