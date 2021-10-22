#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

//
//void encrypt(char* key, char* words, char* cipher)
//{
//	int kLen = strlen(key);
//	int wLen = strlen(words);
//	int i, j, pos;
//
//	for (i = 0; i < wLen; i += kLen)
//	{
//		for (j = 0; j < kLen; ++j)
//		{
//			pos = key[j] - '0' - 1 + i;
//
//			if (pos < wLen)
//			{
//				sprintf(cipher, "%s%c", cipher, tolower(words[pos]));
//			}
//			else
//			{
//				sprintf(cipher, "%s ", cipher);
//			}
//		}
//	}
//}
