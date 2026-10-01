#include <stdio.h>

#define MAX 20

int main(void) {
    /* Hardcoded process data. Smaller number = higher priority. */
    int at[] =       {0, 1, 2, 3};
    int bt[] =       {5, 3, 1, 2};
    int priority[] = {2, 1, 3, 2};
    int n = sizeof(at) / sizeof(at[0]);
    int ct[MAX] = {0};
    int tat[MAX], wt[MAX], done[MAX] = {0};
    int sequence[MAX];
    int time = 0, completed = 0;
    double total_wt = 0, total_tat = 0;

    while (completed < n) {
        int best = -1;

        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time &&
                (best == -1 || priority[i] < priority[best])) {
                best = i;
            }
        }

        if (best == -1) {
            time++;
            continue;
        }

        sequence[completed] = best;
        time += bt[best];
        ct[best] = time;
        done[best] = 1;
        completed++;
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], priority[i], ct[i], tat[i], wt[i]);
    }

    printf("\nExecution sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d%s", sequence[i] + 1, i == n - 1 ? "\n" : " -> ");
    }
    printf("\nCompletion order: ");
    for (int i = 0; i < n; i++) {
        printf("P%d%s", sequence[i] + 1, i == n - 1 ? "\n" : " -> ");
    }

    printf("Average waiting time = %.2f\n", total_wt / n);
    printf("Average turnaround time = %.2f\n", total_tat / n);
    return 0;
}
