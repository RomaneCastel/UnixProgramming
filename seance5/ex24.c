#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



void rechercher(int tableau[], int size, int searchedValue){
	int i;
	for(i=0; i<size; i++){
		fprintf(stdout, "coucou \n");
		if(tableau[i]==searchedValue){
			fprintf(stdout, "On a trouvé %d dans le tableau \n", searchedValue);
		}
	}
}

void * routineThreadRecherche(void * tab){
	int 
	return (void *) EXIT_SUCCESS;
}

int main(int argc, char * argv[]){
	pthread_t thr1, thr2;
	int tailleTableau = argc -2;
	int searchedValue = atoi(argv[argc-1]);
	int i;
	if(tailleTableau %2==0){
		int tableau1[tailleTableau/2];
		int tableau2[tailleTableau/2];
		for(i=0; i<(tailleTableau/2); i++){
			tableau1[i]=atoi(argv[i+1]);
		}
		for(i=0; i<(tailleTableau/2); i++){
			tableau2[i]=atoi(argv[i+(tailleTableau/2)+1]);
		}
		pthread_create(&thr1, NULL, routineThread,(void *) tableau1);
		pthread_create(&thr2, NULL, routineThread, (void *) tableau2);
		rechercher(tableau, tailleTableau, searchedValue);
	}
	return EXIT_SUCCESS;
}
