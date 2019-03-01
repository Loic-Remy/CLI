#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../inc/cli.h"

#define BUF_SIZE 100
#define QUOTE 34
#define BLANK_SPACE 32
 


static char *ErrorCodeDesc[] = {
	"No error", /* 0 - CLI_SUCCESS */
	"Memory allocation failed", /* 1 - CLI_MEMORYERROR */
	"Failed to open the file", /* 2 - CLI_FILEERROR */
	"Miss end quote in commande-line"	/* CLI_MISSENQUOTE */
};



/*--------------------- F U N C ------------------------------*/

CLI_ErrorCode 
CLI_Prompt(const char *text, char *buffer,FILE *stream) {
	
	if (0<strlen(text)) {
			printf("%s ",text);
	}

	fgets(buffer,BUF_SIZE,stream);
	
	return CLI_SUCCESS;
}

/*--------------------- F U N C ------------------------------*/

CLI_ErrorCode 
CLI_Interpret(char *buffer, char ***tabPointer, size_t *nb) 
{
	char *pCursor=buffer;
	size_t i=0, arg=2;
	size_t bufLen=strlen(buffer);
	int inQuote=1;
	
	for(i=0; i<=bufLen; i++) {
		if (buffer[i]==QUOTE) {
			inQuote*=(-1);
		}
		else if (buffer[i]==BLANK_SPACE && inQuote==1) {
			arg++;
		} 
	}
	
	*tabPointer=malloc(arg*sizeof(char*));
	if(NULL==tabPointer) {return CLI_MEMORYERROR;}

	(*tabPointer)[0]=NULL;
	(*tabPointer)[1]=pCursor;
	
	for (i=0, arg=1; i<=bufLen; i++) {
		if (*pCursor==BLANK_SPACE) {
			if (inQuote==1) {
				(*tabPointer)[arg]=pCursor+1;
			}
			else {
				*pCursor='\0';
			}
			inQuote*=(-1);
			pCursor++;
		}
	else if (*pCursor==BLANK_SPACE && inQuote==1) {
			*pCursor='\0';
			pCursor++;
			arg++;
			(*tabPointer)[arg]=pCursor;
		}
		else if (*pCursor=='\n') {
			*pCursor='\0';
		}
		else {
			pCursor++;
		}

	}
	
	*nb=arg;
	
return CLI_SUCCESS;
}

/*--------------------- F U N C ------------------------------*/

void
CLI_DisplayArg(char **tabPointer, size_t nb) {
	size_t i=0;
	
	for (i=0; i<=nb; i++) {
	printf("\nElement [%zd]: %s",i,tabPointer[i]);
	}
}

/*--------------------- F U N C ------------------------------*/

CLI_ErrorCode 
CLI_FreePP(char*** tabPointer, size_t nb) {
	size_t i=0;
	
	for (i=0; i<=nb; i++) {
		free((*tabPointer)[i]);
		
	}
	free(*tabPointer);
	*tabPointer=NULL;
	
	return CLI_SUCCESS;
}

/*--------------------- F U N C ------------------------------*/

void
CLI_DisplayError(CLI_ErrorCode error) {
	
	printf("\n%d\t%s",error,ErrorCodeDesc[error]);
}

