#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    char buffer[100];
    const char *message = "Hello from the parent through a pipe!";

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        close(fd[1]);
        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n < 0) {
            perror("read");
            exit(1);
        }
        buffer[n] = '\0';
        close(fd[0]);
        printf("Child received: %s\n", buffer);
        exit(0);
    }

    close(fd[0]);
    write(fd[1], message, strlen(message));
    close(fd[1]);
    wait(NULL);
    printf("Parent: child finished\n");
    return 0;
}
