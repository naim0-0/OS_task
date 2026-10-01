#include <stdio.h>

#define N 5

int main(void) {
    /* Hardcoded wake-up order. */
    int events[] = {0, 1, 2, 3, 4};
    int event_count = sizeof(events) / sizeof(events[0]);
    int room = N - 1;
    int chopstick[N] = {1, 1, 1, 1, 1};

    for (int e = 0; e < event_count; e++) {
        int id = events[e];
        int left = id;
        int right = (id + 1) % N;

        if (room == 0) {
            printf("Philosopher %d is BLOCKED (Room Full).\n", id);
            continue;
        }
        room--;

        if (chopstick[left] == 0) {
            printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", id);
            continue;
        }
        chopstick[left]--;

        if (chopstick[right] == 0) {
            printf("Philosopher %d is BLOCKED (Waiting for Chopstick).\n", id);
            continue;
        }
        chopstick[right]--;
        printf("Philosopher %d is EATING.\n", id);
    }

    return 0;
}
