#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
	pid_t pid_fils=-1;
	int tube[2];
	char buffer[50];
	//creation tube
	int returnValue = pipe(tube);
	if(returnValue !=0){
		printf("creation du tube impossible");
		return EXIT_FAILURE;
	}
	pid_fils=fork();
	if(pid_fils==-1){
		perror("creation du fils impossible");
		exit(EXIT_FAILURE);
	}
	//code affecté au processus père qui écrit dans le pipe
	if(pid_fils!=0){
		sleep(10);
		close(tube[0]);
		write(tube[1], "coucou",strlen("coucou"));
		close(tube[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	//code affecté au processus fils, lit dans le pipe
	else{
		close(tube[1]);
		while(read(tube[0], &buffer, 2)>0){
			sleep(1);
			printf("(fils) j'ai lu %s \n", buffer);
		}
		close(tube[0]);
		exit(EXIT_SUCCESS);
	}
	return 0;
}
