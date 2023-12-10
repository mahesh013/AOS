// Write a C program that catches the ctrl-c (SIGINT) signal for the first time and display the 
// appropriate message and exits on pressing ctrl-c again
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
int ctrl_c_count = 0;
// Signal handler function for SIGINT
void sigint_handler(int signum) {
 if (ctrl_c_count == 0) {
 printf("Ctrl-C pressed. Press Ctrl-C again to exit.\n");
 ctrl_c_count++;
 } else {
 printf("Ctrl-C pressed again. Exiting...\n");
 exit(EXIT_SUCCESS);
 }
}
int main() {
 // Register the signal handler for SIGINT
 signal(SIGINT, sigint_handler);
 // Infinite loop to keep the program running
 while (1) {
 // Your main program logic goes here
 // For demonstration purposes, this loop just sleeps
 sleep(1);
 }
 return 0;
}
