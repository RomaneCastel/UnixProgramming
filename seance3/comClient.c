#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <fcntl.h>

int main(int argc, char * argv[]){
	char * numero;
	int returnValue:
	mqd_t mq;
	returnValue = mq = mq_open("/queue", 	O_WRONLY | O_CREAT, 0644, NULL);
	if(retrunValue !=-1){
		printf("Veuillez entrer un numero entre 1 et 10");
		scanf("%s", numero);
		mq_send(mq, numero, strlen(numero), 1);
		return EXIT_SUCCESS;
	}
	else{
		fprintf(stdout, "échec de la création/ouverture de la file");
	}
	return 0;
}
