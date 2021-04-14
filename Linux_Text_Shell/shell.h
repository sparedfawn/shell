#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_PATH 1024
#define BUF_SIZE 128 

char*** get_arguments(int);
short int execute(char***);
char* get_line();