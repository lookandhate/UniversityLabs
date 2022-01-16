#include "string.h"

#include <cstdlib>

size_t lh_strlen(const char* string)
{
	size_t i = 0;
	while (string[i] != '\0')
		i++;
	return i;
}


void lh_strcpy(char* destination, const char* source)
{
	size_t sourceSize = lh_strlen(source);
	for (size_t i = 0; i <= sourceSize; i++)
		destination[i] = source[i];
}

char* lh_strcat(char* destination, const char* source)
{
	size_t sourceSize = lh_strlen(source);
	// Allocating enough memory for destination pointer, so it can accumulate old data from destination and new from source
	char* newString = (char*)malloc(sizeof(char*) * (lh_strlen(destination) + lh_strlen(source)));

	lh_strcpy(newString, destination);
	int indexToWriteTo = lh_strlen(destination);
	for (int i = 0; i <= sourceSize; i++, indexToWriteTo++)
	{
		//printf("i = %d, indexToWriteTo = %d, newString = %s", i, indexToWriteTo, newString);
		newString[indexToWriteTo] = source[i];
	}
	newString[indexToWriteTo + 1] = '\0';
	return newString;
}

int lh_strcmp(const char* str1, const char* str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

char* lh_strchr(char* str, int character)
{
	for (int i = 0; i < lh_strlen(str); i++)
	{
		if (character == (int)str[i])
			return &str[i];
	}
	return nullptr;
}


char* lh_strstr(char* str1, const char* str2)
{
	if (*str2 == '\0') {
		return str1;
	}

	for (int i = 0; i < lh_strlen(str1); i++)
	{
		if (*(str1 + i) == *str2)
		{
			char* ptr = lh_strstr(str1 + i + 1, str2 + 1);

			return (ptr) ? ptr - 1 : nullptr;
		}
	}

	return nullptr;
}