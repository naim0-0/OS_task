#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;
    int burst;
    int period; 
    int rem_time;
    int deadline;
} Process;

typedef struct {
    int pid; // -1 for IDLE
    int start;
    int end;
} Interval;

int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }
int lcm(int a, int b) { return (a * b) / gcd(a, b); }

void render_gantt_chart(int timeline[], int hyperperiod) {
    Interval intervals[150];
    int count = 0;
    int current_proc = timeline[0];
    int start = 0;

    for (int t = 1; t <= hyperperiod; t++) {
        if (t == hyperperiod || timeline[t] != current_proc) {
            intervals[count].pid = current_proc;
            intervals[count].start = start;
            intervals[count].end = t;
            count++;
            if (t < hyperperiod) {
                current_proc = timeline[t];
                start = t;
            }
        }
    }

    printf("\n============================================================\n");
    printf("                    EDF GANTT CHART                         \n");
    printf("============================================================\n\n");

    // Interval Table
    printf("Execution Intervals:\n");
    for (int i = 0; i < count; i++) {
        if (intervals[i].pid == -1) {
            printf("Time %3d - %3d: IDLE\n", intervals[i].start, intervals[i].end);
        } else {
            printf("Time %3d - %3d: Process P%d\n", intervals[i].start, intervals[i].end, intervals[i].pid);
        }
    }
    printf("\nVisual Block Chart:\n");

    // Top Border
    printf("+");
    for (int i = 0; i < count; i++) {
        printf("---------+");
    }
    printf("\n|");

    // Process Names
    for (int i = 0; i < count; i++) {
        if (intervals[i].pid == -1) {
            printf("  IDLE   |");
        } else {
            printf("   P%d    |", intervals[i].pid);
        }
    }
    printf("\n+");

    // Bottom Border
    for (int i = 0; i < count; i++) {
        printf("---------+");
    }
    printf("\n");

    // Time Markers
    printf("%-10d", intervals[0].start);
    for (int i = 0; i < count; i++) {
        printf("%-10d", intervals[i].end);
    }
    printf("\n\n");
}

int main() {
    // Process parameters: P1 (burst=25, period=50), P2 (burst=30, period=75)
    Process proc[] = {
        {1, 25, 50, 0, 0},
        {2, 30, 75, 0, 0}
    };
    int n = sizeof(proc) / sizeof(proc[0]);
    int hyperperiod = lcm(proc[0].period, proc[1].period);
    int timeline[150];

    for (int t = 0; t < hyperperiod; t++) {
        // Release tasks and set absolute deadline
        for (int i = 0; i < n; i++) {
            if (t % proc[i].period == 0) {
                if (proc[i].rem_time > 0) {
                    printf("[Time %3d] DEADLINE MISS: Process P%d!\n", t, proc[i].id);
                }
                proc[i].rem_time = proc[i].burst;
                proc[i].deadline = t + proc[i].period;
            }
        }

        // Priority by earliest absolute deadline (EDF dynamic priority)
        int selected = -1;
        int min_deadline = 1e9;
        for (int i = 0; i < n; i++) {
            if (proc[i].rem_time > 0 && proc[i].deadline < min_deadline) {
                min_deadline = proc[i].deadline;
                selected = i;
            }
        }

        if (selected != -1) {
            timeline[t] = proc[selected].id;
            proc[selected].rem_time--;
        } else {
            timeline[t] = -1; // IDLE
        }
    }

    render_gantt_chart(timeline, hyperperiod);
    return 0;
}