#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

// Custom getline function
char *custom_getline(void) {
    static char buffer[BUFFER_SIZE];
    static int position = 0;
    static int bytes_read = 0;

    char *line = NULL;
    int line_length = 0;
    int c;

    while (1) {
        // If buffer is empty, read more data
        if (position >= bytes_read) {
            position = 0;
            bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            if (bytes_read <= 0) {
                return NULL; // EOF or error
            }
        }

        // Read one character from buffer
        c = buffer[position++];
        
        // If end of line or end of buffer, terminate the line
        if (c == '\n' || c == '\0') {
            break;
        }

        // Append character to line
        if (line_length + 1 >= line_length) {
            line_length += BUFFER_SIZE;
            line = realloc(line, line_length);
            if (!line) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        line[line_length - 1] = c;
    }

    // Null-terminate the line
    if (line) {
        line[line_length] = '\0';
    }

    return line;
}

int main(void) {
    char *line;
    char *args[2];
    int status;

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);

        line = custom_getline();
        if (!line) {
            printf("\n");
            break; // Exit on EOF
        }

        args[0] = line;
        args[1] = NULL;

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child proces
