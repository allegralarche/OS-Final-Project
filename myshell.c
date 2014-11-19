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
    char *a[MAX_NUM_ARGS]; // a is an array of strings aka an array of char arrays
    char *token;
    int val, i;


    int last_val = 0;


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
            a[i] = malloc(strlen(token)+1); 
            i++;
            token = strtok(NULL, " \t");
        }

        /* Check if the given command is internal one */
        if (strcmp(a[0], "cd") == 0) {
            if(a[1]) {
                errno = 0;
                chdir(a[1]);
                if(errno != 0) {
                    printf("%s is not a valid directory\n", a[1]); //check pointer
                }
            }
            else {
                chdir(getenv("HOME")); // check this
            }
        }

        else if (strcmp(a[0], "exit") == 0) {
            if(a[1]) {
                errno = 0;
                val = strtol(a[1], NULL, 10); // val might need to be long int
                if(errno != 0) {
                    printf("Invalid exit value\n");
                }
                else{
                    exit(val);
                }
            }
            else {
                exit(last_val);
            }
        }

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