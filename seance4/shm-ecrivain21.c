/********************************
 * Fichier shm-ecrivain.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2017 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
// Processus créateur d'une zone de memoire partagee nommée shmCompteur de stockage d'un entier.

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int main(){
  int fd, i, valRetour;
  int *compteur;

  valRetour = shm_unlink("shmCompteur");
  if (valRetour==0) { 
		fprintf(stdout, "[Log] RAZ shmCompteur\n");
  }
  fd = shm_open("shmCompteur", O_RDWR | O_CREAT, 0644);
  if (fd==-1){
		perror("shmCompteur");
		exit(EXIT_FAILURE);
  }
  valRetour=ftruncate(fd, sizeof(int));
  if (valRetour==-1){
		perror("ftruncate");
		exit(EXIT_FAILURE);
  }
  compteur = mmap(NULL,sizeof(int),PROT_WRITE,MAP_SHARED,fd,0);
  if (compteur==MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
  }
  for (i = 0; i < 10; i++) {
    *compteur = i;
    fprintf(stdout, "Producteur : insertion de %d faite dans le segment partage\n",(*compteur));
    sleep(2);
  }
  exit(EXIT_SUCCESS);
}
