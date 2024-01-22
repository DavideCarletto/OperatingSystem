#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <ctype.h>
#define MAX 100
#define PREFIX "./"

sem_t sem1, sem2, sem3;

void *readFile(void *arg);
void *invertLine(void *arg);
void *writeFile(void *arg);
void checkThread(int thread);

typedef struct 
{
    char *fileInputPath, *fileOutputPath, *currentLine;
    int stop;
    
}ThreadArgs;

int main(int argc, char* argv[]){

    pthread_t tid1, tid2, tid3;
    ThreadArgs tA;

    int thread_reader, thread_inverter, thread_writer;
    
    if(sem_init(&sem1, 0, 1)!= 0){
        fprintf(stderr, "Error while creating semaphore");
        return -1;
    }

    if(sem_init(&sem2, 0, 0)!= 0){
        fprintf(stderr, "Error while creating semaphore");
        return -1;
    }

    if(sem_init(&sem3, 0, 0)!= 0){
        fprintf(stderr, "Error while creating semaphore");
        return -1;
    }

    tA.fileInputPath = (char*) malloc(MAX*sizeof(char));
    tA.fileOutputPath = (char*) malloc(MAX*sizeof(char));
    tA.currentLine = (char*) malloc(MAX*sizeof(char));
    tA.stop = 0;

    strcpy(tA.fileInputPath, PREFIX);
    strcat(tA.fileInputPath, argv[1]);
    strcpy(tA.fileOutputPath, PREFIX);
    strcat(tA.fileOutputPath, argv[2]);
    
    thread_reader = pthread_create(&tid1, NULL,  readFile,  (void *)&tA);
    thread_inverter = pthread_create(&tid2, NULL, invertLine, (void *)&tA);
    thread_writer = pthread_create(&tid3, NULL, writeFile, (void *)&tA);

    checkThread(thread_reader);
    checkThread(thread_inverter);
    checkThread(thread_writer);


    pthread_join(tid1, NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);

    fprintf(stdout, "Done.");
    return 0;
}

void checkThread(int thread){ //check if there are errors in creating threads

    if(thread){
         fprintf(stdout, "Error while creating thread");
        exit(-1);
    }
}


void *readFile(void *arg){
    ThreadArgs *tA = (ThreadArgs *) arg;

    FILE *fp;

    if((fp =fopen(tA->fileInputPath, "r"))== NULL){
        fprintf(stdout, "Error opening input file...");
        pthread_exit(NULL);
    }

    while(1){
        sem_wait(&sem1);
        
        if(fgets(tA->currentLine, MAX, fp)== NULL){
            tA->stop = 1;
            sem_post(&sem2);
            sem_wait(&sem1);
            break;
        }

        sem_post(&sem2);
    }

    fprintf(stdout, "Thread 1 closed...\n");
    pthread_exit(NULL);
}

void *invertLine(void *arg){
    ThreadArgs *tA = (ThreadArgs *) arg;
    
    int length = strlen(tA->currentLine), i, j;

    while(1){
        sem_wait(&sem2);
        
        if(tA->stop){
            sem_post(&sem3);
            sem_wait(&sem2);
            break;
        }

        length = strlen(tA->currentLine);
        for (i = 0, j = length - 2; i < j; ++i, --j) {
            char temp = (tA->currentLine)[i];
            (tA->currentLine)[i] = (tA->currentLine)[j];
            (tA->currentLine)[j] = temp;
        }

        for(i =0; i<length; i++){
            (tA->currentLine)[i] = toupper((tA->currentLine)[i]);
        }

        // fprintf(stdout, "%s", tA->currentLine);
        fflush(stdout);
        sem_post(&sem3);
    }
    sem_post(&sem1);
    fprintf(stdout, "Thread 2 closed...\n");
    pthread_exit(NULL);
}

void *writeFile(void *arg){
    ThreadArgs *tA = (ThreadArgs *) arg;

    FILE *fp;
        
    if((fp = fopen(tA->fileOutputPath, "w"))== NULL){
        fprintf(stderr, "Error opening output file...");
        pthread_exit(NULL);
    }

    while(1){
        sem_wait(&sem3);

         if(tA->stop){
            break;
        }

        fprintf(fp, "%s", tA->currentLine);

        sem_post(&sem1);
    }

    fprintf(stdout, "Thread 3 closed...\n");
    sem_post(&sem2);
    pthread_exit(NULL);

}