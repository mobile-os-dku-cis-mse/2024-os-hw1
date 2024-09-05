#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include "../src/shell.h"

static char *capture_stdout(void (*func)(void)) {
    int pipefd[2];
    pid_t pid;
    char *output = NULL;
    ssize_t nread;
    size_t size = 0;
    char buffer[1024];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return NULL;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return NULL;
    }

    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        func();

        _exit(EXIT_SUCCESS);
    } else {
        close(pipefd[1]);
        FILE *fp = fdopen(pipefd[0], "r");
        if (fp == NULL) {
            perror("fdopen");
            return NULL;
        }

        output = malloc(1);
        if (output == NULL) {
            perror("malloc");
            fclose(fp);
            return NULL;
        }
        output[0] = '\0';

        while ((nread = fread(buffer, 1, sizeof(buffer) - 1, fp)) > 0) {
            buffer[nread] = '\0';
            size_t new_size = size + nread;
            char *new_output = realloc(output, new_size + 1);
            if (new_output == NULL) {
                perror("realloc");
                free(output);
                fclose(fp);
                return NULL;
            }
            output = new_output;
            strcat(output, buffer);
            size = new_size;
        }

        fclose(fp);
        wait(NULL);
        return output;
    }
}

static void trim_newline(char *str) {
    if (str == NULL) return;

    char *end = str + strlen(str) - 1;
    while (end > str && (*end == '\n' || *end == '\r')) {
        *end-- = '\0';
    }
}


void ck_assert_str_contains(const char *str, const char *substr) {
    if (str == NULL || substr == NULL) {
        ck_abort_msg("String or substring is NULL.");
    }
    if (strstr(str, substr) == NULL) {
        ck_abort_msg("String does not contain the expected substring: '%s'", substr);
    }
}


START_TEST(test_getenv_invalid) {
    void test_func(void) {
        char input[] = "getenv INVALID_VAR";
        process_command(input);
    }

    char *output = capture_stdout(test_func);
    ck_assert_msg(output != NULL, "Failed to capture stdout");
    trim_newline(output);
    ck_assert_str_eq(output, "Environment variable not found.");

    free(output);
}
END_TEST

START_TEST(test_echo_command) {
    void test_func(void) {
        char input[] = "echo test";
        process_command(input);
    }

    char *output = capture_stdout(test_func);
    ck_assert_msg(output != NULL, "Failed to capture stdout");
    trim_newline(output);
    ck_assert_str_eq(output, "test");

    free(output);
}
END_TEST

START_TEST(test_quit_command) {
    void test_func(void) {
        char input[] = "quit";
        process_command(input);
    }

    char *output = capture_stdout(test_func);
    ck_assert_msg(output != NULL, "Failed to capture stdout");

    trim_newline(output);
    ck_assert_str_eq(output, "Exiting shell.");

    free(output);
}
END_TEST

START_TEST(test_getenv_path) {
    void test_func(void) {
        char input[] = "getenv PATH";
        process_command(input);
    }

    char *output = capture_stdout(test_func);
    ck_assert_msg(output != NULL, "Failed to capture stdout");
    trim_newline(output);

    printf("Captured PATH: '%s'\n", output);
    fflush(stdout);

    ck_assert_str_contains(output, "/usr/local/sbin");

    free(output);
}
END_TEST

Suite *shell_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Shell");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_getenv_invalid);
    tcase_add_test(tc_core, test_echo_command);
    tcase_add_test(tc_core, test_quit_command);
    tcase_add_test(tc_core, test_getenv_path);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = shell_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
