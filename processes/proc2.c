#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc > 1){
		if(strstr(argv[1], "add")){
			printf("Addition operation chosen:\n");
			printf("%d + %d = %d\n", atoi(argv[2]), atoi(argv[3]), atoi(argv[2]) + atoi(argv[3]));
		}
		else if(strstr(argv[1], "subtract")){
			printf("Subtraction operation chosen:\n");		
			printf("%d - %d = %d\n", atoi(argv[2]), atoi(argv[3]), atoi(argv[2]) - atoi(argv[3]));
		}
	}
	return 0;
}
		
