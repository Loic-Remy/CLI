#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 50


int cli(int bufSize, char *buffer, char ***tabPointer, size_t *nb);
int displayTabP(char **tabPointer, size_t nb);

/*------------------------------------------------------------*/

int 
cli(int bufSize, char *buffer, char ***tabPointer, size_t *nb) 
{
	char *pCursor=buffer;
	size_t i=0, arg=2;
	size_t bufLen=strlen(buffer);
	
	for(i=0; i<=bufLen; i++) {
		if (buffer[i]==' ') {
			arg++;
		} 
	}
	
	*tabPointer=malloc(arg*sizeof(char*));
	(*tabPointer)[0]=NULL;
	(*tabPointer)[1]=pCursor;
	
	for (i=0, arg=1; i<=bufLen; i++) {
		if (*pCursor==32) {
			*pCursor='\0';
			pCursor++;
			arg++;
			(*tabPointer)[arg]=pCursor;
		}
		pCursor++;
	}
	
	*nb=arg;
	
return 0;	
}

/*------------------------------------------------------------*/

int 
displayTabP(char **tabPointer, size_t nb) {
	size_t i=0;
	
	for (i=0; i<=nb; i++) {
	printf("\nElement [%lu]: %s",i,tabPointer[i]);
	}
return 0;
}

/*------------------------------------------------------------*/

int main (int argc, char *argv[])
{
	char buffer[BUF_SIZE]={0};
	char **tabArg=NULL;
	size_t nbArg=1;

	strncpy(buffer,"edit vs 23.11.2018 \"Anniversaire Loic\"",BUF_SIZE);
	
	cli(BUF_SIZE,buffer,&tabArg,&nbArg);

	displayTabP(tabArg,nbArg);
	
	return 0;

}
