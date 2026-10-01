#include <stdio.h>

#define MAX 20
#define MAX_SEQUENCE 10000

int main(void) {
    /* Hardcoded process data. */
    int at[] = {0, 1, 2, 3};
    int bt[] = {5, 3, 1, 2};
    int n = sizeof(at) / sizeof(at[0]);
    int remaining[MAX], ct[MAX] = {0};
    int tat[MAX], wt[MAX], time = 0, completed = 0;
    int sequence[MAX_SEQUENCE];
    int completion_order[MAX], sequence_count = 0;
    double total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        remaining[i] = bt[i];
    }

    while (completed < n) {
        int shortest = -1;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && remaining[i] > 0 &&
                (shortest == -1 || remaining[i] < remaining[shortest])) {
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        if (sequence_count == 0 || sequence[sequence_count - 1] != shortest) {
            sequence[sequence_count] = shortest;
            sequence_count++;
        }
        remaining[shortest]--;
        time++;

        if (remaining[shortest] == 0) {
            ct[shortest] = time;
            completion_order[completed] = shortest;
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
