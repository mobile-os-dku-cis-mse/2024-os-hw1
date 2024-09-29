//
// Created by hochacha on 24. 9. 27.
//

#include "argument_parser.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ARGS 1024

// Ai Generated code
int expand_environment_variables(const char *input, char *output, int output_size) {
    int i = 0, j = 0;
    while (input[i] != '\0' && j < output_size - 1) {
        if (input[i] == '$') {
            i++;
            // 환경 변수 이름 추출
            char var_name[256];
            int k = 0;

            if (input[i] == '{') {
                i++; // '{' 건너뜀
                while (input[i] != '\0' && input[i] != '}' && k < sizeof(var_name) - 1) {
                    var_name[k++] = input[i++];
                }
                if (input[i] == '}') i++; // '}' 건너뜀
            } else {
                while (input[i] != '\0' && (isalnum((unsigned char)input[i]) || input[i] == '_') && k < sizeof(var_name) - 1) {
                    var_name[k++] = input[i++];
                }
            }
            var_name[k] = '\0';

            // 환경 변수 값 가져오기
            char *value = getenv(var_name);
            if (value != NULL) {
                int l = 0;
                while (value[l] != '\0' && j < output_size - 1) {
                    output[j++] = value[l++];
                }
            }
        } else {
            output[j++] = input[i++];
        }
    }
    output[j] = '\0';
    return 0;
}

// AI Generated Code
int argument_parser(char* input, char **args) {
    int i = 0;
    char *p = input;
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (*p != '\0' && i < MAX_ARGS - 1) {
        // 공백 건너뛰기
        while (isspace((unsigned char)*p)) p++;

        if (*p == '\0') break;

        char arg_buffer[4096]; // 충분한 크기의 버퍼
        char *arg_end = arg_buffer;

        while (*p != '\0') {
            if (in_single_quote) {
                if (*p == '\'') {
                    in_single_quote = 0;
                    p++;
                } else {
                    *arg_end++ = *p++;
                }
            } else if (in_double_quote) {
                if (*p == '"') {
                    in_double_quote = 0;
                    p++;
                } else {
                    *arg_end++ = *p++;
                }
            } else {
                if (*p == '\'') {
                    in_single_quote = 1;
                    p++;
                } else if (*p == '"') {
                    in_double_quote = 1;
                    p++;
                } else if (isspace((unsigned char)*p)) {
                    p++;
                    break;
                } else {
                    *arg_end++ = *p++;
                }
            }
        }

        *arg_end = '\0';

        // environment expanding - working on plain $VAR or ${VAR}, env inside of quote
        char expanded_arg[4096];
        if (!in_single_quote) {
            expand_environment_variables(arg_buffer, expanded_arg, sizeof(expanded_arg));
        } else {
            strcpy(expanded_arg, arg_buffer);
        }

        // 동적 메모리 할당하여 인자 저장
        args[i] = strdup(expanded_arg);
        if (args[i] == NULL) {
            perror("메모리 할당 실패");
            return -1;
        }
        i++;
    }

    args[i] = NULL;
    return i;
}