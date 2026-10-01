#include <stdio.h>

#define N 5

int room = N - 1;
int chopstick[N] = {1, 1, 1, 1, 1};
int eating[N] = {0};

void take_fork(int id) {
    int left = id;
    int right = (id + 1) % N;

    if (id < 0 || id >= N) {
        printf("Invalid philosopher number %d. Use 0 to 4.\n", id);
        return;
    }

    if (eating[id]) {
        printf("Philosopher %d is already EATING.\n", id);
        return;
    }

    if (room == 0) {
        printf("Philosopher %d is BLOCKED (Room Full).\n", id);
        return;
    }

    if (chopstick[left] == 0 || chopstick[right] == 0) {
        printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", id);
        return;
    }

    room--;
    chopstick[left] = 0;
    chopstick[right] = 0;
    eating[id] = 1;
    printf("Philosopher %d is EATING.\n", id);
}

void put_fork(int id) {
    int left = id;
    int right = (id + 1) % N;

    if (!eating[id]) {
        return;
    }

    chopstick[left] = 1;
    chopstick[right] = 1;
    eating[id] = 0;
    room++;
    printf("Philosopher %d put down both chopsticks.\n", id);
}

int main(void) {
    int attempts, philosopher;

    printf("Enter number of attempts: ");
    scanf("%d", &attempts);

    printf("Enter philosopher numbers (0 to 4):\n");
    for (int i = 0; i < attempts; i++) {
        scanf("%d", &philosopher);
        take_fork(philosopher);
    }

    printf("\nReleasing chopsticks:\n");
    for (int i = 0; i < N; i++) {
        put_fork(i);
    }

    return 0;
}
