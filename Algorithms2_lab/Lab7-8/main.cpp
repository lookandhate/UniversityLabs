#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

#define MY_PC

#ifdef MY_PC
#define PATH_TO_INPUT_TEXT_FILE "C:\\Users\\root\\Desktop\\LabsTextFiles\\input.txt.txt"

#define PATH_TO_OUTPUT_FILE "C:\\Users\\root\\Desktop\\LabsTextFiles\\output_d.txt"
#else
#define PATH_TO_INPUT_TEXT_FILE "C:\\Users\\USER\\Desktop\\input.txt"
#define PATH_TO_OUTPUT_FILE "C:\\Users\\USER\\Desktop\\output.txt"
#endif

namespace Utils {
	void PrintArray(size_t arraySize, int arrayToPrint[])
	{
		for (int i = 0; i < arraySize; i++)
		{
			printf("%d ", arrayToPrint[i]);
		}
		printf("\n");
	}

	void PrintArrayToFile(size_t arraySize, int arrayToPrint[], FILE* filePtr)
	{
		for (int i = 0; i < arraySize; i++)
		{
			fprintf(filePtr, "%d ", arrayToPrint[i]);
		}
	}

	void InputArray(size_t arraySize, int arrayToFill[])
	{
		for (int i = 0; i < arraySize; i++)
		{
			scanf_s("%d", arrayToFill + i);
		}
	}

	void ReadArrayFromFile(int **arrayToFill, int* createdArraySize)
	{
		FILE* filePtr;
		fopen_s(&filePtr, PATH_TO_INPUT_TEXT_FILE, "rt");
		fscanf_s(filePtr, "%d", createdArraySize);

		printf_s("Size = %d\n", *createdArraySize);
		*arrayToFill = (int*)malloc(sizeof(int) * (*(createdArraySize)));
		for (int i = 0; i < *(createdArraySize); i++)
		{
			fscanf_s(filePtr, "%d", &((*arrayToFill)[i]));
		}
		fclose(filePtr);
	}

	void FindMinAndMax(size_t arraySize, int arrayToModificate[],
		int* maxElementPtr, int* minElementPtr,
		int* maxElementIndexPtr, int* minElementIndexPtr)
	{
		*maxElementIndexPtr = 0;
		*minElementIndexPtr = 0;
		*maxElementPtr = arrayToModificate[0];
		*minElementPtr = arrayToModificate[0];
		for (int i = 0; i < arraySize; i++)
		{
			if (*maxElementPtr < arrayToModificate[i])
			{
				*maxElementPtr = arrayToModificate[i];
				*maxElementIndexPtr = i;
			}

			if (*minElementPtr > arrayToModificate[i])
			{
				*minElementPtr = arrayToModificate[i];
				*minElementIndexPtr = i;
			}
		}
	}

	
}

namespace Lab7 
{
	void PerformActionOnArrayTaskA(size_t arraySize, int arrayToModificate[])
	{
		for (int i = 0; i < arraySize; i++)
		{
			if (*(arrayToModificate + i) % 2 == 0)
				*(arrayToModificate + i) *= -1;
		}
	}
	
	void PerformActionTaskC(size_t arraySize, int arrayToModificate[],
		size_t leftBorder, size_t rightBorder)
	{
		for (int i = 0; i < arraySize; i++)
		{
			if ((i < rightBorder && i > leftBorder) && arrayToModificate[i] % 2 == 0)
				printf("%d ", arrayToModificate[i]);
		}
	}

	void TaskA()
	{
		printf("Specify how many elements there would be: ");
		int arraySize;
		scanf_s("%d", &arraySize);

		int* arrayPointer = (int*)malloc(sizeof(int) * arraySize);
		printf("Input array elements:");

		Utils::InputArray(arraySize, arrayPointer);
		Lab7::PerformActionOnArrayTaskA(arraySize, arrayPointer);

		printf("Modificated array: ");
		Utils::PrintArray(arraySize, arrayPointer);

	}


	void TaskB()
	{
		printf("Specify how many elements there would be: ");
		int arraySize;
		scanf_s("%d", &arraySize);

		int* arrayPointer = (int*)malloc(sizeof(int) * arraySize);
		printf("Input array elements:");

		Utils::InputArray(arraySize, arrayPointer);

		int max;
		int min;
		int maxIndex;
		int minIndex;
		Utils::FindMinAndMax(arraySize, arrayPointer, &max, &min, &maxIndex, &minIndex);

		printf("Max element = %d\nMin element = %d", max, min);

	}


	void TaskC()
	{
		printf("Specify how many elements there would be: ");
		int arraySize;
		scanf_s("%d", &arraySize);

		int* arrayPointer = (int*)malloc(sizeof(int) * arraySize);
		printf("Input array elements:");

		Utils::InputArray(arraySize, arrayPointer);

		int max;
		int min;
		int maxIndex;
		int minIndex;
		Utils::FindMinAndMax(arraySize, arrayPointer, &max, &min, &maxIndex, &minIndex);

		int leftBorder;
		int rightBorder;
		if (maxIndex > minIndex)
		{
			rightBorder = maxIndex;
			leftBorder = minIndex;
		}
		else
		{
			rightBorder = minIndex;
			leftBorder = maxIndex;
		}

		Lab7::PerformActionTaskC(arraySize, arrayPointer, leftBorder, rightBorder);

	}


