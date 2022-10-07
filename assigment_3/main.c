#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define LINE_SIZE 1024
#define TOKEN_SIZE 64
#define FILE_SIZE 1000
#define STATUS_OK 9
#define STATUS_not_OK -1
#define QUIT_STATE -1
#define CONTINUE_RESULT 0XFA

struct env_var{
	char name[100];
	char value[100];
	struct env_var * next;
	
}env_var;
struct env_var * head;

//linked list functions

void add_env_var(char ** argv);

char ** parse(char * line);
int  select_and_run_command(char **argv);
int command_loop(void);
char * readline(void);
void teminalinit(void);
void terminal_terminate(void);


// kernel funtions
void print_local_env_var(void);
int export_local_env_var(void);


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
	while (status != QUIT_STATE ){
		printf("wasfy@wasfy-ubuntu:");
		line = readline();
		args = parse(line);
		status = select_and_run_command(args);
		free(line);
		free(args);
		if (status = CONTINUE_RESULT)continue;
		
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
	
	
	token = strtok(line , "=");
	args[position + 1] = token;	
	token = strtok(NULL , "=");
	if (token != NULL){
		args[position] = "env_var";
		position += 2;
		args [position++] = token;
		token = strtok(NULL , " \t\r\n\a");
		args [position++] = NULL;
	}
	else{
		token = strtok(line , " \t\r\n\a");
		while(token != NULL){
			args [position] = token;
			position++;
			
		token = strtok(NULL , " \t\r\n\a");
		}
		
		args [position] = NULL;
			
	}
	
	return args;

}

int  select_and_run_command(char **argv){
		int result=0;
		if(argv[0] == NULL ) return result;
		else if (strcmp(argv[0] , "\n") == 0) result = CONTINUE_RESULT;
		else if (strcmp(argv[0] , "env_var") == 0){
			add_env_var(argv);
		}
		else if (strcmp(argv[0] , "set") == 0){
			print_local_env_var();

		}
		else if (strcmp(argv[0] , "export") == 0){
			result = export_local_env_var();

		}
		else{
			pid_t pid, wpid;
			pid = fork();
		  if (pid == 0) {
			// Child process
			if (execvp(argv[0], argv) == -1) {
			  result = -1;
			}
			exit(EXIT_FAILURE);
		  } else if (pid < 0) {
			// Error forking
			result = -1;
		  } else {
			// Parent process
			do {
			  wpid = waitpid(pid, &result, WUNTRACED);
			} while (!WIFEXITED(result) && !WIFSIGNALED(result));
		  }
		}
	return result;
}


void add_env_var(char ** argv){
	struct env_var *node = 0;
	struct env_var *index = head;
	node = (struct env_var *)malloc(sizeof(env_var));
	strcpy(node->name,argv[1]);
	strcpy(node->value,argv[2]);
	if (head != 0)node->next = head;
	head = node;

}



// kernel funtions
void print_local_env_var(void){
	struct env_var *index = head;
	while(index != 0){
		printf("%s  %s \n",index->name,index->value);	
		index=index->next;
	}
}

int export_local_env_var(void){
	struct env_var *index = head;
	int result=0;
	
	while(index != 0){
		setenv(index->name,index->value,1);
		index = index->next;
		
}
	return result;		
	}
	
