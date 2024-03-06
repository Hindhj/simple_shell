#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define ARG_SIZE 64

// Function to check if a file exists
int file_exists(const char *filename) {
    return access(filename, F_OK) != -1;
}

int main(void) {
    char buffer[BUFFER_SIZE];
    char *args[ARG_SIZE];
    int status;

    while (1) {
        printf(":) ");
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

        // Check if the command exists in PATH
        char *path_env = getenv("PATH");
        if (path_env != NULL) {
            char *path_copy = strdup(path_env);
            token = strtok(path_copy, ":");
            while (token != NULL) {
                // Construct full path to the command
                char full_path[BUFFER_SIZE];
                snprintf(full_path, BUFFER_SIZE, "%s/%s", token, args[0]);
                if (file_exists(full_path)) {
                    // Command found, execute it
                    args[0] = full_path;
                    break;
                }
                token = strtok(NULL, ":");
            }
            free(path_copy);
        }

        if (!file_exists(args[0])) {
            printf("Command not found: %s\n", args[0]);
            continue;
        }

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
