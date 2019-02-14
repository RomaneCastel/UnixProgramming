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
	//creation du premier fils
	pid_fils=fork();
	if(pid_fils==-1){
		perror("creation du fils impossible");
		exit(EXIT_FAILURE);
	}
	if(pid_fils!=0){
		//creation du second fils
		pid_fils=fork();
		if(pid_fils==-1){
			perror("creation du fils impossible");
			exit(EXIT_FAILURE);
		}
		if(pid_fils!=0){
			close(tube[0]);
			write(tube[1], "guiguiesttropbeau",strlen("guiguiesttropbeau"));
			close(tube[1]);
			wait(NULL);
			exit(EXIT_SUCCESS);
		}
		else{
			close(tube[1]);
			while(read(tube[0], &buffer, 1)>0){
				printf("(fils2) j'ai lu %s \n", buffer);
			}
			close(tube[0]);
			exit(EXIT_SUCCESS);
		}
	}
	else{
			close(tube[1]);
			while(read(tube[0], &buffer, 1)>0){
				printf("(fils1) j'ai lu %s \n", buffer);
			}
			close(tube[0]);
			exit(EXIT_SUCCESS);
		}
}
