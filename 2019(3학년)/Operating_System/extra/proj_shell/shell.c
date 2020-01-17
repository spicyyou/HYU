#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

char command[1005];
char* arr[1005];
char** cmd_arr[1005];

void interactive_mode();
void batch_mode(char file_name[]);
int check_semi();
void check_option(char com[],int index);
void run();
int fork1();
int main(int argc, char **argv){
	if(argc==1){
	//interactive mode
		interactive_mode();
		
	}else if(argc ==2){
	//batch mode
	    batch_mode(argv[1]);
	}else{
		printf("wrong input\n");
	//wrong input
	}
	return 0;
}

void interactive_mode(){
	while(1){
		printf("prompt> ");
		if(fgets(command, sizeof(command),stdin)==NULL){
			exit(0);
		}
		command[strlen(command)-1]=0;
		
		if(strcmp(command,"quit")==0){
			exit(0);
		}
		
		//printf("command : %s\n",command);
		//file start

		int command_num =check_semi();
		run(command_num);
	}
}
void batch_mode(char file_name[]){
	FILE *fd;
	fd = fopen(file_name,"r");
	while(1){
		if(fgets(command, sizeof(command),fd)==NULL){
			exit(0);
		}
		command[strlen(command)-1]=0;
		
		if(strcmp(command,"quit")==0){printf("quit\n");exit(0);}
		printf("%s\n",command);
		int command_num = check_semi(command);
		run(command_num);
	}
	fclose(fd);
}

//counts the number of commands by using strtok
int check_semi(){
    int command_num =0;
	//printf("%s",command);
    char *ptr = strtok(command,";");
    int i=0;
    while(ptr !=NULL){
	arr[i]=ptr;
	command_num++;
	i++;
	ptr = strtok(NULL,";");
    }
	int j=0;
	for (j =0;j<command_num;j++){
			check_option(arr[j],j);
	}
    return command_num; //return how many commands it is
}

// to seperate option(ex ls -al)
void check_option(char com[], int idx){
    int i=0;
    //printf("ok0)");
    char *ptr = strtok(com," ");
    cmd_arr[idx]=(char**)malloc(sizeof(char*)*1005); 
    while(ptr !=NULL){
	//printf("ok2");
	cmd_arr[idx][i]=ptr;
	i++;
	//printf("num %d: %s\n",i-1,cmd_arr[idx][i-1]);
	ptr = strtok(NULL," ");
    }
}

void run(int cmd_num){
    int i=0;
//    int status;
    pid_t pid[cmd_num];
    //printf("rutn run\n");
	//printf("cmd num: %d\n",cmd_num);
    for (i=0;i<cmd_num;i++){
	//	printf("%d //  cmd_arr: %s\n",i+1,*cmd_arr[i]);
	if(*cmd_arr[i]==NULL){continue;}
/*	if(strcmp(*cmd_arr[i],"quit")==0){
		int j;
		printf("quit\n");
		for (j=0;j<i;j++){
		    waitpid(pid[j],NULL,0);
		}
	//	printf("error1");
		exit(0);
	}*/
	pid[i]=fork1();
	if(pid[i]==0){
		//	printf("run fork\n");
	    if(execvp(*cmd_arr[i],cmd_arr[i])<0){
	    	printf("exec error\n");
			kill(getpid(),SIGINT);
			break;
	    }
	}
	
    }
	//printf("last\n");
    for (i=0;i<cmd_num;i++){
    	waitpid(pid[i],NULL,0);
    }
}

int fork1(void){
    int pid;
	//printf("fork1 run\n");
    pid = fork();
    if(pid==-1){
		printf("fork error\n");
	exit(0);}
	
    return pid;
}
