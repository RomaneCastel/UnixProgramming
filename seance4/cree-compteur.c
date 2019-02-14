#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int main(){
	//RAZ si le compte existe déjà
	if (shm_unlink("compteur") == 0) {
		fprintf(stdout, "RAZ de compteur\n");
	}
	//creation de l'espace mémoire partagée compteur
	if(shm_open("compteur", O_CREAT, 0644)==-1){
		perror("/memoire");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
