// Write a C program which creates a child process and child process catches a signal SIGHUP, 
// SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT signal after every 3 
// seconds, at the end of 15 second parent send SIGQUIT signal to child and child terminates 
// by displaying message "My Papa has Killed me!!!”.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
void sighup_handler(int signum) {
 printf("Child process received SIGHUP signal.\n");
}
void sigint_handler(int signum) {
 printf("Child process received SIGINT signal.\n");
}
void sigquit_handler(int signum) {
 printf("Child process received SIGQUIT signal. My Papa has Killed me!!!\n");
 exit(EXIT_SUCCESS);
}
int main() {
 pid_t child_pid;
 // Create a child process
 if ((child_pid = fork()) == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if (child_pid == 0) {
 // Child process
 // Set signal handlers for SIGHUP, SIGINT, and SIGQUIT
 signal(SIGHUP, sighup_handler);
 signal(SIGINT, sigint_handler);
 signal(SIGQUIT, sigquit_handler);
 // Infinite loop to keep the child process running
 while (1) {
 // Sleep for a short duration
 sleep(1);
 }
 } else {
 // Parent process
 // Sleep for 3 seconds and send SIGHUP signal to child
 sleep(3);
 kill(child_pid, SIGHUP);
 // Sleep for another 3 seconds and send SIGINT signal to child
 sleep(3);
 kill(child_pid, SIGINT);
 // Sleep for another 3 seconds and send SIGHUP signal to child
 sleep(3);
 kill(child_pid, SIGHUP);
 // Sleep for another 3 seconds and send SIGINT signal to child
 sleep(3);
 kill(child_pid, SIGINT);
 // Sleep for another 3 seconds and send SIGQUIT signal to child
 sleep(3);
 kill(child_pid, SIGQUIT);
 // Wait for the child process to finish
 waitpid(child_pid, NULL, 0);
 printf("Parent process exiting.\n");
 }
 return 0;
}