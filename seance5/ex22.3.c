#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>

int main(){
	int i;
	for(i=0; i<4; i++){
		printf("Thread principal \n");
		sleep(1);
	}
	pthread_exit(EXIT_SUCCESS); // remplace le retrun(EXIT_SUCCESS)
}
