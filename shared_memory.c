#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SHM_NAME "/os_lab_shm"

typedef struct {
    int flag;
    char message[200];
} SharedMemory;

int main(void) {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }

    if (ftruncate(fd, sizeof(SharedMemory)) == -1) {
        perror("ftruncate");
        return 1;
    }

    SharedMemory *shm = mmap(NULL, sizeof(SharedMemory),
                             PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    shm->flag = 0;

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        while (shm->flag != 1) usleep(1000);
        printf("Child received: %s\n", shm->message);
        strcpy(shm->message, "Reply from child");
        shm->flag = 2;
        munmap(shm, sizeof(SharedMemory));
        close(fd);
        exit(0);
    }

    strcpy(shm->message, "Hello child, this is the parent");
    shm->flag = 1;
    wait(NULL);

    if (shm->flag == 2)
        printf("Parent received: %s\n", shm->message);

    munmap(shm, sizeof(SharedMemory));
    close(fd);
    shm_unlink(SHM_NAME);
    return 0;
}
