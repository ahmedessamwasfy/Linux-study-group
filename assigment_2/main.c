#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define LINE_SIZE 1024
#define TOKEN_SIZE 64
#define FILE_SIZE 1000
#define STATUS_OK 9
#define STATUS_not_OK -1
#define QUIT_STATE -1

char ** parse(char * line);
int  select_and_run_command(char **argv);
int command_loop(void);
char * readline(void);
void teminalinit(void);
void terminal_terminate(void);


// kernel funtions
int pwd (char** argv);
int echo (char** argv);
int cp (char** argv);
int mv (char** argv);


int main(int argc, char ** argv){
teminalinit();

command_loop();

terminal_terminate();
return 0;
}

void teminalinit(void){
	printf("Welcome to the MSHEEL\n");

}
void terminal_terminate(void){
	printf("Good bye :>  \n");

}


int command_loop(void){
	char * line;
	char ** args;
	int status;
	while (status != QUIT_STATE){
		line = readline();
		args = parse(line);
		status = select_and_run_command(args);
		free(line);
		free(args);
	}
}

char * readline(void){
	int position =0;
	int buffer_size = LINE_SIZE;
	int c;
	char * buffer = malloc(sizeof(char) * buffer_size);
	if (!buffer){
		printf("Error in allocation of input buffer");
		return NULL;
	}
	while(1){
		c = getchar();
		
		if (c == '\0' || c == '\n'){
			buffer[position] = '\0';
			return buffer;
		}
		else 
			buffer[position] = c;	
	position++;
	if (position >= buffer_size){
	buffer_size += LINE_SIZE;
	buffer = realloc(buffer , buffer_size);
	if (!buffer){
		printf("Error in allocation of input buffer");
		return NULL;
	}
	}
}
}

char ** parse(char * line){
	int buffer_size = TOKEN_SIZE , position = 0;
	char ** args = malloc(buffer_size * sizeof(char * )); // new one
	char * token;
	if (!args){
		printf("Error in allocation of input buffer");
		return NULL;
	}
	token = strtok(line , " \t\r\n\a");
	while(token != NULL){
		args [position] = token;
		position++;
		
	token = strtok(NULL , " \t\r\n\a");
	}
	
args [position] = NULL;
	return args;

}
int  select_and_run_command(char **argv){
		int result=0;
		printf("%s",argv[0]);
		if(argv[0] == NULL ) return result;
		else if (strcmp(argv[0] ,"q") == 0)result =-1;
		else if (strcmp(argv[0] ,"pwd") == 0)result = pwd(argv);
		else if (strcmp(argv[0] , "echo") == 0) result = echo(argv);
		else if (strcmp(argv[0] , "cp") == 0) result = cp(argv);
		else if (strcmp(argv[0] , "mv") == 0) result = mv(argv);
		else printf("you entered wrong command\n");
	
	return result;
}



// kernel funtions
int pwd (char** argv){
	char out[PATH_MAX];
	int status = STATUS_OK;
	if( getcwd(out,sizeof(out)) != NULL)printf("%s\n\a",out);
	else{
		status = STATUS_not_OK;
		printf("PWD Error occures\n");
	}
	return status;
}
int echo (char** argv){
	int position = 1;
	while(argv[position] != NULL){printf("%s \n",argv[position]);
	position++;
	}
	return 0;
}
int cp (char** argv){
	char buffer [FILE_SIZE];
	int count = 0;
	int file1 = open(argv[1], O_RDONLY, 0644);
	int file2 = open(argv[2], O_WRONLY|O_CREAT, 0644);
	if (file1 == -1|| file2 == -1) return -1;
	while(count = read(file1, buffer, count) != 0){
		write(file2, buffer, count);
	}
	close(file1);
	close(file2);
}
int mv (char** argv){
	int status = -1;
	if(argv[1] == NULL || argv[3] != NULL) return status;
	status = rename(argv[1], argv[2]);
	return status;
}
