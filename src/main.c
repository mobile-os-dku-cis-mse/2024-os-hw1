#include <stdio.h>
#include <string.h>

int main()
{
	char input[1024];
	
	// so far, the program merely echoes the input back to the user.
	while (1)
	{
		fgets(input, 1024, stdin);

		char *__lnptr = strchr(input, '\n');
		if (__lnptr)
			*__lnptr = 0;
		
		if (!strcmp("quit", input))
			break;

		puts(input);
	}

	return 0;
}
