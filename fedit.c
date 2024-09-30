#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_PATH 1024
#define BUFFER_SIZE 1024

const char *protected_files[] = {"fedit.c", "explore.c", "sish.c", "devproc.c"};

int is_protected_file(const char *filename) {
    for (int i = 0; i < sizeof(protected_files) / sizeof(protected_files[0]); i++) {
        if (strcmp(filename, protected_files[i]) == 0) {
            return 1; // Protected file
        }
    }
    return 0;
}

void memo_command(const char *message) {
    printf("%s\n", message);  // 메시지를 화면에 출력
}

void edit_file(const char *filename) {
    if (is_protected_file(filename)) {
        printf("Error: Editing %s is not allowed.\n", filename);
        return;
    }

    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error: Could not open file %s for editing.\n", filename);
        return;
    }

    char buffer[BUFFER_SIZE];
    printf("Current content of %s:\n", filename);
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    printf("\nEnter new content for %s (Ctrl+D to save):\n", filename);
    rewind(file);  // 파일 처음으로 돌아가기
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        fputs(buffer, file);
    }

    fclose(file);
}

void make_file(const char *filename, const char *content) {
    if (is_protected_file(filename)) {
        printf("Error: Creating %s is not allowed.\n", filename);
        return;
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create file %s.\n", filename);
        return;
    }

    if (content != NULL) {
        fprintf(file, "%s", content);
    }

    fclose(file);
    printf("File created: %s\n", filename);
}

void make_directory(const char *dirname) {
    if (mkdir(dirname, 0755) == -1) {
        printf("Error: Could not create directory %s.\n", dirname);
    } else {
        printf("Directory created: %s\n", dirname);
    }
}

void remove_file(const char *filename) {
    if (is_protected_file(filename)) {
        printf("Error: Deleting %s is not allowed.\n", filename);
        return;
    }

    if (unlink(filename) == -1) {
        printf("Error: Could not remove file %s.\n", filename);
    } else {
        printf("File removed: %s\n", filename);
    }
}

void remove_directory(const char *dirname) {
    char current_dir[MAX_PATH];
    getcwd(current_dir, sizeof(current_dir));

    // Check if trying to delete the current directory
    if (strcmp(current_dir, dirname) == 0) {
        printf("Error: Deleting the current directory is not allowed.\n");
        return;
    }

    if (rmdir(dirname) == -1) {
        printf("Error: Could not remove directory %s.\n", dirname);
    } else {
        printf("Directory removed: %s\n", dirname);
    }
}

void append_to_file(const char *filename, const char *content) {
    if (is_protected_file(filename)) {
        printf("Error: Modifying %s is not allowed.\n", filename);
        return;
    }

    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error: Could not open file %s for appending.\n", filename);
        return;
    }

    if (content != NULL) {
        fprintf(file, "%s", content);
    }

    fclose(file);
    printf("Content appended to file: %s\n", filename);
}

void display_help() {
    printf("Fedit Command Help:\n");
    printf("  fedit -e filename         : Edit an existing file\n");
    printf("  fedit -m filename [content] : Create a new file with optional content\n");
    printf("  fedit -md dirname         : Create a new directory\n");
    printf("  fedit -rm filename        : Remove a file\n");
    printf("  fedit -rmdir dirname      : Remove a directory\n");
    printf("  fedit -a filename [content] : Append content to a file\n");
    printf("  memo \"message\"          : Display a message to the screen\n");
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Invalid usage. Use 'fedit -h' for help.\n");
        return 1;
    }

    // 명령어 처리
    if (strcmp(argv[1], "memo") == 0) {
        if (argc < 3) {
            printf("Usage: memo \"message\"\n");
        } else {
            memo_command(argv[2]);
        }
    } else if (strcmp(argv[1], "-e") == 0) {
        if (argc < 3) {
            printf("Usage: fedit -e filename\n");
        } else {
            edit_file(argv[2]);
        }
    } else if (strcmp(argv[1], "-m") == 0) {
        if (argc < 3) {
            printf("Usage: fedit -m filename [content]\n");
        } else {
            const char *content = (argc == 4) ? argv[3] : NULL;
            make_file(argv[2], content);
        }
    } else if (strcmp(argv[1], "-md") == 0) {
        if (argc < 3) {
            printf("Usage: fedit -md dirname\n");
        } else {
            make_directory(argv[2]);
        }
    } else if (strcmp(argv[1], "-rm") == 0) {
        if (argc < 3) {
            printf("Usage: fedit -rm filename\n");
        } else {
            remove_file(argv[2]);
        }
    } else if (strcmp(argv[1], "-rmdir") == 0) {
        if (argc < 3) {
            printf("Usage: fedit -rmdir dirname\n");
        } else {
            remove_directory(argv[2]);
        }
    } else if (strcmp(argv[1], "-a") == 0) {
        if (argc < 3) {
            printf("Usage: fedit -a filename [content]\n");
        } else {
            const char *content = (argc == 4) ? argv[3] : NULL;
            append_to_file(argv[2], content);
        }
    } else if (strcmp(argv[1], "-h") == 0) {
        display_help();
    } else {
        printf("Unknown option. Use 'fedit -h' for help.\n");
    }

    return 0;
}
