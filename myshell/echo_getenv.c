#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "other_func.h"

void echo_getenv(int argc, char *argv[]) {
	int i, j=0;
	char *env, *str;
	char *tok[100], *saveptr;
	if (argc == 1)	{
		printf("usage: getenv env_vars ... \n");
	} else {
		for (i = 0 ; i < argc-1 ; i++) {
			env = getenv(argv[i+1]);
			printf("%s=%s\n", argv[i+1], env);
			for (j=0,str=env; ;str= NULL,j++) {
				tok[j] = strtok_r(str, ":", &saveptr);
				if (tok[j] == NULL) break;
				printf("\t%s\n", tok[j]);
			}
			printf("***---------------------***\n");
		}
	}
}
