// Generate parent process to write unnamed pipe and will write into it. Also generate child 
// process which will read from pipe.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 100
int main() {
 int pipe_fd[2];
 pid_t child_pid;
 // Create a pipe
 if (pipe(pipe_fd) == -1) {
 perror("pipe");
 exit(EXIT_FAILURE);
 }
 // Create a child process
 if ((child_pid = fork()) == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if (child_pid == 0) {
 // Child process
 // Close the write end of the pipe
 close(pipe_fd[1]);
 // Buffer to read from the pipe
 char buffer[BUFFER_SIZE];
 // Read from the pipe and print the message
 ssize_t read_bytes = read(pipe_fd[0], buffer, sizeof(buffer));
 if (read_bytes == -1) {
 perror("read");
 exit(EXIT_FAILURE);
 }
 buffer[read_bytes] = '\0'; // Null-terminate the string
 printf("Child process received message: %s\n", buffer);
 // Close the read end of the pipe
 close(pipe_fd[0]);
 exit(EXIT_SUCCESS);
 } else {
 // Parent process
 // Close the read end of the pipe
 close(pipe_fd[0]);
 // Message to be written to the pipe
 const char *message = "Hello from the parent process!";
 // Write the message to the pipe
 if (write(pipe_fd[1], message, strlen(message)) == -1) {
 perror("write");
 close(pipe_fd[1]);
 exit(EXIT_FAILURE);
 }
 // Close the write end of the pipe
 close(pipe_fd[1]);
 // Wait for the child process to finish
 waitpid(child_pid, NULL, 0);
 printf("Parent process exiting.\n");
 }
 return EXIT_SUCCESS;
}