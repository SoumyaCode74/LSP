#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void *prg_brk = NULL, *alloc_mem = NULL;

int main(){
 /*   printf("Program break located at: %p\n", sbrk(0));
    // unsigned char size = 1;    
    // alloc_mem = malloc(size);
    sbrk(1);
    printf("Program break located at: %p\n", sbrk(0));    
*/
    for(int i = 0; i < 10; i++){
        printf("%p\n", sbrk(0));
    }
    return 0;
}