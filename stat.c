#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main(int argc, char * argv[])
{
	struct stat fstat_buf;
	int i;
	int ret;
	if (argc == 1) {
		printf("usage: stat file_path ... \n");
		printf("example: \"./a.out /home/adrd/test/test1.c\"\n");
		return 0;
	} else {
		for (i = 0 ; i < argc-1 ; i++) {
			ret = stat(argv[i+1], &fstat_buf);
			if (ret == -1) {
				perror("stat");
			} else {
                // 파일 정보 출력
                printf("File: %s\n", argv[i + 1]);
                printf("Size: %lld bytes\n", (long long)fstat_buf.st_size);
                printf("Blocks: %lld\n", (long long)fstat_buf.st_blocks);
                printf("IO Block: %ld\n", (long)fstat_buf.st_blksize);
                printf("File Type: ");
                switch (fstat_buf.st_mode & S_IFMT) {
                    case S_IFREG:  printf("Regular file\n"); break;
                    case S_IFDIR:  printf("Directory\n"); break;
                    case S_IFCHR:  printf("Character device\n"); break;
                    case S_IFBLK:  printf("Block device\n"); break;
                    case S_IFLNK:  printf("Symbolic link\n"); break;
                    case S_IFIFO:  printf("FIFO/pipe\n"); break;
                    case S_IFSOCK: printf("Socket\n"); break;
                    default:       printf("Unknown type\n"); break;
                }
                printf("Last accessed: %s", ctime(&fstat_buf.st_atime));
                printf("Last modified: %s", ctime(&fstat_buf.st_mtime));
                printf("Last status change: %s", ctime(&fstat_buf.st_ctime));
                printf("\n");
			}
		}
	}
	return 0;
}

/*
파일을 명령어 인자로 받아 파일의 구체적인 상태를 출력하는 프로그램
*/