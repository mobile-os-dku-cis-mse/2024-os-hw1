#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "other_func.h"

//cd --> chdir
void cd_command(char *command){
    // 현재 dir 주소 저장
    char cwd[100]; 
    getcwd(cwd, sizeof(cwd));
    printf("%s -> ", cwd);

   //cd 판별
   char *path = command + 3; // "cd " 이후의 경로

    if(strcmp(path, "~") == 0){ // (by. ChatGPT)
        // 환경 변수 HOME을 통해 홈 디렉토리 가져오기
        char *home = getenv("HOME");
        if(chdir(home) != 0){
            perror("chdir failed");
        };
    }
    else {
        if (chdir(path) != 0) {
            perror("chdir failed"); // 변경 실패 시 오류 출력
        }
    }
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);

    return; // 자식 프로세스 생성하지 않음
}