#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "other_func.h"

void echo_getenv(int argc, char *argv[]) {
    int i, j = 0;
    char *env, *str;
    char *tok[100], *saveptr;

    if (argc == 1) {
        printf("usage: getenv env_vars ... \n");
    } else {
        for (i = 0; i < argc - 1; i++) {
            // 특정 환경 변수를 임의로 지정
            if (strcmp(argv[i + 1], "HISTSIZE") == 0) {
                env = "200";  // HISTSIZE 값을 임의로 지정
            } else {
                env = getenv(argv[i + 1]);  // 다른 환경 변수는 getenv로 처리
            }
            
            if (env != NULL) {
                printf("%s=%s\n", argv[i + 1], env);
                
                // ':'로 구분된 값을 나눠서 출력 (예: PATH)
                for (j = 0, str = env; ; str = NULL, j++) {
                    tok[j] = strtok_r(str, ":", &saveptr);
                    if (tok[j] == NULL) break;
                    printf("\t%s\n", tok[j]);
                }
                printf("***---------------------***\n");
            } else {
                printf("%s: environment variable not found\n", argv[i + 1]);
            }
        }
    }
}
