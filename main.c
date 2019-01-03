#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 50


int cli(int bufSize, char *cpyBuffer, char ***tabPointer);
int display(char ***tabPointer);

/*------------------------------------------------------------*/

int 
cli(int bufSize, char *cpyBuffer, char ***tabPointer) 
{
	char *pCursor=cpyBuffer;
	char **tempPointer=NULL;
	
	tempPointer=malloc(sizeof(char*)*3);
	
	
	
	cpyBuffer[4]='\0';
	tempPointer[0]=pCursor;
	tempPointer[1]=(pCursor+5);

	printf("\nArg 0 : %s",tempPointer[0]);
	printf("\nArg 0 : %s",tempPointer[1]);
	
	*tabPointer=tempPointer;
	
return 0;	
}

/*------------------------------------------------------------*/

int 
display(char ***tabPointer) {
	
return 0;
}





int main (int argc, char *argv[])
{
	char buffer[BUF_SIZE]={0};
	char **tabPointer=NULL;

	strcpy(buffer,"calc vs");
	
	cli(BUF_SIZE,buffer,&tabPointer);

	printf("\n arg 0 : %s",tabPointer[0]);
	
	return 0;

}
