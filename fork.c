#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	// 프로세스 ID
	pid_t pid;
	int i;

	for (i = 0 ; i < 10 ; i++) {
		// 새로운 자식 프로세스를 생성
		pid = fork();
		printf("\n!!! : %d\n", pid);
		if (pid == -1) {
			// 호출이 실패
			perror("fork error");
			return 0;
		} else if (pid == 0) {
			// child
			printf("child process with pid %d (i: %d) \n", getpid(), i);
			exit(0);
		} else {
			// parent
			printf("parent process with pid %d (i: %d)... wait for child \n", getpid(), i);
			wait(0);
		}
	}
	return 0;
}

/*
자식 프로세스:
각 자식 프로세스는 자신이 생성된 반복 인덱스와 프로세스 ID를 출력합니다.
출력을 마친 후, exit(0) 호출로 정상 종료합니다.

부모 프로세스:
각 자식 프로세스가 종료될 때까지 wait(0) 호출로 대기합니다.
자식 프로세스가 종료될 때까지 기다리므로, 부모 프로세스는 자식 프로세스가 완전히 종료된 후에야 다음 반복으로 넘어갑니다.


C 언어를 사용하여 리눅스 환경에서 프로세스를 생성하고, 자식 프로세스를 생성하는 기본적인 예제
실행 실패 시 -1, 부모에게는 새로운 PID, 자식에게는 0 반환
*/
