#include <stdio.h>
 
int isEven(int n);

int main(int argc, char* argv[]){

    int n;
    // fprintf(stdout, "Inserisci un numero: ");
    
    while(fscanf(stdin, "%d", &n)==1){ 

        if(isEven(n))
            fprintf(stdout, "%d\n", n);
        else
            fprintf(stderr, "%d\n", n);

    // fprintf(stdout, "Inserisci un numero: ");
    }

    return 0;
}

int isEven(int n){
    return n % 2 == 0;
}

