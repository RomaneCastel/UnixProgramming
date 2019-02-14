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
	return EXIT_SUCCESS;
}
// un seul thread issu de l'éxécution du programme
