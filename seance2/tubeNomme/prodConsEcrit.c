#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){
	int tubeNomme;
	if(tubeNomme==-1){
		printf("creation du tube impossible");
		return EXIT_FAILURE;
	}
	close(tube[0]);
	write(tube[1], "Ils ont des chapeaux ronds, vive la Bretagne",strlen("Ils ont des chapeaux ronds, vive la Bretagne"));	
	sleep(5);
	write(tube[1], "Ils ont des tonneaux ronds, vive les bretons",strlen("Ils ont des tonneaux ronds, vive les bretons"));
	close(tube[1]);
	exit(EXIT_SUCCESS);
	return 0;
}

