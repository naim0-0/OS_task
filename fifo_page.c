#include <stdio.h>

#define FRAME_COUNT 3

int main(void) {
    /* Hardcoded reference string and number of frames. */
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int frame_count = FRAME_COUNT;
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames[FRAME_COUNT] = {-1, -1, -1};
    int next = 0, faults = 0;

    printf("FIFO Page Replacement\n");
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
            frames[next] = pages[i];
            next = (next + 1) % frame_count;
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
