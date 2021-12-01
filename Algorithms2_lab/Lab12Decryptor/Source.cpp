#include <stdlib.h>
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
struct LabelData
{
	int posX, posY;
	char labelString[255];
	int colorRedRate, colorGreenRate, colorBlueRate;
	int fontSize;
};

int main()
{
	FILE* outputBinaryFilePtr;
	outputBinaryFilePtr = fopen("C:\\Users\\root\\Desktop\\labs\\testTextFiles\\lab12\\file.bin", "wb");


	printf("Lab 12 decryptor.\n");
	printf("How many labels are there gonna be:");
	
	int labelsCount;

	scanf("%d", &labelsCount);
	fwrite(&labelsCount, sizeof(int), 1, outputBinaryFilePtr);
	
	LabelData* labels = (LabelData*)malloc(sizeof(LabelData) * labelsCount);
	for (int i = 0; i < labelsCount; i++)
	{
		printf("Data for label %d\n", i + 1);
		LabelData labelData;

		printf("Input x and y position for the label: ");
		scanf("%d%d", &labelData.posX, &labelData.posY);

		printf("\nInput R G B colors for the label: ");
		scanf("%d%d%d", &labelData.colorRedRate, &labelData.colorGreenRate, &labelData.colorBlueRate);

		printf("\nInput the text for the label: ");
		scanf("%s", &labelData.labelString);

		printf("\nInput label font size: ");
		scanf("%d", &labelData.fontSize);


		fwrite(&labelData, sizeof(labelData), 1, outputBinaryFilePtr);
		printf("\n C:\\Users\\user\\Desktop\\Algorithms\\\file.bin");
	}
}