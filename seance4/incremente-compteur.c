#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int main(){
	int fd;
	int * compteur;
	int valRetourTruncate;
	//ouverture de compte
	fd=shm_open("compteur", O_RDWR, 0644);
	if(fd==-1){
		perror("compteur");
		return EXIT_FAILURE;
	}
	valRetourTruncate = ftruncate(fd, sizeof(int));
	if(valRetourTruncate==-1){
		perror("ftruncate");
		return EXIT_FAILURE;
	}
	//Rattachement de la réegion partagée à l’espace d’adressage  
	compteur = mmap(NULL, sizeof(int),PROT_WRITE, MAP_SHARED, fd, 0);
	for(int i=0; i<100; i++){
		(* compteur) ++;
		printf("(PID : %d) compteur = %d \n", getpid(), *compteur);
		sleep(1);
	}
	return EXIT_SUCCESS;
}

//q4 : si on appelle supprime-compteur pendant l'éxécution, cela ne marchera pas car le lien entre le compteur et la zone mémoire est faire (mmap), le lien connait encore le nom de la zone. En revanche si on le supprime et qu'on relance une éxécution, ça ne marche plus, car ne connait plus le lien.
