#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define file_input_path "../E_03/Input/"
#define file_output_path "../E_03/Output/"
#define max 1024

typedef struct
{
    int n, *vet;
    char *fileInputPath;

}ThreadArgs;

void createInputFiles(int n, char *stra);
void sort(int **vet, int n);
void *tF(void *args);
void readFile(char *filePath, int *tn, int **tvet);
void writeOutputFile(char *filePath, int tn, int *vet, int index);
int merge (int *v1,int *v2,int *vmerge,int size_v1, int size_v2);

int main(int argc, char *argv[]) {

    char *stra = argv[2], *strb = argv[3], *fileOutputPath = (char*) malloc (max*sizeof(char));
    int n = atoi(argv[1]), rc, **mat, *sizes, *merged, mergedSize = 0;
    pthread_t t[n];
    void *status;

    mat = (int**) malloc (n*sizeof(int*));
    sizes = (int*) malloc(n*sizeof(int));
    merged = (int*) malloc(max*sizeof(int));

    createInputFiles(n,stra);
    sprintf(fileOutputPath, "%s%s.txt", file_output_path, strb);
    
    for (int i = 0; i < n; i++) {
        ThreadArgs tA;
        tA.fileInputPath = (char *)malloc(max * sizeof(char));

        sprintf(tA.fileInputPath, "%s%s%d.txt", file_input_path, stra, i);
        fprintf(stdout, "Thread N %d is handling vet: ", i);
        rc = pthread_create(&t[i], NULL, tF, (void *)&tA);

        if (rc) {
            exit(-1);
        }

        mat[i] = (int*) malloc(tA.n * sizeof(int));
        pthread_join(t[i], &status);

        sizes[i] = tA.n;

        for(int j=0; j<tA.n; j++){
            mat[i][j] = tA.vet[j];
            printf("%d ", mat[i][j]);
        }
        
        printf("\n");
        int *currentMerged = (int*) malloc(max*sizeof(int));

        mergedSize = merge(merged, mat[i], currentMerged, mergedSize, sizes[i]);
        memcpy(merged, currentMerged, max);

        writeOutputFile(fileOutputPath, mergedSize, merged, i);

        free(tA.vet); 
        free(currentMerged);
    }
    
    for (int i = 0; i < n; i++) {
            free(mat[i]);
    }
    free(mat);
    free(merged);

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
    sort(&(tA->vet), tA->n);
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

void writeOutputFile(char *filePath, int tn, int *vet, int index){

    FILE *fp;
    if((fp = fopen(filePath, "a")) == NULL){
        fprintf(stderr, "Errore nell'apertura del file di output");
        return;
    }

    fprintf(fp, "Vettore ordinato all' %d-esimo passo: ", index+1);

    for(int i=0; i < tn; i++){
        fprintf(fp, "%d ", vet[i]);
    }
    fprintf(fp, "\n");
    fclose(fp);
}

int merge (int *v1,int *v2,int *vmerge,int size_v1, int size_v2){ 
  
  int size_vmerge, i,j,k;
  i=j=k=0; 

  while (i<size_v1 && j<size_v2) { 
    if (v1[i]<v2[j])
	vmerge[k++]=v1[i++];
    else
	vmerge[k++]=v2[j++];
   } 
   while (i<size_v1) {   
	vmerge[k++]=v1[i++];
   }
   while (j<size_v2) {
     vmerge[k++]=v2[j++];
   }
   size_vmerge=size_v1+size_v2; 
   return size_vmerge;  
}