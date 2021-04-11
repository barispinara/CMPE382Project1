//CMPE382 Project1 Linux Shell
//Group members:
//Barış Pınar -------------  Beray Akar
//Lecture : CMPE382
//Topic: Linux Shell


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <math.h>
#include <string.h>
#define  NUM_THREADS 10

int quit = 0;

//executer method is the system call method, threads run this method and this method do system call according to parameter.
void *executer(void *thread){
        char *input = (char*) thread;
	system(input);
        pthread_exit(NULL);
}

//thread_worket is the main part of the our shell, it firstly seperate input string according to "|" sign
//After splitting string, it creates thread array which size is 10 , and it adds seperated string in to threads after the
//splitting string according to ";" sign.
void thread_worker(char* input){
        char *ptr = strtok(input , "|");
        char *line_array[512];
        int i=0;
        line_array[i] = ptr;
	while(ptr != NULL){
                ptr = strtok(NULL , "|");
                i++;
                line_array[i] = ptr;

        }
	char *ptr2;
	int x;
	pthread_t threads[NUM_THREADS];
	int rc;
	char *quitcommand;
        for(int a= 0; a<i; a++){
		x = 0;
                ptr2 = strtok(line_array[a] , ";");
		while(ptr2 != NULL){
			if(strcmp(ptr2 , "quit") == 0 || strcmp(ptr2 , " quit ") == 0 || strcmp(ptr2 , "quit ") == 0 ||
 strcmp(ptr2 , " quit" ) == 0 ){
				quitcommand = ptr2;
			}
			else{
				rc = pthread_create(&threads[x] , NULL , executer  , (void*) ptr2);
				x++;
			}
			ptr2 = strtok(NULL , ";");
		}
		for(int b = 0; b<x; b++){
			pthread_join(threads[b] , NULL);
		}
        }
	if(quitcommand != NULL){
		quit = 1;
	}

}


int main(int argc , char *argv[]){
        char input[520];
	system("clear");
	FILE *file;
	//BATCH MODE
	//Batch mode reads file line by line and calls thread_worker method.
	//If system can not find file  , it gives error
	if(argc == 2){
		file =  fopen(argv[1] , "r");
		if(file == NULL){
			printf("File couldn't find or opened %s \n" , argv[1]);
			return 1;
		}
		else{
			while(fgets(input , sizeof(input) , file) != NULL){
				if(strlen(input) > 512){
					printf("command input cannot longer than 512 \n");
					break;
				}
				else{
					printf("%s \n" , input);
					thread_worker(input);
				}
			}
			printf("----This is end of the file---- \n");
			fclose(file);
			while(quit != 1 ){
				printf("myshell:>");
				gets(input);
				if(strlen(input) >512){
					printf("command input cannot longer than 512 \n");
				}
				else{
					thread_worker(input);
				}

			}
		}


	}
	//Interactive MODE
	//This part is simply takes input from the user and calls thread_worker method

	else if(argc == 1){
		while(quit != 1){
			printf("myshell:>");
			gets(input);
			if(strlen(input) > 512){
				printf("command input cannot bigger than 512 \n");
			}
			else{
				thread_worker(input);
			}
		}
	}
	//If user gives anormal or extra input, system prints reminder message
	else if((argc != 1 || argc != 2)){
		printf("System has 2 options please use like this \n");
		printf("./shell <file> activates batch mode and system will read file \n");
		printf("./shell activates interactive mode and system terminal will start \n");
	}
return 0;

}

