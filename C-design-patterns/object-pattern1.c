#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

struct A{
    unsigned int var1;
    struct A* (*fn1)(struct A *, unsigned int);
};

struct B{
    unsigned int var1;
    struct B* (*fn1)(struct B *, unsigned int);
};

struct  app
{
    /* data */
    struct A * A1;
    struct B * B1;
};

struct A* fn1_A(struct A * this, unsigned int val){
    this->var1 = val;
    return this;
}

struct B* fn1_B(struct B * this, unsigned int val){
    this->var1 = val;
    return this;
}

static void signal_handler(int signo){
    if(signo == SIGUSR1){
        printf("Incorrect argument passed! Allowed arguments: A, B\n");
        exit(2);
    }
}

int main(int argc, const char ** argv){
    struct A ob1_A;
    struct B ob1_B;
    struct app App;
    App.A1 = &ob1_A;
    App.B1 = &ob1_B;
    ob1_A.fn1 = fn1_A;
    ob1_B.fn1 = fn1_B;
    if(argc > 1){
        if(strstr(argv[1], "A")){
            ob1_A.fn1(&ob1_A, 20);
            printf("Value of variable of A object: %d\n", ob1_A.var1);
        }
        else if(strstr(argv[1], "B")){
            ob1_B.fn1(&ob1_B, 50);
            printf("Value of variable of B object: %d\n", ob1_B.var1);
        }
        else{
            if(signal(SIGUSR1, signal_handler) == SIG_ERR){
                exit(3);
            }
            kill(getpid(), SIGUSR1);
        }
    }
    else{
        ob1_A.fn1(&ob1_A, 80);
        ob1_B.fn1(&ob1_B, 180);
        printf("Values from app\n");
        printf("ob1_A.val = %d\n", ob1_A.var1);
        printf("ob1_B.val = %d\n", ob1_B.var1);        
    }
    return 0;
}
