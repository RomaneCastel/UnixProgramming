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
	//code affecté au processus père qui attend l'entrée d'un entier de l'utilisateur
	if(pid_fils!=0){
		close(tube[0]);
		char entreeUtilisateur[50];
		printf("Entrez un entier \n");
		scanf("%s", entreeUtilisateur);
		printf("t'as rentré %s", entreeUtilisateur);
		write(tube[1], &entreeUtilisateur,50);
		close(tube[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
	//code affecté au processus fils, lit dans le pipe
	else{
		close(tube[1]);
		read(tube[0], &buffer, 50);
		sleep(1);
		printf("buffer %s \n", buffer);
		int read=atoi(buffer);
		printf("lu : %d \n", read);
		int carre = read*read;
		printf("(fils) carré vaut %d \n", carre);
		close(tube[0]);
		exit(EXIT_SUCCESS);
	}
}

