/********************************
 * Fichier shm-bancaire.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2017 P. Alain, J. Chevelu, V. Thion <3
 *
 ********************************/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>


int main (int argc, char * argv[]){
  int   fd1, fd2; // descripteurs de memoire partagee
  int * cpt1, * cpt2; // variables de rattachement des regions de memoire 
  int somme; // resultat de la somme des deux comptes
  pid_t pid_fils; // PID du processus fils
  int val_retour; // stockage de valeur de retour d'appel de primitive

  // CREATION ET OUVERTURE DES SEMAPHORES
  sem_t * semlock1=sem_open("lock_cpt1", O_CREAT, 0644,1);
  if(semlock1 == SEM_FAILED){
		perror("sem_open lock_cpt1");
		exit(EXIT_FAILURE);
  }
  sem_t * semlock2=sem_open("lock_cpt2", O_CREAT, 0644,1);
  if(semlock1 == SEM_FAILED){
		perror("sem_open lock_cpt2");
		exit(EXIT_FAILURE);
  }

  // Suppression des regions pour RAZ
  shm_unlink("cpt1"); 
  shm_unlink("cpt2"); 
  
  // Region de memoire partagee cpt1 : creation, ouverture, dimensionn.
  fd1 = shm_open("cpt1", O_RDWR|O_CREAT, 0600); 
  if (fd1 == -1) { 
		perror("cpt1"); 
		exit(EXIT_FAILURE);}
  val_retour = ftruncate(fd1, sizeof(int)); 
  if (val_retour == -1) { 
		perror("ftruncate fd1"); 
		exit(EXIT_FAILURE);}
  // Region de memoire partagee cpt2 : creation, ouverture, dimensionn.
  fd2 = shm_open("cpt2", O_RDWR|O_CREAT, 0600); 
  if (fd2 == -1) {
		perror("cpt2"); 
		exit(EXIT_FAILURE);}
  val_retour = ftruncate(fd2, sizeof(int)); 
  if (val_retour == -1) { 
		perror("ftruncate fd2"); 
		exit(EXIT_FAILURE);}
  // Rattachement des regions a l'espace d'adressage
  cpt1 = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
  if (cpt1==MAP_FAILED){	
		perror("mmap cpt1"); 
		return EXIT_FAILURE;}
  		cpt2 = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
  if (cpt2==MAP_FAILED){
		perror("mmap cpt2"); 
		return EXIT_FAILURE;}

  // Instanciation du contenu des comptes
  * cpt1 = 200; fprintf(stdout, "Solde du compte 1  : %d\n", *cpt1);
  * cpt2 = 100; fprintf(stdout, "Solde du compte 2  : %d\n", *cpt2);

  // Creation d'un processus fils
  pid_fils = fork();
  
  if (pid_fils==0){ // Code du fils : le calcul de la somme des comptes
    int * premier_cpt, * second_cpt; // Var de rattach. specifiques au fils
    // Rattachement des regions à  partagées à premier_cpt et second_cpt
    premier_cpt = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, fd1, 0);
    if (premier_cpt==MAP_FAILED) {
			perror("mmap premier_cpt"); 
			exit(EXIT_FAILURE);}
    second_cpt = mmap(NULL, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED, fd2, 0);
    if (second_cpt==MAP_FAILED) {
			perror("mmap second_cpt"); 
			exit(EXIT_FAILURE);}
    // Calcul de la somme des deux comptes
    sleep(1); // Simulation du temps de lancement du fils
	 //DEMANDES DE JETONS
	 sem_wait(semlock1);
	 sem_wait(semlock2);
	 //////////////////
    somme = * premier_cpt + * second_cpt; // Calcul somme cpts
	 //RESTITUTION DE JETONS
	 sem_post(semlock1);
	 sem_post(semlock2);
	 /////////////////
    fprintf(stdout, "(Fils) La somme des comptes est : %d\n", somme);
    exit(EXIT_SUCCESS);
  }

  // Code assoceé au pere : transfert de 50 euros de cpt1 vers cpt2	  
  fprintf(stdout, "(Pere) Debut du virement : Debit de 50 euros du cpt 1 \n");
  // DEMANDES DE JETONS
  sem_wait(semlock1);
  sem_wait(semlock2);
  ////////////////////////
  * cpt1 = 200-50;
  sleep(3); // Simulation d'un temps de réponse du SI bancaire
  * cpt2 = 100+50;
  fprintf(stdout, "(Pere) Fin du virement : Credit de 50 euros sur cpt 2 \n");
  // RESTITUTION DE JETONS
  sem_post(semlock1);
  sem_post(semlock2);
  ////////////////////////
  sleep(3); // Simulation d'un temps de réponse du SI bancaire
  fprintf(stdout, "(Pere) Fin du virement \n");

  wait(NULL); // Attente du fils pour eviter orphelin
  shm_unlink("cpt1"); 
  shm_unlink("cpt2"); // Suppression regions
  return EXIT_SUCCESS;
}
