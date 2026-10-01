#include <stdio.h>

#define FRAME_COUNT 3

int main(void) {
    /* Hardcoded reference string and number of frames. */
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int frame_count = FRAME_COUNT;
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames[FRAME_COUNT] = {-1, -1, -1};
    int faults = 0;

    printf("Optimal Page Replacement\n");
    printf("Page\tFrames\t\tResult\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int victim = -1;

            /* Use an empty frame first. */
            for (int j = 0; j < frame_count; j++) {
                if (frames[j] == -1) {
                    victim = j;
                    break;
                }
            }

            /* Otherwise replace the page used farthest in the future. */
            if (victim == -1) {
                int farthest = -1;
                for (int j = 0; j < frame_count; j++) {
                    int next_use;
                    for (next_use = i + 1; next_use < n; next_use++) {
                        if (pages[next_use] == frames[j]) break;
                    }
                    if (next_use > farthest) {
                        farthest = next_use;
                        victim = j;
                    }
                }
            }

            frames[victim] = pages[i];
            faults++;
        }

        printf("%d\t", pages[i]);
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == -1) printf("- ");
            else printf("%d ", frames[j]);
        }
        printf("\t%s\n", found ? "Hit" : "Fault");
    }

    printf("Total page faults = %d\n", faults);
    return 0;
}
