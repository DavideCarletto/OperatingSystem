#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>


typedef int * Semaphore;

Semaphore SA, SBCD, SEF, SG, SH, SI;

Semaphore semaphore_init();
void semaphore_signal(int *S);
void semaphore_wait(int *S);
void pA();
void pB();
void pC();
void pD();
void pE();
void pF();
void pG();
void pH();
void pI();

int main(int argc, char *argv[]){
    
    __pid_t pIDA, pIDB, pIDC, pIDD, pIDE, pIDF, pIDG, pIDH, pIDI; 

    SA = semaphore_init();
    SBCD =  semaphore_init();
    SEF = semaphore_init();
    SG = semaphore_init();
    SH = semaphore_init();
    SI = semaphore_init();

    semaphore_signal(SA);

    while(1) {
        pIDA=fork();
        if (pIDA!=0) {
        pIDB=fork();
        if (pIDB!=0) { 
            pIDC=fork(); 
            if (pIDC!=0) { 
                pIDD=fork();
                if (pIDD!=0) {
                    pIDH=fork();
                    if (pIDH!=0) {
                        pI();
                        } else
                        pH();    
                } else 
                    pD();   
            }else { 
                    pIDE=fork();
                    if (pIDE!=0) 
                    pC();
                    else {
                        pIDF=fork();
                        if (pIDF!=0) {
                            pE();  
                        } else {
                                pIDG=fork();
                                if (pIDG!=0)  
                                    pF();
                                else pG(); 
                            }     
                    }   
                }   
            }else
                pB();                        
        }else pA();
    }  
    return 0;
}

Semaphore semaphore_init(){
    int *S = calloc(2,sizeof(int)); 
    if(pipe(S) == -1){
        fprintf(stderr, "Error in in");
        exit(1);
    }
    return S;
}

void semaphore_signal(int *S){
    char crt = 'X';
    if(write(S[1], &crt, 1)!= 1){
        fprintf(stderr, "Error in signal");
        exit(1);
    }
    return;
}

void semaphore_wait(int *S){
    int junk;

    if(read(S[0], &junk, 1) != 1){
        fprintf(stderr, "Error in wait");
        exit(1);
    }
    return;
}

void pA(){
    semaphore_wait(SA);
    sleep(1);
    fprintf(stdout, "\tA\n");
    semaphore_signal(SBCD);
    semaphore_signal(SBCD);
    semaphore_signal(SBCD);
    exit(0);
}

void pB(){
    semaphore_wait(SBCD);
    sleep(2);
    fprintf(stdout, "B\t");
    semaphore_signal(SI);
    exit(0);
}

void pC(){
    semaphore_wait(SBCD);
    sleep(3);
    fprintf(stdout, "C\t");
    semaphore_signal(SEF);
    semaphore_signal(SEF);
    exit(0);
}

void pD(){
    semaphore_wait(SBCD);
    sleep(4);
    fprintf(stdout, "D\n");
    semaphore_signal(SH);
    exit(0);
}

void pE(){
    semaphore_wait(SEF);
    sleep(2);
    fprintf(stdout, "    E       ");
    semaphore_signal(SG);
    exit(0);
}

void pF(){
    semaphore_wait(SEF);
    sleep(3);
    fprintf(stdout, "F\n");
    semaphore_signal(SG);
    exit(0);
}

void pG(){
    semaphore_wait(SG);
    semaphore_wait(SG);
    sleep(1);
    fprintf(stdout, "\tG");
    semaphore_signal(SI);
    exit(0);
}

void pH(){
    semaphore_wait(SH);
    sleep(5);
    fprintf(stdout, "\tH\n");
    semaphore_signal(SI);
    exit(0);
}

void pI(){
    semaphore_wait(SI);
    semaphore_wait(SI);
    semaphore_wait(SI);
    sleep(1);
    fprintf(stdout, "\tI\n");
    semaphore_signal(SA);
}