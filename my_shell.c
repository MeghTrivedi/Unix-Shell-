#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h> 
#include <sys/wait.h> 
#define DEBUG true
 

extern char **getln();

void add(char ** args, int totalArgs){

	char* stringAdd = NULL; 
	int addNum = 0;
	int sum = 0;  
	if(totalArgs >= 1){

		if (strcmp(args[0], "add") == 0 ){
			
			stringAdd = malloc(sizeof(char)*100); 

			for(int i= 1; args[i] != NULL; i++){
				stringAdd = args[i]; 
				addNum = strtol(stringAdd, NULL, 0); 
				sum = addNum + sum; 
			}
			printf("Sum: %d\n", sum); 
			//free(stringAdd);
		}
	}
}

void cmndArg(char **args){
	if(strcmp(args[0], "arg") == 0){
		int counter = 0; 
		int i = 0;
		printf("Output:: ");
		printf(" Args "); 
		for (i = 1; args[i] != NULL; i++){	
			printf(" Argument %d: %s ", i, args[i]);
			counter = counter +1; 
		}
		printf(" Argc: %d\n", counter); 
	}
}	

void myCmnd(char **args){
	if (strcmp(args[0], "name") == 0){
		printf("Hello %s, how are you doing?\n", args[1]); 
	}
	//free(args); 
}

/*Terminate Shell*/
void exitShell(char ** args, int totalArgs){
	//if(totalArgs >= 1){
		if(args[0] == NULL){
			printf("Error: No Command Inputted\n");
			return; 
		}else if(strcmp(args[0], "exit") == 0){
					printf("Goodbye!\n"); 
					exit(0); 
		}
	//}
}
/*Commands with and without Args*/
void execArgs(char ** args,  int totalArgs){
	char filename[100];
	bool outputFound = false;
	for(int x=0; args[x] != NULL; x++){
		if(strcmp(args[x], ">") == 0){
			outputFound = true;
			strcpy(filename,args[x+1]);
			if(DEBUG)printf("filename for output command: %s\n", filename);
			args[x] = NULL;
		}
		// } else if(strcmp(args[x], "<") == 0){
		// 	outputFound = true; 
		// 	strcpy(filename, args[x+1]); 
		// 	if(DEBUG){
		// 		printf("Filename for input command: %s\n", filename); 
		// 	}
		// 	args[x] = NULL;
		// }
	}

	pid_t pid;
	pid = fork(); 

		if(pid > 0){
			wait(NULL); 
		}else if(pid == -1){
			printf("Failed forking\n"); 
			exit(0); 
		}else if (pid == 0){
			if(outputFound == true){
				freopen(filename, "w+", stdout);
			}
			execvp(args[0], args); 	
			exit(0); 
		
		}
}

int main() {
		
	int i;
	char **args; 
	int totalArgs = 0;
	
	printf("SHELL$ Starting\n"); 

	while(true) {

		printf("SHELL$ "); 
		args = getln();
		for(i = 0; args[i] != NULL; i++) {
			printf("Argument %d: %s\n", i, args[i]);
			totalArgs++; 
		}
		
		exitShell(args, totalArgs);
		add(args, totalArgs);  
		cmndArg(args); 
		myCmnd(args); 
		execArgs(args, totalArgs);
		//argFile(args); 
	}	
}
