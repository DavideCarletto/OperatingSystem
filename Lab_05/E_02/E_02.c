#include <stdio.h>
#include <unistd.h>

#define MAX 1024

int main(int argc, char *argv[]) {
    int fd_parent_to_child[2],fd_child_to_parent[2], i=0;
    __pid_t pid;
    char string[MAX];

    // Creare le due pipe
    pipe(fd_parent_to_child);
    pipe(fd_child_to_parent);

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (!pid) { // Processo figlio
        close(fd_parent_to_child[1]);
        close(fd_child_to_parent[0]);

        while (i <10) {
            read(fd_parent_to_child[0], string, sizeof(string));
            fprintf(stdout, "%s", string);
            sprintf(string, "I'm the children (PID = %d)\n", getpid());
            write(fd_child_to_parent[1], string, sizeof(string));
            i++;
        }
    } else { // Processo padre
        close(fd_parent_to_child[0]);
        close(fd_child_to_parent[1]);
        while (1) {
            sprintf(string, "I'm the father (PID = %d)\n", getpid());
            write(fd_parent_to_child[1], string, sizeof(string));
            read(fd_child_to_parent[0], string, sizeof(string));
            fprintf(stdout, "%s", string);
        }
    }

    return 0;
}