	void TaskD()
	{

		printf("Specify how many elements there would be: ");
		int arraySize;
		scanf_s("%d", &arraySize);

		int* arrayPointer = (int*)malloc(sizeof(int) * arraySize);
		printf("Input array elements:");

		Utils::InputArray(arraySize, arrayPointer);

		int max;
		int min;
		int maxIndex;
		int minIndex;
		Utils::FindMinAndMax(arraySize, arrayPointer, &max, &min, &maxIndex, &minIndex);

		int leftBorder;
		int rightBorder;
		if (maxIndex > minIndex)
		{
			rightBorder = maxIndex;
			leftBorder = minIndex;
		}
		else
		{
			rightBorder = minIndex;
			leftBorder = maxIndex;
		}

		int newSize = 0;
		for (int i = 0; i < arraySize; i++)
		{
			// i not in [leftBorder;rightBorder] -> saving all elements
			if (i <= leftBorder || i >= rightBorder)
			{
				arrayPointer[newSize] = arrayPointer[i];
				newSize++;
			}
			else
			{
				if (arrayPointer[i] % 2 != 0)
				{
					arrayPointer[newSize] = arrayPointer[i];
					newSize++;
				}
			}
		}
		Utils::PrintArray(newSize, arrayPointer);

	}

}

namespace Lab8
{

	void PerformActionOnArrayTaskA(size_t arraySize, int arrayToModificate[])
	{
		for (int i = 0; i < arraySize; i++)
		{
			if (*(arrayToModificate + i) % 2 == 0)
				*(arrayToModificate + i) *= -1;
		}
	}

	void PerformActionTaskC(size_t arraySize, int arrayToModificate[],
		size_t leftBorder, size_t rightBorder,
		FILE* filePtr)
	{
		for (int i = 0; i < arraySize; i++)
		{
			if ((i < rightBorder && i > leftBorder) && arrayToModificate[i] % 2 == 0)
				fprintf(filePtr, "%d ", arrayToModificate[i]);
		}
	}

	void TaskA()
	{
		int arraySize;
		int* arrayPointer = nullptr;
		Utils::ReadArrayFromFile(&arrayPointer, &arraySize);
		Lab7::PerformActionOnArrayTaskA(arraySize, arrayPointer);
		Utils::PrintArray(arraySize, arrayPointer);

		FILE* outputFilePtr;

		fopen_s(&outputFilePtr, PATH_TO_OUTPUT_FILE, "wt");
		Lab8::PerformActionOnArrayTaskA(arraySize, arrayPointer);
		Utils::PrintArrayToFile(arraySize, arrayPointer, outputFilePtr);

	}

	void TaskB()
	{
		int arraySize;
		int* arrayPointer = nullptr;
		Utils::ReadArrayFromFile(&arrayPointer, &arraySize);
		int min; int max; int minIndex; int maxIndex;
		Utils::FindMinAndMax(arraySize, arrayPointer, &max, &min, &maxIndex, &minIndex);
		
		FILE* outputFilePtr;

		fopen_s(&outputFilePtr, "C:\\Users\\USER\\Desktop\\output_b.txt", "wt");
		fprintf(outputFilePtr, "Min = %d, max = %d", min, max);

		free(arrayPointer);
		fclose(outputFilePtr);

	}


	void TaskC()
	{
		int arraySize;
		int* arrayPointer = nullptr;
		Utils::ReadArrayFromFile(&arrayPointer, &arraySize);
		int min; int max; int minIndex; int maxIndex;
		Utils::FindMinAndMax(arraySize, arrayPointer, &max, &min, &maxIndex, &minIndex);


		int leftBorder;
		int rightBorder;
		if (maxIndex > minIndex)
		{
			rightBorder = maxIndex;
			leftBorder = minIndex;
		}
		else
		{
			rightBorder = minIndex;
			leftBorder = maxIndex;
		}


		FILE* outputFilePtr;

		fopen_s(&outputFilePtr, "C:\\Users\\USER\\Desktop\\output_c.txt", "wt");
		PerformActionTaskC(arraySize, arrayPointer, leftBorder, rightBorder, outputFilePtr);
		fclose(outputFilePtr);
		free(arrayPointer);

	}

	void TaskD()
	{
		int arraySize;
		int* arrayPointer = nullptr;
		Utils::ReadArrayFromFile(&arrayPointer, &arraySize);
		int min; int max; int minIndex; int maxIndex;
		Utils::FindMinAndMax(arraySize, arrayPointer, &max, &min, &maxIndex, &minIndex);


		int leftBorder;
		int rightBorder;
		if (maxIndex > minIndex)
		{
			rightBorder = maxIndex;
			leftBorder = minIndex;
		}
		else
		{
			rightBorder = minIndex;
			leftBorder = maxIndex;
		}


		FILE* outputFilePtr;

		fopen_s(&outputFilePtr, PATH_TO_OUTPUT_FILE, "wt");

		int newSize = 0;
		for (int i = 0; i < arraySize; i++)
		{
			// i not in [leftBorder;rightBorder] -> saving all elements
			if (i <= leftBorder || i >= rightBorder)
			{
				arrayPointer[newSize] = arrayPointer[i];
				newSize++;
			}
			else // saving only odd elements
			{
				if (arrayPointer[i] % 2 != 0)
				{
					arrayPointer[newSize] = arrayPointer[i];
					newSize++;
				}
			}
		}
		Utils::PrintArrayToFile(newSize, arrayPointer, outputFilePtr);
		free(arrayPointer);
		fclose(outputFilePtr);
	}

}
int main()
{
	//Lab7::TaskD();
	Lab8::TaskD();
}