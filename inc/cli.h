
#ifndef H_CLI_H
#define H_CLI_H


typedef int CLI_ErrorCode;

enum CLI_ErrorCode {
	CLI_SUCCESS,
	CLI_MEMORYERROR,
	CLI_FILEERROR,
	CLI_MISSENDQUOTE
};

CLI_ErrorCode CLI_Prompt(const char *text, char *buffer, FILE *stream);
CLI_ErrorCode CLI_Interpret(char *buffer, char ***tabPointer, size_t *nb);
void CLI_DisplayArg(char **tabPointer, size_t nb);
CLI_ErrorCode CLI_FreePP(char*** tabPointer, size_t nb);
void CLI_DisplayError(CLI_ErrorCode error);




#endif

