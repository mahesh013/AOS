
// 2. Write a C program to create an unnamed pipe. The child process will write following three 
// messages to pipe and parent process display it. Message1 = “Hello World” Message2 = 
// “Hello SPPU” Message3 = “Linux is Funny”
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#define BUFFER_SIZE 100
int main() {
 int pipe_fd[2]; // File descriptors for the pipe
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
 // Close the read end of the pipe
 close(pipe_fd[0]);
 // Messages to be written to the pipe
 char *messages[] = {"Hello World", "Hello SPPU", "Linux is Funny"};
 // Write each message to the pipe
 for (int i = 0; i < 3; ++i) {
 write(pipe_fd[1], messages[i], strlen(messages[i]) + 1);
 }
 // Close the write end of the pipe
 close(pipe_fd[1]);
 exit(EXIT_SUCCESS);
 } else {
 // Parent process
 // Close the write end of the pipe
 close(pipe_fd[1]);
 // Buffer to read messages from the pipe
 char buffer[BUFFER_SIZE];
 // Read and display each message from the pipe
 while (read(pipe_fd[0], buffer, BUFFER_SIZE) > 0) {
 printf("Received message: %s\n", buffer);
 }
 // Close the read end of the pipe
 close(pipe_fd[0]);
 // Wait for the child process to finish
 wait(NULL);
 printf("Parent process exiting.\n");
 }
 return 0;
}
