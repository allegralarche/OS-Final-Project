#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_NUM_ARGS 50

void handler(int sig) {
    // terminate process
    //new line
}

int main(int argc, char *argv[]) {
    char line[MAX_LINE_LENGTH]; // stores entire input string
    char *tmpstr; // temp copy of input string
    char *a[MAX_NUM_ARGS]; // stores tokens of input string
    int i; // index
    char *token;


    signal(SIGINT, handler);

    while(1) {
        /* Wait for input */
        printf("MyShell>");
        fgets(line, MAX_LINE_LENGTH, stdin); // check return value--could be null if user just pressed enter

        /* Parse input */
        tmpstr = strdup(line); // might need to malloc--check documentation
        i = 0;
        token = strtok(tmpstr, " \t");
        while (token != NULL && i < MAX_NUM_ARGS) {
            a[i] = token; 
            i++;
            token = strtok(NULL, " \t");
        }

        /* Check if the given command is internal one */
        if (strcmp(a[0], "cd") == 0) {
            if(a[1]) {
                chdir(a[1]);
            }
            else {
                chdir(getenv("HOME")); // check this
            }
        }

        else if (strcmp(a[0], "exit") == 0) {
            exit (...);
        }

        /* check if executable exists and is executable */

        /* launch executable */
        if (fork() == 0) {
            execvp(a[0], a[1]);
        }
        else {
            wait(...);
        }
    }
    return 0;
}