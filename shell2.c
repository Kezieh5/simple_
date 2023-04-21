#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt(const char* prompt) {
    write(STDOUT_FILENO, prompt, strlen(prompt));
    fsync(STDOUT_FILENO);
}
int main(int argc, char *argv[]) {
    while (1) {
        display_prompt("$ ");
        
        // Read the user's command from stdin
        char command[MAX_COMMAND_LENGTH];
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            // End of file condition (Ctrl+D)
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
 
        // Remove trailing newline character
        command[strcspn(command, "\n")] = '\0';

        // Parse the command and its arguments
        #define MAX_ARGS ((MAX_COMMAND_LENGTH / 2) + 1)
        char* argv[MAX_ARGS];
	int argc = 0;
        for (char *token = strtok(command, " "); token != NULL; token = strtok(NULL, " ")) 
	{
         argv[argc++] = token;
	}
        argv[argc] = NULL;


        // Fork a new process to execute the command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execvp(argv[0], argv);
            // If execvp returns, the command could not be executed
            perror(argv[0]);
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
                 const char* error_message = "Command '";
    write(STDERR_FILENO, error_message, strlen(error_message));
    write(STDERR_FILENO, command, strlen(command));
    const char* error_message_end = "' could not be executed.\n";
    write(STDERR_FILENO, error_message_end, strlen(error_message_end));
	    }
	}
    }
}

    return 0;
}
