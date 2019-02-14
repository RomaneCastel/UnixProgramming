#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int main(){
	if(shm_unlink("compteur")==-1){
		perror("/memoire");
		return EXIT_FAILURE;
	}
	EXIT_SUCCESS;
}
