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
		printf("Thread secondaire %ld \n", num);
		sleep(1);
	}
	return (void *) EXIT_SUCCESS;
}

int main(){
	pthread_t thr1, thr2, thr3;
	int i, returnValue;
	returnValue = pthread_create(&thr1, NULL, routineThread, (void *)1L);
	if(returnValue !=0){
		fprintf(stderr, "Erreur de la creation du thread secondaire 1");
	}
	returnValue = pthread_create(&thr2, NULL, routineThread, (void *)2L);
	if(returnValue !=0){
		fprintf(stderr, "Erreur de la creation du thread secondaire 2");
	}
	returnValue = pthread_create(&thr3, NULL, routineThread, (void *)3L);
	if(returnValue !=0){
		fprintf(stderr, "Erreur de la creation du thread secondaire 3");
	}
	for(i=0; i<4; i++){
		printf("Thread principal \n");
		sleep(1);
	}
	pthread_exit(EXIT_SUCCESS); // remplace le return(EXIT_SUCCESS)
}
