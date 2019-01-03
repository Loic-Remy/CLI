#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 50





int cli(int bufSize, char *cpyBuffer);

cli(int bufSize, char *cpyBuffer) 
{
	char *pCursor=cpyBuffer;
	char **tabPointer=NULL;
	
	tabPointer=malloc(sizeof(char*)*3);
	
	
	
	cpyBuffer[4]='\0';
	tabPointer[0]=pCursor;
	tabPointer[1]=(pCursor+5);

	printf("\nArg 0 : %s",tabPointer[0]);
	printf("\nArg 0 : %s",tabPointer[1]);
return 0;	
}







int main (int argc, char *argv[])
{
	char buffer[BUF_SIZE]={0};
	/*
	printf("\n > ");
	fgets(buffer,BUF_SIZE,stdin);
	*/
	strcpy(buffer,"calc vs");
	
	cli(BUF_SIZE,buffer);

	
	
	return 0;

}
