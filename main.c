#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 50


int cli(int bufSize, char *cpyBuffer, char ***tabPointer, size_t *nb);
int display(char **tabPointer, int nb);

/*------------------------------------------------------------*/

int 
cli(int bufSize, char *cpyBuffer, char ***tabPointer, size_t *nb) 
{
	char *pCursor=cpyBuffer;
	char **tempPointer=NULL;
	size_t i=0;
	
	tempPointer=malloc(sizeof(char*)*3);
	tempPointer[0]=pCursor;
	
	for (i=0; i<=strlen(cpyBuffer)-1; i++) {
		if (strcmp(pCursor," ")==0) {
			*pCursor='\0';
			pCursor++;
			tempPointer[*nb]=pCursor;
			(*nb)++;
		}
		pCursor++;
	}
	
	*tabPointer=tempPointer;
	
return 0;	
}

/*------------------------------------------------------------*/

int 
display(char **tabPointer, int nb) {
	size_t i=0;
	
	for (i=0; i<=nb; i++) {
	printf("\nArg [%d] : %s",i,tabPointer[i]);
	}
return 0;
}





int main (int argc, char *argv[])
{
	char buffer[BUF_SIZE]={0};
	char **tabPointer=NULL;
	size_t nb=1;

	strcpy(buffer,"calc vs 23.11.18 24.11.18");
	
	cli(BUF_SIZE,buffer,&tabPointer,&nb);

	display(tabPointer,1);
	
	return 0;

}
