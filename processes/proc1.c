#include <unistd.h>

int main(int argc, char **argv){
	char arg_passed[] = "Arguments passed\n";
	char arg_not_passed[] = "No arguments passed\n";
	if(argc > 1){
		int arg_length = 0;
		write(1, arg_passed, sizeof(arg_passed));
		for(int i = 1; i < argc; i++){
			int j = 0;
			while(argv[i][j] != '\0'){
				arg_length++;
				j++;
			}
			write(1, argv[i],arg_length);
			write(1, "\n", 1);
			arg_length = 0;
		}

	}
	else{
		write(1, arg_not_passed, sizeof(arg_not_passed));
	}
	return 0;
}