#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	char input[1024];
	
	// so far, the program merely echoes the input back to the user.
	while (1)
	{
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

	return 0;
}
