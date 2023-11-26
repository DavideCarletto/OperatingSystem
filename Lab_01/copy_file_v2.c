// Scrivere un programma in linguaggio C che, utilizzando le primitive
//   di I/O ANSI C (fgetc/fputc, fscanf/fprint, fget/fputs a scelta), sia
//   in grado di copiare un file di testo in file identico tramite una funzione copyFile.
//   Il nome due file sia ricevuto sulla riga di comando, in modo che
//   il programma possa essere eseguito mediante un comando

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void copyFile(int src, int dst);

int main(int argc, char *argv[]) {
    int src, dst;

    if (argc != 3) {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    src = open(argv[1], O_RDONLY| O_CREAT );
    if (src == -1) {
        printf("Error opening source file\n");
        return 2;
    }

    dst = open(argv[2], O_WRONLY | O_CREAT );
    if (dst == -1) {
        printf("Error opening destination file\n");
        return 3;
    }

    copyFile(src, dst);

    close(src);
    close(dst);

    return 0;
}

void copyFile(int src, int dst){
    char buf[8192];
    ssize_t n= 0;

    while((n = read(src, buf, 8192)) > 0)
        write(dst, buf, n);

    return;

}

