#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>

// Define the shared memory structure
typedef struct {
    int flag;
    char message[1024];
} SharedMemory;

int main() {
    const char *shm_name = "/sync_shm";
    int shm_fd;
    SharedMemory *shm_ptr;
    pid_t pid;

    // Create shared memory object
    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);

    // Allocate sufficient memory for the structure
    ftruncate(shm_fd, sizeof(SharedMemory));

    // Map the shared memory into the process's address space
    shm_ptr = mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Initialize the synchronization flag (0 = waiting for parent)
    shm_ptr->flag = 0;

    // Create a child process
    pid = fork();

    if (pid > 0) {
        // ----------------- PARENT PROCESS ----------------- //
        
        printf("Parent: Enter a message to send to child: ");
        fgets(shm_ptr->message, sizeof(shm_ptr->message), stdin);
        
        // Remove the trailing newline character from fgets
        shm_ptr->message[strcspn(shm_ptr->message, "\n")] = '\0';

        // Update flag to 1 to notify the child that the message is ready
        shm_ptr->flag = 1;

        // Wait until the child updates the flag to 2 (reply is ready)
        while (shm_ptr->flag != 2) {
            // Busy-wait loop (spin wait)
        }

        // Display the child's reply
        printf("Parent: Child replied with -> \"%s\"\n", shm_ptr->message);

        // Wait for the child process to complete entirely
        wait(NULL);

        // Release allocated resources
        munmap(shm_ptr, sizeof(SharedMemory));
        close(shm_fd);
        shm_unlink(shm_name);

    } else if (pid == 0) {
        // ----------------- CHILD PROCESS ----------------- //
        
        // Wait until the parent sets the flag to 1
        while (shm_ptr->flag != 1) {
            // Busy-wait loop (spin wait)
        }

        // Read and display the received message from parent
        printf("Child: Received message -> \"%s\"\n", shm_ptr->message);

        // Write the reply into the shared memory
        strcpy(shm_ptr->message, "Message received loud and clear!");

        // Update the flag to 2 to notify the parent that the reply is ready
        shm_ptr->flag = 2;

        // Release mapping and close file descriptor in the child
        munmap(shm_ptr, sizeof(SharedMemory));
        close(shm_fd);
    }

    return 0;
}