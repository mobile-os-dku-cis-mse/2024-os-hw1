#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "strops.h"

void run(const char **path_list, int path_cnt)
{
	char input[1024];
	
	while (1)
	{
		printf("> ");
		if (!fgets(input, 1024, stdin))
			break;

		char *__lnptr = strchr(input, '\n');
		if (__lnptr)
			*__lnptr = 0;
		
		if (!strcmp("quit", input))
			break;

		pid_t spawn = fork();

		// fork error.
		if (spawn == -1)
			exit(0);

		// parent process.
		if (spawn)
			wait(0);

		// child process; echoing is done here.
		else
		{
			puts(input);
			exit(0);
		}
	}
}

int main()
{
	// fetching the value of the 'PATH' environment variable.
	char *path = strdup(getenv("PATH"));
	const char **path_list = malloc(sizeof(char*) * (strchrcnt(path, ':')+1));
	int path_cnt = strchrsplit(path, ':', path_list);

	run(path_list, path_cnt);

	free(path_list);
	free(path);
	return 0;
}
