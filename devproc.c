#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

// 함수 선언
void create_project_directory(const char *project_name);
void create_subdirectories(const char *project_name);
void create_main_file(const char *project_name);
void compile_code(const char *filename);
void create_makefile(const char *filename);
void display_help();

// 1. 프로젝트 디렉토리 생성 함수 (fedit -md)
void create_project_directory(const char *project_name)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        char *args[] = {"fedit", "-md", (char *)project_name, NULL};
        execv("./fedit", args);
        perror("execv failed");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("Project directory %s created.\n", project_name);
    }
    else
    {
        perror("fork failed");
        exit(1);
    }
}

// 2. 서브디렉토리 생성 함수 (fedit -md)
void create_subdirectories(const char *project_name)
{
    char header_dir[256];
    char source_dir[256];

    snprintf(header_dir, sizeof(header_dir), "%s/header", project_name);
    snprintf(source_dir, sizeof(source_dir), "%s/source", project_name);

    // header 디렉토리 생성
    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        char *args[] = {"fedit", "-md", header_dir, NULL};
        execv("./fedit", args);
        perror("execv failed");
        exit(1);
    }
    else if (pid1 > 0)
    {
        wait(NULL);
        printf("Header directory created: %s\n", header_dir);
    }
    else
    {
        perror("fork failed");
        exit(1);
    }

    // source 디렉토리 생성
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        char *args[] = {"fedit", "-md", source_dir, NULL};
        execv("./fedit", args);
        perror("execv failed");
        exit(1);
    }
    else if (pid2 > 0)
    {
        wait(NULL);
        printf("Source directory created: %s\n", source_dir);
    }
    else
    {
        perror("fork failed");
        exit(1);
    }
}

// 3. main.c 파일 생성 및 내용 작성 함수 (fedit -m, fedit -e)
void create_main_file(const char *project_name)
{
    char main_file_path[256];
    snprintf(main_file_path, sizeof(main_file_path), "%s/source/main.c", project_name);

    // main.c 파일 생성
    pid_t pid = fork();
    if (pid == 0)
    {
        char *args[] = {"fedit", "-m", main_file_path, NULL};
        execv("./fedit", args);
        perror("execv failed");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("main.c file created: %s\n", main_file_path);
    }
    else
    {
        perror("fork failed");
        exit(1);
    }

    // main.c 파일 내용 작성
    pid = fork();
    if (pid == 0)
    {
        char *args[] = {"fedit", "-e", main_file_path, NULL};
        execv("./fedit", args);
        perror("execv failed");
        exit(1);
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("Content written to main.c in %s\n", main_file_path);
    }
    else
    {
        perror("fork failed");
        exit(1);
    }
}
// 4. 파일 컴파일 함수 (.o 파일 생성 및 실행)
void compile_and_run_code(const char *filename)
{
    char *exec_file = strdup(filename);      // filename 기반으로 실행 파일 이름 생성
    exec_file[strlen(exec_file) - 2] = '\0'; // .c 확장자 제거하여 실행 파일 이름 생성

    pid_t pid = fork();
    if (pid == 0)
    {
        // 자식 프로세스에서 gcc를 호출하여 컴파일 및 링크 수행
        // gcc filename.c -o filename
        char *gcc_args[] = {"gcc", (char *)filename, "-o", exec_file, NULL};
        execvp("user/bin/gcc", gcc_args); // execvp는 PATH에서 gcc를 찾음
        perror("execvp for gcc failed");
        exit(1);
    }
    else if (pid > 0)
{
    // 부모 프로세스: 자식 프로세스가 실행 파일을 생성할 때까지 대기
    wait(NULL);

    // 실행 파일 이름 앞에 ./을 추가
    size_t exec_file_len = strlen(exec_file);
    char *exec_file_with_path = malloc(exec_file_len + 3); // ./ + filename + null
    if (exec_file_with_path == NULL)
    {
        perror("malloc failed");
        exit(1);
    }

    // ./을 실행 파일 앞에 붙이기
    strcpy(exec_file_with_path, "./");
    strcat(exec_file_with_path, exec_file);

    // 컴파일 및 링크가 성공적으로 완료된 후 실행 파일 실행
    printf("Running the program: %s\n", exec_file_with_path);
    char *exec_args[] = {exec_file_with_path, NULL};
    execv(exec_file_with_path, exec_args); // 생성된 실행 파일을 실행
    perror("execv failed");
    free(exec_file_with_path); // 메모리 해제
    exit(1);
}

    else
    {
        perror("fork failed");
        exit(1);
    }
}

