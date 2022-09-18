#include <stdio.h>
#include <string.h>
int main(){
char input[10]="";
printf("Welcome to the MSHEEL\n");
while (strcmp(input,"q")!=0)
{
	printf("msheel > ");
	scanf("%s",input);
	printf("you said >%s\n",input);	
}
printf("Good bye :>  \n");

return 0;
}

