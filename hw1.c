#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>

int printShell();
int getFileState();
int getEnvVar(char newenv[10]);
int tokenize(char* command);
int tokenizePath();
int execute(char *argv[]);

char* str[40];
char store_path[70][70];
char* basic[100];
int str_num, num_path;
char command[256];
char* findpath;
typedef struct tm time_str;

int main(int argc, char *argv[]){
	num_path = 0;
	memset(store_path, 0, sizeof(store_path));
	tokenizePath();

	while(1){
		memset(str, 0, sizeof(str));
		str_num = 0;
		printShell();
		fgets(command, sizeof(command), stdin);
		command[strlen(command) - 1] = '\0';

		if((strcmp(command, "quit")==0)) break;

		if(tokenize(command)==0){
			if(str[0][0]=='$')
				getEnvVar(str[0]+1);

			else if(strcmp(str[0], "echo")==0){
				getFileState();
				for(int a=1; ; a++){
                    if(str[a]==NULL) break;

					if(str[a][0]=='$'){
						char* env;
						env = getenv(str[a]+1);
						printf("%s", env);
					}
					else{
						printf("%s", str[a]);
					}
					printf(" ");
				}
				printf("\n");
			}
			else{
				int find = getFileState();
				if(find==0)
					execute(str);

				else if(find==-1)
					printf("Program not found\n");

			}
		}
	}
	return 0;
}

int execute(char* argv[]){
	pid_t pid = fork();

	if(pid==-1){
		perror("fork error");
		exit(0);
	}
	else if(pid==0){
		if(execve(findpath, argv, NULL)==-1)
			printf("execve error\n");

        free(findpath);
		exit(0);
	}
	else
		wait(NULL);

	return 0;
}

int tokenizePath(){
	char *saveptr, *str_var;
	char save_path[200];
	int j;
	char* basic_path;

	basic_path = getenv("PATH");
	strcpy(save_path, basic_path);

	for(j=0, str_var=save_path; ; str_var=NULL, j++){
		basic[j] = strtok_r(str_var, ":", &saveptr);
		if (basic[j] == NULL) break;
		strcpy(store_path[j], basic[j]);
		num_path++;
	}
	num_path--;
	return 0;
}

int printShell(){
	char prompt[80];
	getcwd(prompt, 80);
	printf("SiSH %s $ ", prompt);
	return 0;
}

int tokenize(char* command){
	char *next, *token_str;
	str_num = 0;

	while(1){
		str[str_num] = strtok_r(command, " ", &next);
		if(str[0]==NULL)
			return 1;

		if(str[str_num]==NULL) break;

		command = NULL;
		str_num++;
	}
	return 0;
}

int getEnvVar(char newenv[10]){
	char *env;
	env = (char*)malloc(sizeof(char)*200);

	if(strcmp(str[0]+1, "TIME")==0){
		time_t today_time;
		time_str* today;
		time(&today_time);
		today = localtime(&today_time);
		printf("[TIME] %d:%d:%d \n", today->tm_hour, today->tm_min, today->tm_sec);
	}
	else{
		if(strcmp(str[0], "echo")==0)
			strcpy(env, str[1]+1);

		env = getenv(newenv);
		printf("%s=%s\n", newenv, env);
	}
	return -1;
}

int getFileState(){
	struct stat fstat_buf;
	int i = 0;
	while(1){
		if(basic[i]==NULL) break;

		if(strcmp(str[0], "cd")==0){
			char cwd[100];
			getcwd(cwd, sizeof(cwd));
			chdir(str[1]);
			getcwd(cwd, sizeof(cwd));
			return 2;
		}
		char newpath[20];
		findpath = (char*)malloc(sizeof(int)*100);

		if(stat(str[0], &fstat_buf)==0){
			strcpy(findpath, str[0]);
			return 0;
		}
		strcpy(newpath, store_path[i]);
		strcat(newpath, "/");
		strcat(newpath, str[0]);
		i++;

		if(stat(newpath, &fstat_buf)==0){
			strcpy(findpath, newpath);
			return 0;
		}
		if(i==num_path){
			printf("No file\n");
			return -1;
		}
	}
	return 0;
}

