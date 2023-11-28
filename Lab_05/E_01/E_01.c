#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX 1024

int main(int argc, char *argv[]){

	int pid, fd[2];
	char string[MAX];

	pipe(fd);
	pid = fork();

	if(pid){
		if(!fork()){
			while (read(fd[0], &string, sizeof(string))>0){

				if(!strcmp(string, "end")){
					break;
				}

				for(int i=0; i<strlen(string); i++)
					string[i] = toupper(string[i]);

				fprintf(stdout, "%s\n", string);
			}
		}
		wait(NULL);
	}else{

		fprintf(stdout, "Inserisci stringhe da convertire:");
		fflush(stdout);
		close(fd[0]);

		while (scanf("%s",string) > 0){
			close(fd[0]);

			write(fd[1], &string, sizeof(string));

			if(!strcmp(string, "end")){
				close(fd[1]);
				break;
			}
		}
	}
	return 0;
}
