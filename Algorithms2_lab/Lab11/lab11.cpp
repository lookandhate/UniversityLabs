#include <stdlib.h>
#include <stdio.h>


void readDataFromTextFile(const char* textFilePath,char** buffer, int& bufferSize)
{
	FILE* inputFilePtr;
	int openningError = fopen_s(&inputFilePtr, textFilePath, "rt");
	if (openningError)
	{
		exit(0x1337);
		// TODO: handle file openning error
	}
	int stringCount = 0;
	while ( !feof(inputFilePtr))
	{
		fgets(*buffer, 255, inputFilePtr);
		stringCount++;
	}
	bufferSize = stringCount;

}

int main()
{
	char* buffer;
	int bufferTrueSize = 0;
	readDataFromTextFile("C:\\Users\\root\\Desktop\\labs\\testTextFiles\\lab11\\testReadData.txt",
		&buffer, bufferTrueSize);
	getc(NULL);



}