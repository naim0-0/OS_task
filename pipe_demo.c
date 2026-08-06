#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    // fd[0] is for reading, fd[1] is for writing
    int fd[2]; 
    pid_t pid;
    char buffer[100];
    char *message = "Hello from the Parent via Pipe!";

    // 1. Initialize the unidirectional pipe
    if (pipe(fd) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    // 2. Fork a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid > 0) {
        // ==========================================
        // PARENT PROCESS (Sender)
        // ==========================================
        
        // Close the read end of the pipe (parent only writes)
        close(fd[0]); 

        // Write the message to the pipe (including the null terminator)
        write(fd[1], message, strlen(message) + 1);
        
        // Close the write end after sending the data
        close(fd[1]); 

        // Synchronize: Wait for the child process to complete
        wait(NULL); 
    } 
    else {
        // ==========================================
        // CHILD PROCESS (Receiver)
        // ==========================================
        
        // Close the write end of the pipe (child only reads)
        close(fd[1]); 

        // Read the data from the pipe into the text buffer
        read(fd[0], buffer, sizeof(buffer));
        
        // Print the received message
        printf("Child Process Received: %s\n", buffer);
        
        // Close the read end after reading
        close(fd[0]); 

        // Overwrite memory image and execute the system utility "whoami"
        execlp("whoami", "whoami", NULL);

        // This line only executes if execlp() fails
        perror("execlp failed");
        return 1;
    }

    return 0;
}
