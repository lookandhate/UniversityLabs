#include "string.h"

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

void lh_strcat(char* destination, const char* source)
{
	size_t sourceSize = lh_strlen(source)
}
