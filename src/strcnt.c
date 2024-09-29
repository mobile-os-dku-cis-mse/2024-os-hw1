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
