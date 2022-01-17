#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cassert>

#define _CRT_SECURE_NO_WARNINGS

#define INPUT_FILE "E:\\ULSTU\\Programming and algorithms\\testTextFiles\\lab11\\testReadData.txt"
#define OUTPUT_HTML_DOC "E:\\ULSTU\\Programming and algorithms\\testTextFiles\\lab11\\output.html"
#pragma warning(disable:4996)



void readDataFromTextFile(const char* textFilePath,char** &buffer, int& bufferSize)
{
	// Check if buffer initializaited
	if (!buffer)
	{
		buffer = (char**)malloc(sizeof(char*) * 32); // allocating memory for array of 32 pointers to char pointer
		printf("Memory for buffer allocated at 0x%p\n", buffer);
	}
	
	if (buffer == nullptr)
	{
		printf("Buffer is nullptr after allocating!\n");
		return;
	}

	FILE* inputFilePtr;
	int openningError = fopen_s(&inputFilePtr, textFilePath, "rt");
	if (openningError)
	{
		printf("Could not open text file! Error code %d\n", openningError);
		exit(0x1337);
		// TODO: handle file openning error
	}

	int currentIndexOfArrayWritingTo = 0;
	while (!feof(inputFilePtr))
	{
		// Check if string allocated( Actually its always gonna be true, 
		// cuz compiler sets pointer to point on random address.
		// For sake of safety put true in if-statement
		if (true)
		{
			printf("Allocating memory for buffer[%d]\n", currentIndexOfArrayWritingTo);
			// Allocating memory for string
			buffer[currentIndexOfArrayWritingTo] = (char*)malloc(sizeof(char) * 255);
		}
		else
		{
			printf("Memory for buffer[%d] already allocated at 0x%p", buffer[currentIndexOfArrayWritingTo]);
		}
		// write string readed from file in buffer
		fgets(buffer[currentIndexOfArrayWritingTo], 255, inputFilePtr);

		currentIndexOfArrayWritingTo++;
	}
	bufferSize = currentIndexOfArrayWritingTo;
}

bool isAInString(const char* stringToCheck)
{
	return !!strchr(stringToCheck, 'A');
}

int main()
{
	// Pointer to array of strings
	char** buffer = (char**)malloc(sizeof(char**));
	
	const char* boldNOPWord = "<i><b>NOP</b></i>";

	int bufferTrueSize = 0;
	readDataFromTextFile(INPUT_FILE,
		buffer, bufferTrueSize);
	
	for (size_t i = 0; i < bufferTrueSize; i++)
	{
		printf("buffer[%d] = %s\n", i, buffer[i]);
		
		char* copyOfCurrentString = (char*)malloc(sizeof(char*) * 255);
		char* newString = (char*)malloc(sizeof(char*) * 255);
		strcpy(newString, "\0");
		strcpy(copyOfCurrentString, buffer[i]);
		
		char* token = strtok(copyOfCurrentString, " ");
		while (token != NULL)
		{
			printf("\t token = %s;\n", token);
			if (isAInString(token))
			{
				printf("\t there is a A in the string, replacing it's with a NOP\n\n");
				strcat(newString, boldNOPWord);
				strcat(newString, " ");
			}
			else
			{
				printf("\t there are no As in the string -> not doing anything\n\n");
				strcat(newString, token);
				strcat(newString, " ");
			}
			token = strtok(NULL, " ");
		}

		strcpy(buffer[i], newString);
		// Removes /n from the end of string(buffer[i])
		buffer[i][strcspn(buffer[i], "\n")] = 0;
	}
	
	FILE* outputFilePtr;
	int outputFileOpenError = fopen_s(&outputFilePtr, OUTPUT_HTML_DOC, "wt");
	if (outputFileOpenError)
	{
		printf("Could not open text file for writing output data! Error code %d\n", outputFileOpenError);
		exit(0x1337);
		// TODO: handle file openning error
	}

	fprintf(outputFilePtr, "<HTML>\n\t<HEAD>\n\t\t<TITLE>%s</TITLE>\n\t</HEAD>\n", buffer[0]);
	fprintf(outputFilePtr, "\t<BODY>\n");
	fprintf(outputFilePtr, "\t\t<H1>%s</H1>\n", buffer[0]);
	
	for (size_t i = 1; i < bufferTrueSize; i++)
	{
		fprintf(outputFilePtr, "\t\t%s <BR>\n", buffer[i]);
	}
	
	fprintf(outputFilePtr, "\t</BODY>\n");
	fprintf(outputFilePtr, "</HTML>\n");    
	fclose(outputFilePtr);


}