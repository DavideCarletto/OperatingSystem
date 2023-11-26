#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX 1000
#define FILENAME "tmp.txt"

void provider(FILE *fp, pid_t custpid);
void customer(FILE *fp);
void manage();

int main(int argc, char *argv[])
{
	int status, cpid;
	__pid_t pid, custompid;
	FILE *fp;
	char firstword[MAX];

	if(signal(SIGUSR1, manage)==SIG_ERR){
			fprintf(stderr, "Signal Handler error\n");
			return 1;
	}

	pid = fork();
	if (!pid){
		pause();
		customer(fp);
	}else{
		custompid = pid;
		pid = fork();
		if(!pid){
			provider(fp, custompid);
			wait(NULL);
		}
		wait(NULL);
	}
	printf("Parent:%d terminato\n", getpid());
	return 0;
}

void manage(int sig){
	return;
}

void provider(FILE *fp, pid_t custpid){
	
	char word[MAX];
	
	printf("Inserire stringhe da convertire: ");
	fflush(stdout);
	
	sleep(1);
	while(1){
		if((fp = fopen(FILENAME, "w"))==NULL){
			fprintf(stderr, "Error opening file: %s\n", FILENAME);
			return;
		}

		scanf("%s", word);

		fprintf(fp, "%d %s\n",getpid(), word);
		fclose(fp);
		kill(custpid, SIGUSR1);

		if (!strcmp(word, "end")){
			break;
		}

		fprintf (stdout, "SENDER (receiverPid=%d): ", custpid);
		fflush(stdout);

		pause();
	}
	printf("Provider:%d terminato\n", getpid());
	fflush(stdout);
	exit(0);
}

void customer(FILE *fp){

	pid_t provpid;
	char string[MAX];

	while(1){
		if((fp = fopen(FILENAME, "r"))==NULL){
				fprintf(stderr, "Error opening file: %s\n", FILENAME);
				return;
		}

		fscanf(fp, "%d %s", &provpid, string);
		
		if (!strcmp(string, "end")){
			break;
		}

		for (int i=0; i<strlen(string); i++)
      		string[i] = toupper(string[i]);

		fprintf(stdout,"RECEIVER (senderPid=%d): %s\n", provpid, string);
		fflush(stdout);
		fclose(fp);
		sleep(1);
		kill(provpid, SIGUSR1);
		pause();
	}
	printf("Customer:%d terminato\n", getpid());
	fflush(stdout);
	exit(0);
}