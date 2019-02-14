#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>

void * routineThread(void *arg){
	int i;
	for(i=0; i<6; i++){
		printf("Thread secondaire \n");
		sleep(1);
	}
	return (void *) EXIT_SUCCESS;
}

int main(){
	pthread_t t;
	int i, returnValue;
	returnValue = pthread_create(&t, NULL, routineThread, (void *)1L);
	if(returnValue !=0){
		fprintf(stderr, "Erreur de la creation du thread");
	}
	for(i=0; i<4; i++){
		printf("Thread principal \n");
		sleep(1);
	}
	pthread_exit(EXIT_SUCCESS); // remplace le return(EXIT_SUCCESS)
}
