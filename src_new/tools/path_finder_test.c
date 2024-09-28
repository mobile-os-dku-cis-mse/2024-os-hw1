#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <yaml.h>
#include <limits.h>
#include "path_finder.h"
//
// Created by hochacha on 24. 9. 28.
//
// 테스트 함수
void run_tests(const char* config_file) {
    FILE *fh = fopen(config_file, "r");
    if (!fh) {
        printf("Failed to open config file.\n");
        return;
    }

    yaml_parser_t parser;
    yaml_token_t token;
    yaml_parser_initialize(&parser);
    yaml_parser_set_input_file(&parser, fh);

    char description[256] = {0};
    char binary[256] = {0};
    int expected = 0;
    int unset_path = 0;
    int in_tests = 0, in_test_case = 0;

    while (1) {
        yaml_parser_scan(&parser, &token);
        if (token.type == YAML_STREAM_END_TOKEN) {
            break;
        }

        if (token.type == YAML_KEY_TOKEN) {
            yaml_parser_scan(&parser, &token);

            if (strcmp((char *)token.data.scalar.value, "tests") == 0) {
                in_tests = 1;
            }

            if (in_tests) {
                if (strcmp((char *)token.data.scalar.value, "description") == 0) {
                    yaml_parser_scan(&parser, &token);
                    strncpy(description, (char *)token.data.scalar.value, sizeof(description));
                } else if (strcmp((char *)token.data.scalar.value, "binary") == 0) {
                    yaml_parser_scan(&parser, &token);
                    strncpy(binary, (char *)token.data.scalar.value, sizeof(binary));
                } else if (strcmp((char *)token.data.scalar.value, "expected") == 0) {
                    yaml_parser_scan(&parser, &token);
                    expected = atoi((char *)token.data.scalar.value);
                } else if (strcmp((char *)token.data.scalar.value, "unset_path") == 0) {
                    yaml_parser_scan(&parser, &token);
                    unset_path = (strcmp((char *)token.data.scalar.value, "true") == 0);
                }
            }
        }

        if (token.type == YAML_BLOCK_END_TOKEN && in_tests) {
            in_test_case = 0;

            // 테스트 실행
            printf("%s\n", description);
            if (unset_path) {
                unsetenv("PATH");
            }

            int result = bin_path_finder(binary);

            if (result == expected) {
                printf("Test Passed\n");
            } else {
                printf("Test Failed\n");
            }

            if (unset_path) {
                // PATH 복원 필요시 처리
            }

            // 초기화
            memset(description, 0, sizeof(description));
            memset(binary, 0, sizeof(binary));
            expected = 0;
            unset_path = 0;
        }

        yaml_token_delete(&token);
    }

    yaml_parser_delete(&parser);
    fclose(fh);
}

int main() {
    // 테스트 실행
    run_tests("test_config.yaml");
    return 0;
}