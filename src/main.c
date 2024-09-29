#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "strops.h"

void run(char **path_list, char **argv)
{
	extern char **environ;

	if (argv[0][0] == '/')
		execve(argv[0], argv, environ);
	else
	{
		char full[4096];
		
		for (int i = 0; path_list[i]; i++)
		{
			sprintf(full, "%s/%s", path_list[i], argv[0]);
			if (access(full, F_OK) == -1)
				continue;

			if (execve(full, argv, environ) == -1)
				perror(argv[0]);
		}
	}

	if (execve(argv[0], argv, environ) == -1)
		perror(argv[0]);
}

void loop(char **path_list)
{
	char buf[1024];
	
	while (1)
	{
		printf("> ");
		if (!fgets(buf, 1024, stdin))
			break;

		char *__buf = strstrip(buf);
		char **argv = malloc(sizeof(char*) * (strchrcnt(__buf, ' ')+2));
		strsplit(__buf, " ", argv);
		
		if (!strcmp("quit", buf))
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
			run(path_list, argv);
			exit(0);
		}
	}
}

int main()
{
	char *path = strdup(getenv("PATH"));
	char **path_list = malloc(sizeof(char*) * (strchrcnt(path, ':')+2));
	strsplit(path, ":", path_list);

	puts("SISH");
	loop(path_list);

	free(path_list);
	free(path);
	return 0;
}
