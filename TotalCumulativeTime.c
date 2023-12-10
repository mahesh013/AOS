// Write a C program to create n child processes. When all n child processes terminates, 
// Display total cumulative time children spent in user and kernel mode
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <unistd.h>
void child_process(int child_number) {
 printf("Child %d started.\n", child_number);
 sleep(2); // Simulating some work in the child process
 printf("Child %d completed.\n", child_number);
}
int main(int argc, char *argv[]) {
 if (argc != 2) {
 fprintf(stderr, "Usage: %s <number_of_children>\n", argv[0]);
 exit(EXIT_FAILURE);
 }
 int n = atoi(argv[1]);
 // Initialize variables for time measurement
 clock_t start_time, end_time;
 struct tms start_cpu, end_cpu;
 // Record the start time and CPU time
 start_time = times(&start_cpu);
 // Create n child processes
 for (int i = 0; i < n; ++i) {
 pid_t child_pid = fork();
 if (child_pid == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 } else if (child_pid == 0) {
 // Child process
 child_process(i);
 exit(EXIT_SUCCESS);
 }
 }
 // Wait for all child processes to complete
 int status;
 pid_t child_pid;
 while ((child_pid = wait(&status)) > 0);
 // Record the end time and CPU time
 end_time = times(&end_cpu);
 // Calculate the total cumulative time
 clock_t user_time = end_cpu.tms_utime - start_cpu.tms_utime;
 clock_t system_time = end_cpu.tms_stime - start_cpu.tms_stime;
 printf("Total Cumulative User Time: %f seconds\n", (double)user_time / 
sysconf(_SC_CLK_TCK));
 printf("Total Cumulative System Time: %f seconds\n", (double)system_time / 
sysconf(_SC_CLK_TCK));
 return EXIT_SUCCESS;
}
