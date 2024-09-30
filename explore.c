#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void search_file(const char *filename, const char *path);
void filter_by_extension(const char *extension, const char *path);
void output_file_content(const char *filename);
void display_directory_tree(const char *path, int depth);
void display_help();

#define MAX_PATH 1024       // 최대 경로 길이


// 1. explore -s 파일이름 PATH: 파일 탐색
void search_file(const char *filename, const char *path) {
    DIR *dir;
    struct dirent *entry;
    char full_path[MAX_PATH];

    if (path == NULL) path = "."; // 기본값으로 현재 디렉토리 사용

    if ((dir = opendir(path)) == NULL) {
        perror("opendir failed");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (strcmp(entry->d_name, filename) == 0) {
            printf("File found: %s\n", full_path);
            closedir(dir);
            return;
        }
    }

    printf("File not found: %s\n", filename);
    closedir(dir);
}

// 2. explore -t 확장자 PATH: 확장자 필터링
void filter_by_extension(const char *extension, const char *path) {
    DIR *dir;
    struct dirent *entry;

    if (path == NULL) path = "."; // 기본값으로 현재 디렉토리 사용

    if ((dir = opendir(path)) == NULL) {
        perror("opendir failed");
        return;
    }

    printf("File: ");
    int i = 0;
    while ((entry = readdir(dir)) != NULL) {
        char *ext = strrchr(entry->d_name, '.');
        if (ext && strcmp(ext, extension) == 0) {
            if(i%4 == 0){
                printf("\n");
            }
            printf("%s\t", entry->d_name);
        }
    }

    closedir(dir);
}

// 3. explore -o 파일이름: 파일 내용 출력
void output_file_content(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[256];

    if (file == NULL) {
        perror("File cannot be opened or does not exist");
        return;
    }

    // 파일이 텍스트 파일인지 확인
    struct stat file_stat;
    if (stat(filename, &file_stat) != 0 || !S_ISREG(file_stat.st_mode)) {
        printf("The file cannot be output: %s\n", filename);
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
}

// 4. explore -sh PATH: 트리 구조로 디렉토리 출력
void display_directory_tree(const char *path, int depth) {
    DIR *dir;
    struct dirent *entry;
    char new_path[MAX_PATH];

    if (path == NULL) path = "."; // 기본값으로 현재 디렉토리 사용

    if ((dir = opendir(path)) == NULL) {
        perror("opendir failed");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        for (int i = 0; i < depth; i++) printf("  ");
        printf("|-- %s\n", entry->d_name);

        snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
        struct stat entry_stat;
        stat(new_path, &entry_stat);

        if (S_ISDIR(entry_stat.st_mode)) {
            display_directory_tree(new_path, depth + 1);  // 재귀적으로 디렉토리 탐색
        }
    }

    closedir(dir);
}

// 5. explore -h: 도움말 출력
void display_help() {
    printf("Explore Command Help:\n");
    printf("  explore -s filename [path]  :    Search for a file in the specified path (default: current path)\n");
    printf("  explore -t extension [path] :    Search for files with the specified extension in the path\n");
    printf("  explore -o filename         :    Output the contents of a file\n");
    printf("  explore -sh [path]          :    Display directory structure as a tree (default: current path)\n");
    printf("  explore -h                  :    Show help information\n");
}



int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Invalid usage. Use 'explore -h' for help.\n");
        return 1;
    }

    // 파일 검색 기능 (-s 옵션)
    if (strcmp(argv[1], "-s") == 0) {
        if (argc < 3) {
            printf("Usage: explore -s filename [path]\n");
        } else {
            search_file(argv[2], (argc == 4) ? argv[3] : NULL);
        }
    }
    // 확장자 필터링 (-t 옵션)
    else if (strcmp(argv[1], "-t") == 0) {
        if (argc < 3) {
            printf("Usage: explore -t extension [path]\n");
        } else {
            filter_by_extension(argv[2], (argc == 4) ? argv[3] : NULL);
        }
    }
    // 파일 내용 출력 (-o 옵션)
    else if (strcmp(argv[1], "-o") == 0) {
        if (argc < 3) {
            printf("Usage: explore -o filename\n");
        } else {
            output_file_content(argv[2]);
        }
    }
    // 디렉토리 트리 출력 (-sh 옵션)
    else if (strcmp(argv[1], "-sh") == 0) {
        display_directory_tree((argc == 3) ? argv[2] : NULL, 0);
    }
    // 도움말 출력 (-h 옵션)
    else if (strcmp(argv[1], "-h") == 0) {
        display_help();
    }
    // 잘못된 명령어 처리
    else {
        printf("Unknown option. Use 'explore -h' for help.\n");
    }

    printf("\n");

    return 0;
}
