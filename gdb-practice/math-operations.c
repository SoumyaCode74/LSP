#include "math-operations.h"
#define float_addition		for(int i = 0; i < count; i++){ \
					 total += va_arg(args, float); \
				}
#define double_addition	for(int i = 0; i < count; i++){ \
				 total += va_arg(args, double); \
				 }
#define int_addition		for(int i = 0; i < count; i++){ \
				 total += va_arg(args, int); \
				 }

/** Library function to calculate addition of numbers passed */
double addition(Typename t, int count, ...){
	va_list args;		/// list of arguments passed
	va_start(args, count);
	double total = 0;	
	switch(t){
		case FLOAT:
			float_addition
			break;
		case DOUBLE:
			double_addition
			break;
		case INT:
			int_addition
			break;
	}
/*	if(!strcmp(argtype, "int")){
		for(int i = 0; i < count; i++){
			total += va_arg(args, int);
		}
	}	
	else{
		for(int i = 0; i < count; i++){
			total += va_arg(args, double);
		}
	}	
*/
	va_end(args);
	return total;
}

