#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 200

void handle_arrows(char *buffer) {
    // 화살표 키 시퀀스 처리
    if (buffer[1] == '[') {
        switch (buffer[2]) {
            case 'A':
                printf("\nUp arrow key pressed\n");
                break;
            case 'B':
                printf("\nDown arrow key pressed\n");
                break;
            case 'C':
                printf("\nRight arrow key pressed\n");
                break;
            case 'D':
                printf("\nLeft arrow key pressed\n");
                break;
            default:
                printf("\nUnknown arrow key\n");
                break;
        }
    }
}

void read_command(char *command) {
    char now_path[200];
    getcwd(now_path, sizeof(now_path));
    printf("\033[90m~%s\033[0m$ ", now_path);

    int index = 0;
    char ch;
    while ((ch = getchar()) != '\n') {
        if (ch == 0x1b) { // ESC 문자 감지
            char buffer[3];
            buffer[0] = ch;
            read(STDIN_FILENO, buffer + 1, 2); // 나머지 두 바이트 읽기
            handle_arrows(buffer);
        } else {
            // 일반 문자 처리
            command[index++] = ch;
            putchar(ch); // 입력된 문자 출력 (에코)
        }
    }
    command[index] = '\0'; // 문자열 끝에 NULL 추가
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    while (1) {
        read_command(command);
        printf("\nCommand entered: %s\n", command);
    }
    return 0;
}
