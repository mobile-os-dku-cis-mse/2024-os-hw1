#include <stdio.h>
#include <string.h>
#include <sys/types.h>

size_t strchrcnt(const char *s, int c)
{
	size_t cnt = 0;

	for (int i = 0; s[i]; i++)
	{
		if (s[i] == c)
			cnt++;
	}

	return cnt;
}

size_t strchrsplit(char *s, int c, const char **res)
{
	size_t cnt = 0;

	char delim[2];
	sprintf(delim, "%c", c);

	const char *token = strtok(s, delim);
	for (int i = 0; token; i++)
	{
		cnt++;
		res[i] = token;
		token = strtok(NULL, delim);
	}

	return cnt;
}
