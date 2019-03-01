#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/cli.h"

#include "CUnit/Basic.h"

#define T_TEST_T


char testBuffer[150];
char **tabArg=NULL;
size_t nb=0;


int init_suite_Prompt(void)
{


	return 0;
}

int clean_suite_Prompt(void) 
{

	return 0;	
}

int init_suite_Interpret(void)
{
	return 0;
}

int clean_suite_Interpret(void) 
{
	memset(testBuffer,0,150);
	return 0;	
}

/*------ TESTS FOR 'CLI_Prompt' ---------------------*/

void test_no_text(void) 
{
	char buffer[150]={0};
	FILE* testStream=NULL;
	
	testStream=fopen("testFile.txt","w");
	if(NULL!=testStream) {
		fputs("",testStream);
		fclose(testStream);
	}
	testStream=fopen("testFile.txt","r");
	if(NULL!=testStream)
	{
		CLI_Prompt("",buffer,testStream);
		CU_ASSERT_STRING_EQUAL(buffer,"");
	}
	fclose(testStream);
}

void test_normal_text(void) 
{
	char buffer[150]={0};
	FILE* testStream=NULL;
	
	testStream=fopen("testFile.txt","w");
	if(NULL!=testStream) {
		fputs("avion",testStream);
		fclose(testStream);
	}
	testStream=fopen("testFile.txt","r");
	if(NULL!=testStream)
	{
		CLI_Prompt("",buffer,testStream);
		CU_ASSERT_STRING_EQUAL(buffer,"avion");
	}
	fclose(testStream);
}

void test_normal_text_2(void) 
{
	char buffer[150]={0};
	FILE* testStream=NULL;
	
	testStream=fopen("testFile.txt","w");
	if(NULL!=testStream) {
		fputs("avion voiture",testStream);
		fclose(testStream);
	}
	testStream=fopen("testFile.txt","r");
	if(NULL!=testStream)
	{
		CLI_Prompt("",buffer,testStream);
		CU_ASSERT_STRING_EQUAL(buffer,"avion voiture");
	}
	fclose(testStream);
}

void test_buffer_overflow(void) 
{
	char buffer[100]={0};
	FILE* testStream=NULL;
	
	testStream=fopen("testFile.txt","w");
	if(NULL!=testStream) {
		fputs("avion voiture bateau pierre age toilettes noir vieux drole test dure chiant tigre oiseau viande qui ? idem pourri 123",testStream);
		fclose(testStream);
	}
	testStream=fopen("testFile.txt","r");
	if(NULL!=testStream)
	{
		CLI_Prompt("",buffer,testStream);
		CU_ASSERT_STRING_EQUAL(buffer,"avion voiture bateau pierre age toilettes noir vieux drole test dure chiant tigre oiseau viande qui");
	}
	fclose(testStream);
}

/*------ TESTS FOR 'CLI_Interpret' ---------------------*/

void test_nbArg_1(void)
{
	strcpy(testBuffer,"avion");
	CLI_Interpret(testBuffer,&tabArg,&nb);
	CU_ASSERT_STRING_EQUAL(tabArg[1],"avion");
}

void test_nbArg_2(void)
{
	strcpy(testBuffer,"avion voiture");
	CLI_Interpret(testBuffer,&tabArg,&nb);
	CU_ASSERT_STRING_EQUAL(tabArg[1],"avion");
	CU_ASSERT_STRING_EQUAL(tabArg[2],"voiture");

}

void test_EndQuoted(void)
{
	strcpy(testBuffer,"avion \"""voiture maison\"");
	CLI_Interpret(testBuffer,&tabArg,&nb);
	CU_ASSERT_STRING_EQUAL(tabArg[1],"avion");
	CU_ASSERT_STRING_EQUAL(tabArg[2],"voiture maison");
}

void test_StartQuoted(void)
{
	strcpy(testBuffer,"\"avion voiture\" maison");
	CLI_Interpret(testBuffer,&tabArg,&nb);
	CU_ASSERT_STRING_EQUAL(tabArg[1],"avion voiture");
	CU_ASSERT_STRING_EQUAL(tabArg[2],"maison");
}

void test_MissEndQuote(void)
{
	strcpy(testBuffer,"avion \"voiture");
	CLI_Interpret(testBuffer,&tabArg,&nb);
	CU_ASSERT_STRING_EQUAL(tabArg[1],"avion");
	CU_ASSERT_STRING_EQUAL(tabArg[2],"voiture");
}

void test_DoubleQuote(void)
{
	strcpy(testBuffer,"avion \"\"voiture\"\"");
	CLI_Interpret(testBuffer,&tabArg,&nb);
	CU_ASSERT_STRING_EQUAL(tabArg[1],"avion");
	CU_ASSERT_STRING_EQUAL(tabArg[2],"\"voiture\"");
}



int main() {

	CU_pSuite pCLI_Prompt=NULL, pCLI_Interpret=NULL;

	/* initialize the CUnit test registry */	
	if (CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

   /* add a suite to the registry */
   pCLI_Prompt = CU_add_suite("CLI_Prompt()", init_suite_Prompt, clean_suite_Prompt);
   if (NULL == pCLI_Prompt) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   pCLI_Interpret = CU_add_suite("Suite_Interpret", init_suite_Interpret, clean_suite_Interpret);
   if (NULL == pCLI_Interpret) {
      CU_cleanup_registry();
      return CU_get_error();
   }


	/* add the tests to the suite */
   if ((NULL == CU_add_test(pCLI_Prompt, "Pass no text", test_no_text)) ||
   		NULL == CU_add_test(pCLI_Prompt,"Pass 'avion'", test_normal_text) ||
		NULL == CU_add_test(pCLI_Prompt,"Pass 'avion voiture'", test_normal_text_2)  ||
		NULL == CU_add_test(pCLI_Prompt,"Pass 'avion voiture...'", test_buffer_overflow))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if ((NULL == CU_add_test(pCLI_Interpret,"Pass 1 arg", test_nbArg_1)) ||
   		NULL == CU_add_test(pCLI_Interpret,"Pass 2 arg", test_nbArg_2) ||
		NULL == CU_add_test(pCLI_Interpret,"End with quoted arg", test_EndQuoted) ||
		NULL == CU_add_test(pCLI_Interpret,"Start with quoted arg", test_StartQuoted) ||
		NULL == CU_add_test(pCLI_Interpret,"Miss end quote", test_MissEndQuote) ||
		NULL == CU_add_test(pCLI_Interpret,"Double quote", test_DoubleQuote))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }



 /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();

}
