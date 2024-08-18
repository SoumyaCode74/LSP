#include <unistd.h>

int main(int argc, char **argv){
	int f1 = 100, f2 = 0, pos = 1;
	if(argc > 1){
		for(int i = 0; i < argc; i++){
			if (i)
				pos = i+1;
			
			if(argv[1] == "-a"){
				switch(write(1, argv[pos], 10)){
					case 0:
						write(2, "no bytes written", 20);
						break;
					case -1:
						write(2, "write error", 20);
						break;
					default:
						write(1, "bytes written", 20);
				}
			}
		}
	}
	else{
		if(write(1, "No arguments passed!", 50) == -1){
			write(2, "write error", 50);
		}
	}
	return 0;
}

