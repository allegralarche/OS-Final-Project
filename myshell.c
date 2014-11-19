#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#define MAX_LINE_LENGTH 1000
#define MAX_NUM_ARGS 50

pid_t cid;

void handler(int sig) {
    kill(cid, sig);
    printf("\n");
}

int main(int argc, char *argv[]) {
    char line[MAX_LINE_LENGTH]; // stores entire input string
    char *a[MAX_NUM_ARGS]; // a is an array of strings aka an array of char arrays
    char *token;
    char *exec;
    int val, i, status;


    int last_val = 0;


    signal(SIGINT, handler);

    while(1) {
        /* Wait for input */
        printf("MyShell>");
        fgets(line, MAX_LINE_LENGTH, stdin); // check return value--could be null if user just pressed enter

        /* Parse input */
        i = 0;
        token = strtok(line, " \t");

        /* Check if the given command is internal one */
        if (strcmp(token, "cd") == 0) {
            token = strtok(NULL, " \t");
            if(token) {
                errno = 0;
                chdir(token);
                if(errno != 0) {
                    printf("\n%s: No such file or directory\n", token); //check pointer
                }
            }
            else {
                chdir(getenv("HOME")); 
                printf("\n");
            }
        }

        else if (strcmp(token, "exit") == 0) {
            token = strtok(NULL, " \t");
            if(token) {
                errno = 0;
                val = strtol(token, NULL, 10); // val might need to be long
                if(errno != 0) {
                    printf("\nInvalid exit value\n");
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
            // child process
            if ((cid = fork()) == 0) {
                a[0] = token;
                i = 1;
                token = strtok(NULL, " \t");
                while(token != NULL) {
                    a[i] = token;
                    i++;
                    token - strtok(NULL, " \t");
                }
                execvp(a[0], a);
                printf("\nCommand not recognized\n");
            }
            // parent process
            else {
                wait(&status);
            }
        }
        
    }
    return 0;
}