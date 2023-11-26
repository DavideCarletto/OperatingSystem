#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void pRight(void);
void pLeft(void);

int main(int argc, char *argv[]){
    
    
    printf("P1 (PID = %d, PARENT = %d)\n",getpid(), getppid());

    int id = fork();

    if(!id){
        printf("P2 (PID = %d, PARENT = %d)\n",getpid(), getppid());
        if(fork()){ //secondo livello dell'albero
            pLeft();
            exit(0);
        }else{
            printf("P4 (PID = %d, PARENT = %d)\n",getpid(), getppid());
            exit(0);
        }
    }else{
        if(!fork()){
            printf("P3 (PID = %d, PARENT = %d)\n",getpid(), getppid());
            pRight();
            wait(NULL);
            printf("P9 (PID = %d, PARENT = %d)\n",getpid(), getppid());
            exit(0);
        }
    }
}

void pRight(){
   int pid = fork();

    if(!pid){ 
         printf("P6 (PID = %d, PARENT = %d)\n",getpid(), getppid());
         exit (0);
    }else{
        wait(NULL);
        printf("P8 (PID = %d, PARENT = %d)\n",getpid(), getppid());
    }
}

void pLeft(){
    int pid = fork();

    if(!pid){ 
         printf("P5 (PID = %d, PARENT = %d)\n",getpid(), getppid());
         exit (0);
    }else{
        while (wait ((int *) 0) != pid);
            printf("P7 (PID = %d, PARENT = %d)\n",getpid(), getppid());
        exit(0);
    }
}