#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
	int i, j=0;
	char *env, *str;
	char *tok[100], *saveptr;
	if (argc == 1)	{
		printf("usage: getenv env_vars ... \n");
		printf("example: \"./a.out PATH HOME\"\n");
		return 0;
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

	return 0;
}

/*
환경 변수의 이름을 명령어 인자로 받은 뒤, 해당 정보를 출력하는 프로그램
키-값 쌍... 시스템 설정과 사용자 정보, 경로 등의 정보 저장
프로세스 실행 환경 설정과 프로그램의 올바른 동작 지원
어떤 경로에서든 특정 실행 가능 파일 실행 가능(txt, python, gcc 등)
*/