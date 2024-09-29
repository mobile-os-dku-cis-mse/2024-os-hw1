#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *strstrip(char *s)
{
	int len = strlen(s);

	for (int i = len-1; i >= 0; i--)
	{
		if (isspace(s[i]))
			s[i] = 0;
		else
			break;
	}

	for (int i = 0; i < len; i++)
	{
		if (!isspace(s[i]))
			return s+i;
	}

	return s+len;
}

int strchrcnt(const char *s, int c)
{
	int cnt = 0;

	for (int i = 0; s[i]; i++)
	{
		if (s[i] == c)
			cnt++;
	}

	return cnt;
}

void strsplit(char *s, const char *delim, char **res)
{
	int cnt = 0;

	char *token = strtok(s, delim);
	for (int i = 0; token; i++)
	{
		cnt++;
		res[i] = token;
		token = strtok(NULL, delim);
	}

	res[cnt] = 0;
}
