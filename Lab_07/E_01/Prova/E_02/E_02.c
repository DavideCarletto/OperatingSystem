#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define file_input_path "../E_02/Input/"
#define file_output_path "../E_02/Output/"
#define max 1024

typedef struct
{
    int n, *vet;
    char *fileInputPath, *fileOutputPath;

}ThreadArgs;

void createInputFiles(int n, char *stra);
void sort(int **vet, int n);
void *tF(void *args);
void readFile(char *filePath, int *tn, int **tvet);
void writeOutputFile(char *filePath, int tn, int *vet);

int main(int argc, char *argv[]) {

    char *stra = argv[2], *strb = argv[3];
    int n = atoi(argv[1]), rc;
    pthread_t t[n];
    void *status;

    createInputFiles(n,stra);
    
    for (int i = 0; i < n; i++) {
        ThreadArgs tA;
        tA.fileInputPath = (char *)malloc(max * sizeof(char));
        tA.fileOutputPath = (char *)malloc(max * sizeof(char));

        sprintf(tA.fileInputPath, "%s%s%d.txt", file_input_path, stra, i);
        sprintf(tA.fileOutputPath, "%s%s%d.txt", file_output_path, strb, i);
        fprintf(stdout, "Thread N %d is handling vet: ", i);
        rc = pthread_create(&t[i], NULL, tF, (void *)&tA);

        if (rc) {
            exit(-1);
        }
        pthread_join(t[i], &status);
        free(tA.vet); 
    }

    printf("Done\n");
    return 0;
}
void createInputFiles(int n, char *stra){

    FILE *fp;
    int nrand, val;
    char *file_path = (char*) malloc(max*sizeof(char));
    for (int i=0; i<n; i++){

        sprintf(file_path,"%s%s%d.txt",file_input_path, stra, i);
        
        fp = fopen(file_path, "w");
        nrand = rand() % 10 + 1;

        fprintf(fp, "%d\n", nrand);

        for(int j=0; j<nrand;j++){
            val = rand() % 100 +1;
            fprintf(fp, "%d\n", val);
        }
        fclose(fp);
    }
    return;
}

void sort(int **vet, int n) {
    int i, j;

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if ((*vet)[j] > (*vet)[j + 1]) {
                int temp = (*vet)[j];
                (*vet)[j] = (*vet)[j + 1];
                (*vet)[j + 1] = temp;
            }
        }
    }
}

void *tF(void *args){

    ThreadArgs *tA = (ThreadArgs*) args;

    
    readFile(tA->fileInputPath, &(tA->n), &(tA->vet));
    
    for(int j=0; j<tA->n; j++){
        fprintf(stdout, "%d ", tA->vet[j]);
    }
    fprintf(stdout, "\n");
    sort(&(tA->vet), tA->n);
    
    writeOutputFile(tA->fileOutputPath, tA->n, tA->vet);

}

void readFile(char *filepath, int *tn, int **tvet){

    FILE *fp;
    int n, count = 0;

    if((fp = fopen(filepath, "r")) == NULL){
        fprintf(stderr, "Errore nell'apertura del file di input\n");
        return;
    }

    fscanf(fp, "%d", tn);

    *tvet = (int*) malloc((*tn)*sizeof(int));

    while (fscanf(fp,"%d", &n) == 1){   
        (*tvet)[count++] = n;
    }
    fclose(fp);

    return;    
}

void writeOutputFile(char *filePath, int tn, int *vet){

    FILE *fp;

    if((fp = fopen(filePath, "w")) == NULL){
        fprintf(stderr, "Errore nell'apertura del file di output");
        return;
    }

    fprintf(fp, "Vettore ordinato: ");

    for(int i=0; i < tn; i++){
        fprintf(fp, "%d ", vet[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);
}