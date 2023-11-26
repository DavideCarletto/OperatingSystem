// Scrivere un programma in linguaggio C che, utilizzando le primitive
//   di I/O ANSI C (fgetc/fputc, fscanf/fprint, fget/fputs a scelta), sia
//   in grado di copiare un file di testo in file identico tramite una funzione copyFile.
//   Il nome due file sia ricevuto sulla riga di comando, in modo che
//   il programma possa essere eseguito mediante un comando

#include <stdio.h>

void copyFile(FILE *src, FILE *dst);

int main(int argc, char *argv[]) {
    FILE *src, *dst;

    if (argc != 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    src = fopen(argv[1], "r");
    if (src == NULL) {
        printf("Error opening source file\n");
        return 2;
    }

    dst = fopen(argv[2], "w");
    if (dst == NULL) {
        printf("Error opening destination file\n");
        return 3;
    }

    copyFile(src, dst);

    fclose(src);
    fclose(dst);

    return 0;
}

void copyFile(FILE *src, FILE *dst){
    char c;
    while ((c = fgetc(src)) != EOF) {
        fputc(c, dst);
    }

    return;

}

