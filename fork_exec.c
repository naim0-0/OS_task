#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        printf("Child: PID = %d, Parent PID = %d\n", getpid(), getppid());
        fflush(stdout);
        execlp("whoami", "whoami", NULL);
        perror("execlp");
        exit(1);
    }

    printf("Parent: PID = %d, Child PID = %d\n", getpid(), pid);
    wait(NULL);
    printf("Parent: child finished\n");
    return 0;
}
