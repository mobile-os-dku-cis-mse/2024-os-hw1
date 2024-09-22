#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // 시그널 헤더파일
#include <unistd.h>

//ctrlc_handler() 함수: 시그널 처리 함수로, SIGINT 시그널이 발생하면 실행됩니다. 
//사용자가 ‘y’ 또는 ‘Y’ 를 입력하면 프로그램을 종료하고, 그 외의 경우에는 계속 실행됩니다.
void ctrlc_handler(int sig) {
   char c; // 사용자 입력받을 문자 선언
   printf("\nDo you really want to quit? [y/n]"); // 사용자 입력 묻는 프린트문
   c = getchar(); // 문자 입력받기
   if (c == 'y' || c == 'Y') { // c가 y혹은 Y이면 종료하기
       exit(0);
    } else {
     printf("Continuing…\n"); // 아니면 계속 진행되기
     }
 }

//sigusr1_handler() 함수: 시그널 처리 함수로, SIGUSR1 시그널이 발생하면 실행됩니다. 
//시그널이 발생하면 “Received SIGUSR1 signal.” 이 출력됩니다.
void sigusr1_handler(int sig) {
    printf("Received SIGUSR1 signal.\n");

}

int main() {

// SIGINT 시그널을 ctrlc_handler 함수로 핸들링 한다.
signal(SIGINT, ctrlc_handler);
// SIGUSR1 시그널을 sigusr1_handler 함수로 핸들링 한다.
signal(SIGUSR1, sigusr1_handler);

printf("Running… Press CTRL+C to quit.\n");

// 무한루프를 돌면서 1초마다 sleep 한다.

while (1) {
  sleep(1);
  }
return 0;
}