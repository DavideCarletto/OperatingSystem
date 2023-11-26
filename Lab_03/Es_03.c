#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_STR 100
#define LEN_STR 100

void allocateMemory(char ***str);
void readFile(FILE *fp, int *n, char ***str);
void executeSystem(char **str, int n);
void doExec(char **str, int n);
void myExecute(char **cmd);

int main(int argc, char *argv[]){

    FILE *fp;
    char *filename, **str;
    int n = 0;

    if(argc != 2){
        printf("Errore: numero di argomenti errato\n");
        return(1);
    }

    filename= argv[1]; 

    if((fp = fopen(filename, "r"))== NULL){
        printf("Errore: impossibile aprire il file\n");
        return(1);
    }

    
    allocateMemory(&str);
    readFile(fp, &n, &str);
    executeSystem(str, n);
    doExec(str, n);

    // for(int i=0; i<n; i++){
    //     printf("%s", str[i]);
    // }

    return 0;
}


void allocateMemory(char ***str) {
    *str = (char**)malloc(MAX_STR * sizeof(char*));

    if (*str == NULL) {
        fprintf(stderr, "Errore nell'allocazione di memoria per il vettore di stringhe.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX_STR; i++) {
        (*str)[i] = (char*)malloc(LEN_STR * sizeof(char));

        if ((*str)[i] == NULL) {
            fprintf(stderr, "Errore nell'allocazione di memoria per la stringa %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }
}
void readFile(FILE *fp, int *n, char ***str){

    while (fgets((*str)[*n], LEN_STR, fp) != NULL) {
        // printf("Riga letta: %s\n", (*str)[*n]);
        (*n)++;
    }
}

void executeSystem(char **str, int n){
    for(int i=0; i<n; i++){
        printf("Executing system... %s\n", str[i]);
        
        if(system(str[i])!= -1){
            printf("System executed\n\n");
        }
    }
}

void doExec(char **str, int n){
    
    char **cmd, *token,  delimiters[] = " \n";

    allocateMemory(&cmd);
    token = (char*) malloc(LEN_STR);

    for(int i=0; i<n; i++){
        token = strtok(str[i], delimiters);
        int indice = 0;

        while (token != NULL) {
            cmd[indice] = strdup(token);
            token = strtok(NULL, delimiters);
            // printf("%s ", cmd[i][indice]);
            indice++;
        }
        cmd[indice] = NULL;
        myExecute(cmd);
        printf("Exec done\n\n");

    }
    
}

void myExecute(char **cmd){
    int pid = fork();
    
    if(pid == 0){
        printf("Running execvp... %s \n", cmd[0]);
        execvp(cmd[0], cmd);
    }else{
        sleep(3);
    }
}