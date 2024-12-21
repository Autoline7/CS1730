#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//main method that immitates the pipe (|) with the system call to pipe and using fork
int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid;
    int pipe_index = -1;

    // find the index of "-pipe"
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-pipe") == 0) {
            pipe_index = i;
        }
    }

    // check if there is a"-pipe"
    if (pipe_index == -1) {
        printf("Error: No -pipe found in command\n");
        return 0;//exit the program
    }

    // separate arguments for child and parent
    char *child_cmd[pipe_index + 1];
    for (int i = 1; i < pipe_index; i++) {
        child_cmd[i - 1] = argv[i];
    }
    child_cmd[pipe_index - 1] = NULL;  // null-terminate child command

    char *parent_cmd[argc - pipe_index];
    for (int i = pipe_index + 1; i < argc; i++) {
        parent_cmd[i - pipe_index - 1] = argv[i];
    }
    parent_cmd[argc - pipe_index - 1] = NULL;  // null-terminate parent command

    // create the pipe
    if (pipe(pipefd) == -1) {
        printf("Failed pipe");
        return 0;//exit the program 
    }

    // Fork the process
    pid = fork();
    if (pid == -1) {
        printf("Failed fork");
        return 0;//exit the program 
    }

    if (pid == 0) {
        // Child process: Runs the first command
      close(pipefd[0]);//close unused read end
        dup2(pipefd[1], STDOUT_FILENO);//redirect stdout to write end of pipe
        close(pipefd[1]);//close the original write end

        // execute the child commands
        execvp(child_cmd[0], child_cmd);
        printf("Failed execvp"); // if execvp fails
        return 0;//exit the program 
    } else {
        // Parent process: Runs the second command after waiting for the child
      close(pipefd[1]);//close unused write end
        dup2(pipefd[0], STDIN_FILENO);//redirect stdin to read end of pipe
        close(pipefd[0]);// close the original read end

        // wait for the child process to finish
        waitpid(pid, NULL, 0);

        // execute the parent commands
        execvp(parent_cmd[0], parent_cmd);
        perror("Failed execvp"); // if execvp fails
        return 0;//exit the program 
    }

    return 0;//returns 0 for the main class
}
