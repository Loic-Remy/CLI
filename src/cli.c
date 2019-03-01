#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../inc/cli.h"


#define BUF_SIZE 100
#define QUOTE 34
#define BLANK_SPACE 32
#define CARRIAGE_RETURN 13
#define NUL 0
 

static char *ErrorCodeDesc[] = {
	"No error", 						/* 0 - CLI_SUCCESS */
	"Memory allocation failed", 		/* 1 - CLI_MEMORYERROR */
	"Failed to open the file", 			/* 2 - CLI_FILEERROR */
	"Miss end quote in commande-line"	/* 3 - CLI_MISSENQUOTE */
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
	size_t i=0, arg=1, newArg=1;
	size_t bufLen=strlen(buffer);
	int inQuote=-1;
	
	*tabPointer=malloc(bufLen/2+1*sizeof(char*));
	if(NULL==tabPointer) 
		return CLI_MEMORYERROR;
	
	for(i=0; i<=bufLen-1; i++) {
		if (buffer[i]==QUOTE) {
			buffer[i]=NUL;
			inQuote*=(-1);
			newArg=1;
		}
		else if (buffer[i]==BLANK_SPACE && inQuote==-1) {
			buffer[i]=NUL;
			newArg=1;
		}
		else if (buffer[i]==CARRIAGE_RETURN) {
			buffer[i]=NUL;
			newArg=1;
		}
		else {
			if (newArg==1) {
				(*tabPointer)[arg]=&buffer[i];
				arg++;
				newArg=0;
			}
		}
	}
	
	if (inQuote==1)
		return CLI_MISSENDQUOTE;
	
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

/*--------------------- F U N C ------------------------------*/




