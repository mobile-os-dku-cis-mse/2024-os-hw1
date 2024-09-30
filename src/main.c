#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "strops.h"

static char **DIRS;

void run(char **argv)
{
	extern char **environ;
	char abs[4096]; // absolute filepath storage.

	if (argv[0][0] == '/' || argv[0][0] == '.' || argv[0][0] == '~')
	{
		if (execve(argv[0], argv, environ) == -1)
			perror(argv[0]);

		return;
	}
	
	for (int i = 0; DIRS[i]; i++)
	{
		sprintf(abs, "%s/%s", DIRS[i], argv[0]);

		if (access(abs, X_OK) == -1)
			continue;

		if (execve(abs, argv, environ) == -1)
			perror(argv[0]);
	}

	printf("%s: command not found\n", argv[0]);
}

void loop()
{
	char buf[1024];
	char *__buf;
	char **argv;
	pid_t spawn;
	
	while (1)
	{
		printf(">> ");
		if (!fgets(buf, 1024, stdin))
			break;

		__buf = strstrip(buf);
		if (!__buf[0])
			continue;

		if (!strcmp("quit", __buf))
			break;

		argv = malloc(sizeof(char*) * (strchrcnt(__buf, ' ')+2));
		strsplit(__buf, " ", argv);

		spawn = fork();

		// fork error.
		if (spawn == -1)
		{
			perror("fork");
			exit(1);
		}

		// parent process.
		if (spawn)
			wait(0);

		// child process; program execution is done here.
		else
		{
			run(argv);
			exit(0);
		}

		free(argv);
	}
}

int main()
{
	char *PATH;

	// parsing the 'PATH' environment variable.
	PATH = strdup(getenv("PATH"));
	DIRS = malloc(sizeof(char*) * (strchrcnt(PATH, ':')+2));
	strsplit(PATH, ":", DIRS);

	loop();

	free(PATH);
	free(DIRS);
	return 0;
}
