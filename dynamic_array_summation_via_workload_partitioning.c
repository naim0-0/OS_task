#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int start;
    int end;
    int *array;
    long long partial_sum;
} Segment;

void *add_part(void *arg) {
    Segment *part = (Segment *)arg;
    part->partial_sum = 0;

    for (int i = part->start; i < part->end; i++) {
        part->partial_sum += part->array[i];
    }

    printf("Thread %d: index %d to %d, partial sum = %lld\n",
           part->id, part->start, part->end - 1, part->partial_sum);
    return NULL;
}

int main(void) {
    int size, thread_count;

    printf("Enter array size: ");
    scanf("%d", &size);

    if (size <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    int *array = malloc((size_t)size * sizeof(int));

    printf("Enter %d integers: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }

    printf("Enter number of threads: ");
    scanf("%d", &thread_count);

    if (thread_count <= 0 || thread_count > size) {
        printf("Thread count must be between 1 and %d.\n", size);
        free(array);
        return 1;
    }

    pthread_t *threads = malloc((size_t)thread_count * sizeof(pthread_t));
    Segment *parts = malloc((size_t)thread_count * sizeof(Segment));

    int basic_size = size / thread_count;
    int extra = size % thread_count;
    int start = 0;

    for (int i = 0; i < thread_count; i++) {
        int length = basic_size + (i < extra ? 1 : 0);

        parts[i].id = i + 1;
        parts[i].start = start;
        parts[i].end = start + length;
        parts[i].array = array;
        start += length;

        pthread_create(&threads[i], NULL, add_part, &parts[i]);
    }

    long long total = 0;
    for (int i = 0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
        total += parts[i].partial_sum;
    }

    printf("Final sum = %lld\n", total);

    free(array);
    free(threads);
    free(parts);
    return 0;
}
