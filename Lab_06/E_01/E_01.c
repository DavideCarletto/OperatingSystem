#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void printBinary(int n, int* vet);
void printVect(int n, int *vect);

int main(int argc, char *argv[]){

    int n = atoi(argv[1]), *vet;

    vet = (int*) malloc (n*sizeof (int));

    printBinary(n,vet);

    return 0;
}


void printBinary(int n, int* vet){
    int i, j;
    pid_t pid0, pid1;

    for(i=0; i<=n; i++){
       
       if (i==n){
            printVect(n, vet);
       }else{
            pid0 = fork();

            if(!pid0){
                vet[i] = 0;
            }else{
                pid1 = fork();

                if(!pid1){
                    vet[i] = 1;
                }else{
                    wait(NULL);
                    wait(NULL);

                    exit(0);
                }
            }
       }
    }
    exit(0);
}

void printVect(int n, int *vet){

    for(int i=0; i<n; i++){
        fprintf(stdout, "%d", vet[i]);
    }
    fprintf(stdout, "\n");

    return;
}