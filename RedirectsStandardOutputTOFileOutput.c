// Write a C program that redirects standard output to a file output.txt. (use of dup and open 
// system call)
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
 // Open the file for writing (creates a new file or truncates an existing file)
 int file_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
 if (file_fd == -1) {
 perror("open");
 exit(EXIT_FAILURE);
 }
 // Duplicate the file descriptor to stdout (file descriptor 1)
 if (dup2(file_fd, STDOUT_FILENO) == -1) {
 perror("dup2");
 close(file_fd);
 exit(EXIT_FAILURE);
 }
 // Now, standard output is redirected to the file "output.txt"
 // Print some output
 printf("This text is redirected to the file.\n");
 // Close the file
 close(file_fd);
 // The redirection is no longer in effect, and output will go to the console
 // Print some more output
 printf("This text is displayed in the console.\n");
 return 0;
}
