#include <cstdlib>
#include <stdio.h>
#include "string.h"
#pragma warning(disable:4996)
int main()
{
	char* userInput= (char*)malloc(sizeof(char) * 32);
	lh_strcpy(userInput, "\0");
	printf("Enter data to string[at address 0x%p]: ", userInput);
	scanf("%s", userInput);
	
	char* copyTo = (char*)malloc(sizeof(char) * 32);
	printf("Copying data '%s' from 0x%p to 0x%p\n", userInput, userInput, copyTo);
	lh_strcpy(copyTo, userInput);


	printf("Data at 0x%p is '%s'\n", copyTo, copyTo);
	printf("Difference between copied string and source string from input: %d\n", lh_strcmp(userInput, copyTo));
	
	printf("Length input string is %d\n\n", lh_strlen(copyTo));

	printf("Input string you want to append at the end of copied(0x%p): ", copyTo);
	char* whatWeWantToAppendAtTheEnd = (char*)malloc(sizeof(char) * 32);
	scanf("%s", whatWeWantToAppendAtTheEnd);
	copyTo = lh_strcat(copyTo, whatWeWantToAppendAtTheEnd);
	
	printf("Appended '%s' at the end of copy of source string, now its '%s' and it's length equal to %d\n",
		whatWeWantToAppendAtTheEnd, copyTo, lh_strlen(copyTo));
	printf("Difference between copied+modified string and source string from input: %d\n\n", lh_strcmp(userInput, copyTo));

	printf("What character do you want to find in string: ");
	char* charToFind = (char*)malloc(sizeof(char));
	scanf("%s", charToFind);

	printf("\nTrying to find %c in %s: %s\n\n", *charToFind, copyTo, lh_strchr(copyTo, *charToFind));

	printf("What string do you want to find in this(%s) string: ", copyTo);
	char* stringToFind = (char*)malloc(sizeof(char) * 32);
	scanf("%s", stringToFind);
	printf("\nTrying to find %s in %s: %s\n", stringToFind, copyTo, lh_strstr(copyTo, stringToFind));



}