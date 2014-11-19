#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1000
#define MAX_NUM_ARGS 50

pid_t cid = 0;

void handler(int sig) {
  if(cid !=0) {
    kill(cid, sig);
  }
  printf("MyShell>");
}

int main(int argc, char *argv[]) {
    char line[MAX_LINE_LENGTH]; // stores entire input string
    char *a[MAX_NUM_ARGS]; // a is an array of strings aka an array of char arrays
    char *token;
    char *exec;
    char *temp;
    int val, i, status;


    int last_val = 0;


    signal(SIGINT, handler);

    while(1) {
        /* Wait for input */
        printf("MyShell>");
        fgets(line, MAX_LINE_LENGTH, stdin); 

        /* Parse input */
        i = 0;
        token = strtok(line, " \t\n");
	if(token!=NULL){

        /* Check if the given command is internal one */
        if (strncmp(token, "cd", 2) == 0) {
	  token = strtok(NULL, " \t\n");
            if(token!=NULL) {
                errno = 0;
                chdir(token);
                if(errno != 0) {
                    printf("%s: No such file or directory\n", token);
                }
            }
            else {
                chdir(getenv("HOME")); 
            }
        }

        else if (strncmp(token, "exit", 4) == 0) {
	  token = strtok(NULL, " \t\n");
            if(token!=NULL) {
                errno = 0;
                val = strtol(token, NULL, 10); 
                if(errno != 0) {
                    printf("Invalid exit value\n");
                }
                else{
                    exit(val);
                }
            }
            else {
                exit(last_val); // LAST VAL NEVER GETTING SET
            }
        }
        else {
            /* launch executable */
	     a[0] = token;
             i = 1;
             token = strtok(NULL, " \t\n");
             while(token != NULL) {
	       a[i] = token;
                 i++;
                 token = strtok(NULL, " \t\n");
             }
	     a[i]=NULL;
            // child process
            if ((cid = fork()) == 0) {
                execvp(a[0], a);
                printf("Command not recognized\n");
		exit(0);
            }
            // parent process
            else {
                wait(&status);
            }
        }
	}
        
    }
    return 0;
}
