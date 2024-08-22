#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void (*ptr1)(int, int);
void math_operations(int op, void (*p)(int, int), int, int);
void addition(int, int);
void subtraction(int, int);
void multiplication(int, int);
void division(int, int);

int main(int argc, char **argv){
	ptr1 = NULL;
	if(argc > 1){
		if(strstr(argv[1], "add")){
			ptr1 = addition;
			math_operations(1, ptr1, atoi(argv[2]), atoi(argv[3]));
		}
		else if(strstr(argv[1], "sub")){
			ptr1 = subtraction;
			math_operations(2, ptr1, atoi(argv[2]), atoi(argv[3]));
		}
		else if(strstr(argv[1], "mul")){
			ptr1 = multiplication;
			math_operations(3, ptr1, atoi(argv[2]), atoi(argv[3]));
		}
		else if(strstr(argv[1], "div")){
			ptr1 = division;
			math_operations(4, ptr1, atoi(argv[2]), atoi(argv[3]));
		}
	}					
	else{
		printf("Not enough arguments passed! Exiting process...\n");
	}
	return 0;
}

void math_operations(int op, void (*p)(int, int), int x, int y){
	p(x, y);
}

void addition(int x, int y){
	printf("Addition: %d + %d = %d\n", x, y, x + y);
}

void subtraction(int x, int y){
	printf("Subtraction: %d - %d = %d\n", x, y, x - y);
}

void multiplication(int x, int y){
	printf("Multiplication: %d * %d = %d\n", x, y, x * y);
}

void division(int x, int y){
	if(y != 0){
		printf("Division: %d / %d : Quotient: %d, Remainder: %d\n", x, y, x / y, x % y);
	}
	else{
		printf("Division by 0 not allowed!\n");
	}
}							
