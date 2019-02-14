#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <fcntl.h>


int main(int argc, char * argv[]){
	char * departements[]={NULL, "Ain", "Aisne", "Allier", "Alpes-de-Haute-Provence", "Hautes-Alpes", "Alpes-Maritime", "Ardèche", "Ardennes", "Ariège", "Aube"}; //dans la case i, le département de numéro i sauf en 0
	/*if(argc==1){
		int numero = atoi(argv[1]);
		if(numero>=1 && numero <=10){
			printf("le département associé au numéro %d est %s \n", numero, departements[numero]);
		}
		else{
			fprintf(stdout, "rentrez un numero entre 1 et 10 \n");
		}
	}
	else{
		fprintf(stdout, "rentrez un argument \n");
	}
	return 0;*/
	//question 2
	mqd_t mq;
	struct mq_attr attr;
	char * buffer = NULL;
	unsigned int prioritie;
	int retrunValue;
	
	returnValue = mq = mq_open("/queue", O_RDONLY);
	if(retrunValue!=-1){
		mq_getattr(mq, &attr);
		buffer =  malloc(attr.mq_msgsize);
		if(mq_receive(mq, buffer, attr.mq_msgsize, &prioritie)<0){
			perror("mq_receive");
			return EXIT_FAILURE;
		}
		fprintf(stdout, "J'ai consomme [%d]  %s \n", priorite, buffer);
	}
	else{
		fprintf(stdout, "échec de l'ouverture de la file");
	}
	
}
