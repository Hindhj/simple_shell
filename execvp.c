#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define ARG_SIZE 64

int main(void) {
    char buffer[BUFFER_SIZE];
    char *args[ARG_SIZE];
    int status;

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);

        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            printf("\n");
            break; // Exit on EOF (Ctrl+D)
        }

        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Tokenize the input line
        char *token = strtok(buffer, " ");
        int arg_count = 0;
        while (token != NULL && arg_count < ARG_SIZE - 1) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL;

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return EXIT_SUCCESS;
}
