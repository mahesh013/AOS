// Implement the following unix/linux command (use fork, pipe and exec system call) ls –l | 
// wc –l.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
 int pipe_fd[2];
 pid_t child1_pid, child2_pid;
 // Create a pipe
 if (pipe(pipe_fd) == -1) {
 perror("pipe");
 exit(EXIT_FAILURE);
 }
 // Create the first child process for "ls -l"
 if ((child1_pid = fork()) == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if (child1_pid == 0) {
 // Child process 1 (ls -l)
 // Close the read end of the pipe
 close(pipe_fd[0]);
 // Redirect stdout to the write end of the pipe
 dup2(pipe_fd[1], STDOUT_FILENO);
 // Close the unused write end of the pipe
 close(pipe_fd[1]);
 // Execute "ls -l"
 execlp("ls", "ls", "-l", NULL);
 // If execlp fails
 perror("execlp");
 exit(EXIT_FAILURE);
 } else {
 // Create the second child process for "wc -l"
 if ((child2_pid = fork()) == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if (child2_pid == 0) {
 // Child process 2 (wc -l)
 // Close the write end of the pipe
 close(pipe_fd[1]);
 // Redirect stdin to the read end of the pipe
 dup2(pipe_fd[0], STDIN_FILENO);
 // Close the unused read end of the pipe
 close(pipe_fd[0]);
 // Execute "wc -l"
 execlp("wc", "wc", "-l", NULL);
 // If execlp fails
 perror("execlp");
 exit(EXIT_FAILURE);
 } else {
 // Parent process
 // Close both ends of the pipe
 close(pipe_fd[0]);
 close(pipe_fd[1]);
 // Wait for both child processes to finish
 waitpid(child1_pid, NULL, 0);
 waitpid(child2_pid, NULL, 0);
 }
 }
 return EXIT_SUCCESS;
}