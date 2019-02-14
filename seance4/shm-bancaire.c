// Processus créateur d'une zone de memoire partagee nommée shmCompteur
// de stockage d'un entier.
// Ce processus écrit dans la zone.

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int main()
{
	int fd, i;
	int *compteur;

	// RAZ de la zone de mémoire si elle existait déjà
	if (shm_unlink("shmCompteur") == 0) {
		fprintf(stdout, "RAZ de shmCompteur\n");
	}
	// Ouverture de la memoire partagee
	if ((fd = shm_open("shmCompteur", O_RDWR | O_CREAT, 0644)) == -1) {
		perror("shmCompteur");
		exit(EXIT_FAILURE);
	}

	if (ftruncate(fd, sizeof(int)) != 0) {
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}

	compteur = mmap(NULL, sizeof(int), PROT_WRITE, MAP_SHARED, fd, 0);
	if (compteur == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < 10; i++) {
		*compteur = i;
		fprintf(stdout, "Producteur : insertion de %d faite dans le segment partage\n",
			(*compteur));
		sleep(2);
	}

	return EXIT_SUCCESS;
}

