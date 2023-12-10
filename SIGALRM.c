// . Write a C program to send SIGALRM signal by child process to parent process and parent 
// process make a provision to catch the signal and display alarm is fired.(Use Kill, fork, signal 
// and sleep system call)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
void alarm_handler(int signum) {
 printf("Alarm is fired!\n");
}
int main() {
 pid_t child_pid;
 // Register the signal handler for SIGALRM
 signal(SIGALRM, alarm_handler);
 // Create a child process
 if ((child_pid = fork()) == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if (child_pid == 0) {
 // Child process
 // Sleep for a few seconds
 sleep(2);
 // Send SIGALRM to the parent process
 kill(getppid(), SIGALRM);
 exit(EXIT_SUCCESS);
 } else {
 // Parent process
 // Wait for the child process to finish
 wait(NULL);
 printf("Parent process exiting.\n");
 }
 return 0;
}