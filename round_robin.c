#include <stdio.h>

#define MAX 20
#define QUEUE_SIZE 10000

int main(void) {
    /* Hardcoded process data and time quantum. */
    int at[] = {0, 1, 2, 3};
    int bt[] = {5, 3, 1, 2};
    int n = sizeof(at) / sizeof(at[0]);
    int quantum = 2;
    int remaining[MAX], ct[MAX] = {0};
    int tat[MAX], wt[MAX], added[MAX] = {0};
    int queue[QUEUE_SIZE], front = 0, rear = 0;
    int sequence[QUEUE_SIZE];
    int completion_order[MAX], sequence_count = 0;
    int time = 0, completed = 0;
    double total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        remaining[i] = bt[i];
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (!added[i] && at[i] <= time) {
                queue[rear++] = i;
                added[i] = 1;
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        int current = queue[front++];
        int run = remaining[current] < quantum
                      ? remaining[current] : quantum;

        sequence[sequence_count] = current;
        remaining[current] -= run;
        time += run;
        sequence_count++;

        /* Add processes that arrived while this process was running. */
        for (int i = 0; i < n; i++) {
            if (!added[i] && at[i] <= time) {
                queue[rear++] = i;
                added[i] = 1;
            }
        }

        if (remaining[current] > 0) {
            queue[rear++] = current;
        } else {
            ct[current] = time;
            completion_order[completed] = current;
            completed++;
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nExecution sequence: ");
    for (int i = 0; i < sequence_count; i++) {
        printf("P%d%s", sequence[i] + 1,
               i == sequence_count - 1 ? "\n" : " -> ");
    }
    printf("\nCompletion order: ");
    for (int i = 0; i < n; i++) {
        printf("P%d%s", completion_order[i] + 1, i == n - 1 ? "\n" : " -> ");
    }

    printf("Average waiting time = %.2f\n", total_wt / n);
    printf("Average turnaround time = %.2f\n", total_tat / n);
    return 0;
}
