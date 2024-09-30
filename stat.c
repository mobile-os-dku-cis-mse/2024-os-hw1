#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    struct stat fstat_buf;
    struct dirent *entry;
    DIR *dir;
    
    if (argc != 2) 
    {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    // 디렉토리 열기
    if ((dir = opendir(argv[1])) == NULL) 
    {
        perror("opendir");
        return 1;
    }

    // 디렉토리 내 파일 탐색
    while ((entry = readdir(dir)) != NULL) 
    {
        if (stat(entry->d_name, &fstat_buf) == -1) 
        {
            perror("stat");
            continue;
        }

        printf("File: %s, Size: %ld bytes, Permissions: %o\n", entry->d_name, fstat_buf.st_size, fstat_buf.st_mode & 0777);
    }

    closedir(dir);
    return 0;
}
