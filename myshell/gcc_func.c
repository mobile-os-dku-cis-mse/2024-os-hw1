#include <stdio.h>
#include <stdlib.h>

void gcc_function(char *argv[]){
    char *output_file = "a.out"; // 기본 출력 파일
    char temp_file[] = "temp.i"; // 임시 파일

    // 전처리
    FILE *input = fopen(source_file, "r");
    FILE *output = fopen(temp_file, "w");
    if (!input || !output) {
        perror("File opening failed");
        exit(1);
    }
    preprocess(input, output);
    fclose(input);
    fclose(output);

    // 컴파일 (여기서는 gcc를 사용)
    char command[1024];
    snprintf(command, sizeof(command), "gcc -o %s %s", output_file, temp_file);
    system(command);

    // 임시 파일 삭제
    remove(temp_file);
}