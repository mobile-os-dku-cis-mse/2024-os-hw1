



int main(int argc, char *argv[]){ 
	int c; 

	pid_t pid = getpid(); 
	printf("My pid: %d\n", pid); 
	
	c = fgetc(stdi); 
	exit(0); 

}
