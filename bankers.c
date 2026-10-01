#include <stdio.h>

#define MAX 10

int main(void) {
    
    int n = 5, m = 3;
    int max[MAX][MAX] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    int allocation[MAX][MAX] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    int available[MAX] = {3, 3, 2};
    int need[MAX][MAX], work[MAX], finished[MAX] = {0};
    int sequence[MAX], count = 0;
    for (int j = 0; j < m; j++) work[j] = available[j];

    printf("\nNeed matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    while (count < n) {
        int progress = 0;

        for (int i = 0; i < n; i++) {
            if (finished[i]) continue;

            int possible = 1;
            for (int j = 0; j < m; j++) {
                if (need[i][j] > work[j]) {
                    possible = 0;
                    break;
                }
            }

            if (possible) {
                for (int j = 0; j < m; j++)
                    work[j] += allocation[i][j];
                finished[i] = 1;
                sequence[count++] = i;
                progress = 1;
            }
        }

        if (!progress) break;
    }

    if (count == n) {
        printf("\nSystem is SAFE.\nSafe sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d%s", sequence[i], i == n - 1 ? "\n" : " -> ");
    } else {
        printf("\nSystem is UNSAFE.\nUnfinished processes: ");
        for (int i = 0; i < n; i++)
            if (!finished[i]) printf("P%d ", i);
        printf("\n");
    }

    return 0;
}
