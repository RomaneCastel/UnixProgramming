/********************************
 * Fichier exit.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2017 P. Alain, V. Thion, B. Vozel
 *
 ********************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *affiche(void *arg);

int main(int argc, char* argv[]){
  pthread_t thr1, thr2;
  int i,returnValue;

  // Utilisation du prg
  if (argc!=4){
    printf("usage : %s nb1 nb2 nb3 (trois entiers)\n",argv[0]);
    exit(EXIT_FAILURE);
  }

  // Création thread supplémentaire 1
  int * nbAffTh1 = malloc(sizeof(int));
  *nbAffTh1=atoi(argv[1]);
  returnValue=pthread_create(&thr1,NULL,affiche,(void *) nbAffTh1);
  if (returnValue != 0) {
    fprintf(stderr, "Erreur dans pthread_create\n");
    exit(EXIT_FAILURE);
  }

  // Création thread supplémentaire 2
  int * nbAffTh2 = malloc(sizeof(int));
  *nbAffTh2=atoi(argv[2]);
  returnValue=pthread_create(&thr2,NULL,affiche,(void *) nbAffTh2);
  if (returnValue != 0) {
    fprintf(stderr, "Erreur dans pthread_create\n");
    exit(EXIT_FAILURE);
  }

  // Affichages par thread principal
  for(i=1;i<=atoi(argv[3]);i++){
    printf("Thread principal : Affichage %d/5\n",i);
    sleep(1);
  }
	pthread_exit(EXIT_SUCCESS);
	pthread_exit(EXIT_SUCCESS);
	pthread_exit(EXIT_SUCCESS);
  exit(EXIT_SUCCESS);
}

void *affiche(void *arg){
  int * nbAff = (int *) arg;
  int i;
  for(i=1;i<=*nbAff;i++){
    printf("Affichage %d/%d\n",i,*nbAff);
    sleep(1);
  }
	return 0; // permet de rendre le code propre, pas de warning lors de la compilation, return ce que l'on veut car void *
  //exit(EXIT_SUCCESS); c'est lui qui bloque
}

// problème lié au programme : c'est qu'en fait dès qu'un processus à fini de faire ses affichages, ça stop directement le programme, car il y a un exit(EXIT_SUCCESS). Donc les threads qui sont chargés de faire des affichages mais qui n'ont pas encore fini (alors qu'un premier a fini), ça stop tout le monde.

