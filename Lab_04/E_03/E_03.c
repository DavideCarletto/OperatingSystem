#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void manage();

int main(int argc, char *argv[]){

	__pid_t pid; 

	if(signal(SIGUSR1, manage)==SIG_ERR){
		fprintf(stderr, "Signal Handler error\n");
		return 1;
	}
	if(signal(SIGUSR2, manage)==SIG_ERR){
		fprintf(stderr, "Signal Handler error\n");
		return 1;
	}

	pid = fork();

	while(1){

		if(pid){ //parent
			sleep(2);
			kill(pid, SIGUSR1);
			pause();
			fprintf (stdout, "Father Woke-up\n");
			
		}else{
			pause();
			fprintf (stdout, "Child Woke-up\n");
			sleep(2);
			kill(pid, SIGUSR1);
		}
	}

	return 0;
}

void manage(int sig){
	if(sig == SIGUSR1)
		return;
}


