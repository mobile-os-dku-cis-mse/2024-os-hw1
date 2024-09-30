#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int counter( char *str ) {
    int cnt = 0;
    const char *temp = str;
    
    while (*temp) {
        if (*temp == ' ') {
            cnt++;
        }
        temp++;
    }
    return cnt + 1;
}


int main() {

    int getlineResult = 0, stauts = 0, cnt = 0, ret = 0;
    char *input = NULL, *env = NULL, *copyEnv = NULL, **cmd = NULL;
    char *saveptr = NULL, *token = NULL, *path = NULL;
    char *user = NULL, *pwd = NULL;
    char cwd[PATH_MAX];
    size_t len = 0;
    pid_t pid;
    

    while (1) {

        user = getenv("USER");
        pwd = getenv("PWD");
        printf("%s:%s SiSH> ", user, pwd );

        getlineResult=getline(&input, &len, stdin);

        if ( getlineResult == -1 ) {
            perror("Error reading from getline\n");        
            break;
        }

        input = strtok(input, "\n");

        if ( input == NULL || strcmp(input, "") == 0 ) {
            continue;
        }

        cnt = counter(input);
        cmd = (char**)malloc(sizeof(char*) * (cnt + 1));
        token = strtok_r(input, " ", &saveptr);

        for (int i = 0; i<cnt; i++) {
            cmd[i] = token;
            token  = strtok_r(NULL, " ", &saveptr);
        }
        cmd[cnt] = NULL;

        if ( strcmp(cmd[0], "quit") == 0 ) {
            printf("Exiting SiSH\n");
            break;
        }
        else if( !strcmp(cmd[0], "cd") ) {
            
            if ( cmd[1] == NULL ) { //home
                ret = chdir( getenv("HOME") );
            }
            else if ( strcmp(cmd[1], "..") == 0 ) { //upper directory
                int i = strlen(pwd) - 1;
                while ( pwd[i] != '/' ) {
                    i--;
                }
                path = (char*)malloc(sizeof(char)*(i+1));
                strncpy( path,pwd,i );
                ret = chdir( path );
            }
            else if ( strcmp(cmd[1], ".") == 0 ) { //current directory
                ret = chdir( cwd );
            }
            else if ( strcmp(cmd[1], "/") == 0 ){ //최상위 디렉토리
                ret = chdir( "/" );
            }
            else { //specific directory
                ret = chdir( cmd[1] );
            }


            if ( ret == -1 ) {
                perror("chdir error");
            }
            else {
            // 현재 작업 디렉토리 업데이트
                if ( getcwd( cwd, sizeof(cwd) ) == NULL ) {
                    perror("getcwd error");
                }
                else {
                    setenv("PWD", cwd, 1);
                }
             }

            free(cmd);
            continue;
        }
        else if ( strcmp(cmd[0], "pwd") == 0 ) {
            printf("%s\n", cwd);
            free(cmd);
            continue;
        }
        else if ( strcmp(cmd[0], "echo") == 0 ) {
            for (int i = 1; i<cnt; i++) {
                printf("%s ", cmd[i]);
            }
            printf("\n");
            free(cmd);
            continue;
        }
        

        //make new process
        pid = fork();

        if( pid == -1 ) {
            perror("fork error");
            free(cmd);
            return 0 ;
        }
        else if ( pid == 0 ) {
            //child
            //환경변수인지 확인
            env = getenv( "PATH" );
            copyEnv = strdup(env);

            token = strtok_r( copyEnv, ":", &saveptr );
            while (token != NULL) {

                //full file path
                path = ( char* )malloc( strlen(token) + strlen(cmd[0]) + 2 );
                strcpy(path, token);
                path[strlen(token)] = '/';
                strcat(path, cmd[0]);

                    //check file
                if ( access(path, X_OK) == 0 ) {
                        //file excution
                    execve(path, cmd, NULL);
                    break;
                }
                    
                token = strtok_r( NULL, ":", &saveptr );
            }                
            
            
            free(path);
            free(copyEnv);            
            exit(0);
        }
        else {
            //parent
            waitpid(pid, &stauts, 0);
            free(cmd);
            cmd = NULL;
        }
    }

    free(input);    
    return 0;
}