#include <stdio.h>

#define MAX_READERS 20

int shared_data = 0;
int reader_count = 0;
int reading[MAX_READERS + 1] = {0};

void start_reading(int id) {
    if (id < 1 || id > MAX_READERS) {
        printf("Invalid reader number.\n");
        return;
    }

    if (reading[id]) {
        printf("Reader %d is already reading.\n", id);
        return;
    }

    reading[id] = 1;
    reader_count++;
    printf("Reader %d starts reading %d (%d active readers).\n",
           id, shared_data, reader_count);
}

void stop_reading(int id) {
    if (id < 1 || id > MAX_READERS || !reading[id]) {
        printf("Reader %d is not currently reading.\n", id);
        return;
    }

    reading[id] = 0;
    reader_count--;
    printf("Reader %d stops reading (%d active readers).\n",
           id, reader_count);
}

void write_data(int id, int value) {
    if (reader_count > 0) {
        printf("Writer %d is BLOCKED because readers are active.\n", id);
        return;
    }

    shared_data = value;
    printf("Writer %d writes %d.\n", id, shared_data);
}

int main(void) {
    int events, choice, id, value;

    printf("1 = start reading, 2 = stop reading, 3 = write\n");
    printf("Enter number of events: ");
    scanf("%d", &events);

    for (int i = 0; i < events; i++) {
        scanf("%d %d", &choice, &id);

        if (choice == 1) {
            start_reading(id);
        } else if (choice == 2) {
            stop_reading(id);
        } else if (choice == 3) {
            scanf("%d", &value);
            write_data(id, value);
        } else {
            printf("Invalid event.\n");
        }
    }

    printf("Final value = %d\n", shared_data);
    return 0;
}
