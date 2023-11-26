#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void createChildren(int n);

int main(int argc, char *argv[]){

    int n, t;

    n = atoi(argv[1]);
    t = atoi(argv[2]);

    createChildren(n);
    
    printf("\nLeaf %d - sleep %d seconds\n",getpid(),t);
    sleep(t); 
    printf("\nLeaf %d - END\n",getpid()); 

    return 0;
}

void createChildren(int n){

    if(n==0){
        return;
    }

    if(fork()){
        if(fork()){
            exit(0);
        }
    }

    createChildren(n-1);
    return ;
}