// 5. Makefile 생성 함수
void create_makefile(const char *filename)
{
    FILE *file = fopen("Makefile", "w");
    if (file == NULL)
    {
        perror("fopen failed");
        exit(1);
    }

    fprintf(file, "CC=gcc\n");
    fprintf(file, "CFLAGS=-Wall\n");
    fprintf(file, "TARGET=program\n\n");
    fprintf(file, "all: $(TARGET)\n\n");
    fprintf(file, "$(TARGET): %s\n", filename);
    fprintf(file, "\t$(CC) $(CFLAGS) -o $(TARGET) %s\n", filename);
    fprintf(file, "\nclean:\n");
    fprintf(file, "\trm -f $(TARGET)\n");

    fclose(file);
    printf("Makefile created for %s\n", filename);
}

// 6. Help 명령어 함수
void display_help()
{
    printf("Devproc Command Help:\n");
    printf("  devproc -c filename       : Compile the specified C file.\n");
    printf("  devproc -mf filename      : Generate a Makefile for the project.\n");
    printf("  devproc -t projectname    : Create a new project template with specified name.\n");
    printf("  devproc -h                : Display this help message.\n");
}

int main(int argc, char *argv[])
{
    if (argc < 3 && !(strcmp(argv[1], "-h") == 0))
    {
        printf("Usage:\n");
        printf("  devproc -t <project_name>\n");
        printf("  devproc -c <file.c>\n");
        printf("  devproc -mf <file.c>\n");
        return 1;
    }

    const char *project_name = argv[2];
    pid_t pid;
    int pipe_fd[2];

    // 명령어 처리
    if (strcmp(argv[1], "-t") == 0)
    {
        if (pipe(pipe_fd) == -1)
        {
            perror("pipe failed");
            exit(1);
        }

        // 1. 프로젝트 디렉토리 생성
        pid = fork();
        if (pid == 0)
        {
            close(pipe_fd[0]);
            create_project_directory(project_name);
            write(pipe_fd[1], "Directory created\n", 18);
            close(pipe_fd[1]);
            exit(0);
        }
        else if (pid > 0)
        {
            wait(NULL);
        }

        // 2. 서브 디렉토리 생성
        pid = fork();
        if (pid == 0)
        {
            sleep(1);
            close(pipe_fd[0]);
            create_subdirectories(project_name);
            write(pipe_fd[1], "Subdirectories created\n", 24);
            close(pipe_fd[1]);
            exit(0);
        }
        else if (pid > 0)
        {
            wait(NULL);
        }

        // 3. main.c 파일 생성
        pid = fork();
        if (pid == 0)
        {
            sleep(1);
            close(pipe_fd[0]);
            create_main_file(project_name);
            write(pipe_fd[1], "main.c file created\n", 20);
            close(pipe_fd[1]);
            exit(0);
        }
        else if (pid > 0)
        {
            wait(NULL);
        }

        // 부모 프로세스: 파이프에서 읽기
        close(pipe_fd[1]);
        char buffer[128];
        while (read(pipe_fd[0], buffer, sizeof(buffer)) > 0)
        {
            printf("%s", buffer);
        }
        close(pipe_fd[0]);
    }
    else if (strcmp(argv[1], "-c") == 0)
    {
        compile_and_run_code(argv[2]); // compile_code 대신 compile_and_run_code 사용
    }
    else if (strcmp(argv[1], "-mf") == 0)
    {
        create_makefile(argv[2]);
    }
    else if (strcmp(argv[1], "-h") == 0)
    {
        display_help();
    }
    else
    {
        printf("Unknown command. Use 'devproc -h' for help\n");
        return 1;
    }

    return 0;
}
