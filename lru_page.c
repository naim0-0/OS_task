#include <stdio.h>

#define FRAME_COUNT 3

int main(void) {
    /* Hardcoded reference string and number of frames. */
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int frame_count = FRAME_COUNT;
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames[FRAME_COUNT] = {-1, -1, -1};
    int last_used[FRAME_COUNT] = {-1, -1, -1};
    int faults = 0;

    printf("LRU Page Replacement\n");
    printf("Page\tFrames\t\tResult\n");

    for (int i = 0; i < n; i++) {
        int position = -1;

        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == pages[i]) {
                position = j;
                break;
            }
        }

        if (position == -1) {
            int victim = 0;
            for (int j = 1; j < frame_count; j++) {
                if (last_used[j] < last_used[victim]) victim = j;
            }
            frames[victim] = pages[i];
            last_used[victim] = i;
            faults++;
        } else {
            last_used[position] = i;
        }

        printf("%d\t", pages[i]);
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == -1) printf("- ");
            else printf("%d ", frames[j]);
        }
        printf("\t%s\n", position == -1 ? "Fault" : "Hit");
    }

    printf("Total page faults = %d\n", faults);
    return 0;
}
