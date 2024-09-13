#include <stdio.h>
#include <unistd.h>

int main(void){
    static int i;
    while(1){
        printf("%s : %d\n", __TIME__, i);
        scanf("%d", &i);
    }
    return 0;
}