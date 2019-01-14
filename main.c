#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUF_SIZE 50


int CLI_Prompt(int bufSize, char *buffer, char ***tabPointer, size_t *nb);
int CLI_DisplayTabP(char **tabPointer, size_t nb);
int CLI_FreePP(char*** tabPointer, size_t nb);

/*------------------------------------------------------------*/

int 
CLI_Prompt(int bufSize, char *buffer, char ***tabPointer, size_t *nb) 
{
	char *pCursor=buffer;
	size_t i=0, arg=2;
	size_t bufLen=strlen(buffer);
	int gui=1;
	
	for(i=0; i<=bufLen; i++) {
		if (buffer[i]==34) {
			gui*=(-1);
		}
		else if (buffer[i]==32 && gui==1) {
			arg++;
		} 
	}
	
	*tabPointer=malloc(arg*sizeof(char*));
	(*tabPointer)[0]=NULL;
	(*tabPointer)[1]=pCursor;
	
	for (i=0, arg=1; i<=bufLen; i++) {
		if (*pCursor==34) {
			if (gui==1) {
				(*tabPointer)[arg]=pCursor+1;
			}
			else {
				*pCursor='\0';
			}
			gui*=(-1);
			pCursor++;
		}
		else if (*pCursor==32 && gui==1) {
			*pCursor='\0';
			pCursor++;
			arg++;
			(*tabPointer)[arg]=pCursor;
		}
		else {
			pCursor++;
		}

	}
	
	*nb=arg;
	
return 0;	
}

/*------------------------------------------------------------*/

int 
CLI_DisplayTabP(char **tabPointer, size_t nb) {
	size_t i=0;
	
	for (i=0; i<=nb; i++) {
	printf("\nElement [%lu]: %s",i,tabPointer[i]);
	}
return 0;
}

/*------------------------------------------------------------*/

int 
CLI_FreePP(char*** tabPointer, size_t nb) {
	size_t i=0;
	
	for (i=0; i<=nb; i++) {
		free((*tabPointer)[i]);
		
	}
	free(*tabPointer);
	*tabPointer=NULL;
}



/*------------------------------------------------------------*/

int main (int argc, char *argv[])
{
	char buffer[BUF_SIZE]={0};
	char **tabArg=NULL;
	size_t nbArg=1;


	if (argc==1) {
		printf("\n$ ");
		fgets(buffer,BUF_SIZE,stdin);
		CLI_Prompt(BUF_SIZE,buffer,&tabArg,&nbArg);
	}
	else {
		tabArg=argv;
		nbArg=argc-1;
	}

	CLI_DisplayTabP(tabArg,nbArg);
	
	CLI_FreePP(&tabArg,nbArg);
	
	
	printf("\n");
	system("pause");
	return 0;

}
