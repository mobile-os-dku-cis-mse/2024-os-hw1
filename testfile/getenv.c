#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        printf("Usage: %s <ENV_VAR_NAME> <VALUE>\n", argv[0]);
        return 1;
    }

    // 환경 변수 설정
    if (setenv(argv[1], argv[2], 1) == -1) 
    {
        perror("Failed to set environment variable");
        return 1;
    }

    // 설정한 환경 변수 읽기
    char *value = getenv(argv[1]);
    if (value == NULL) 
    {
        printf("Environment variable not found.\n");
    } 
    else 
    {
        printf("Environment variable %s = %s\n", argv[1], value);
    }

    return 0;
}

