// Write a C program which creates a child process to run linux/ unix command or any user 
// defined program. The parent process set the signal handler for death of child signal and 
// Alarm signal. If a child process does not complete its execution in 5 second then parent 
// process kills child process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
// Signal handler for SIGCHLD (child process death)
void sigchld_handler(int signum) {
 int status;
 pid_t child_pid;
 // Reap the child process to avoid zombie processes
 while ((child_pid = waitpid(-1, &status, WNOHANG)) > 0) {
 if (WIFEXITED(status)) {
 printf("Child process %d exited with status %d.\n", child_pid, WEXITSTATUS(status));
 } else if (WIFSIGNALED(status)) {
 printf("Child process %d terminated by signal %d.\n", child_pid, WTERMSIG(status));
 }
 }
}
// Signal handler for SIGALRM (alarm signal)
void sigalrm_handler(int signum) {
 printf("Child process execution time exceeded. Killing the child process.\n");
 exit(EXIT_FAILURE);
}
int main() {
 pid_t child_pid;
 // Set the signal handler for SIGCHLD
 signal(SIGCHLD, sigchld_handler);
 // Create a child process
 if ((child_pid = fork()) == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if (child_pid == 0) {
 // Child process
 // Execute a command (e.g., "ls")
 execlp("ls", "ls", (char *)NULL);
 // If execlp fails
 perror("execlp");
 exit(EXIT_FAILURE);
 } else {
 // Parent process
 // Set the signal handler for SIGALRM
 signal(SIGALRM, sigalrm_handler);
 // Set an alarm for 5 seconds
 alarm(5);
 // Wait for the child process to finish
 waitpid(child_pid, NULL, 0);
 // Cancel the alarm
 alarm(0);
 printf("Parent process exiting.\n");
 }
 return 0;
}