#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

volatile sig_atomic_t running = 1;

void handler(int signal_number) {
    (void)signal_number;
    const char message[] = "\nCaught Ctrl+C. Stopping...\n";
    write(STDOUT_FILENO, message, sizeof(message) - 1);
    running = 0;
}

void *worker(void *arg) {
    (void)arg;
    int count = 1;

    while (running) {
        printf("Worker is running: %d\n", count++);
        sleep(1);
    }
    printf("Worker stopped\n");
    return NULL;
}

int main(void) {
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);

    pthread_t thread;
    pthread_create(&thread, NULL, worker, NULL);

    printf("Press Ctrl+C to stop.\n");
    pthread_join(thread, NULL);
    printf("Main program finished.\n");
    return 0;
}
