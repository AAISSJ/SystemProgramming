#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(){

	char *cmd;
	size_t size;
	char path[100];
	char *arg[4];
	int pid;

	while(1){
		
		getline(&cmd,&size,stdin);
		cmd[strlen(cmd)-1]='\0';
		
		
		if (strcmp(cmd,"quit")==0){
			break;
		} 		
		
		int i=0;
		char *ptr=strtok(cmd," ");
		
		while(ptr!=NULL){
			arg[i++]=ptr;
			ptr=strtok(NULL," ");
		}

		arg[i]=NULL;
		sprintf(path,"/bin/%s",arg[0]);
		
		pid=fork();

		if (pid<0){
		
			return -1;
		}
		else if (pid ==0){
		
			execv(path,arg);		
			exit(0);
		}
		else{
		
			wait(NULL);
		}
		
	
	}

	return 0;
}
