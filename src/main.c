#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "strcnt.h"

int main()
{
	// fetching the value of the 'PATH' environment variable.
	const char *PATH = getenv("PATH");
	char *path_copy = malloc(sizeof(char) * (strlen(PATH)+1));
	strcpy(path_copy, PATH);

	// tokenizing the full string into individual paths for easier lookup.
	const char **path_list = malloc(sizeof(char*) * (strchrcnt(path_copy, ':')+1));
	const char *__path_token = strtok(path_copy, ":");
	int path_cnt = 0;
	for (int i = 0; __path_token; i++)
	{
		path_list[i] = __path_token;
		path_cnt++;
		__path_token = strtok(NULL, ":");
	}

	puts("recognized system paths:");
	for (int i = 0; i < path_cnt; i++)
		puts(path_list[i]);

	char input[1024];
	
	// so far, the program merely echoes the input back to the user.
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
			printf("process %d spawned from process %d\n", getpid(), getppid());
			puts(input);
			exit(0);
		}
	}

	free(path_list);
	free(path_copy);
	return 0;
}
