#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int quit = 0;
void sigHandler(){
		quit = 1;
		printf("sexo?\n");

}


int main(void){

		signal(SIGINT, sigHandler);

		while(!quit){}


		printf("bye\n");

		return 0;
}

