// Write a C program to find whether a given files passed through command line arguments 
// are present in current directory or not.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
 // Check if there are command line arguments
 if (argc < 2) {
 fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
 exit(EXIT_FAILURE);
 }
 // Iterate through each command line argument (starting from index 1)
 for (int i = 1; i < argc; ++i) {
 const char *file_path = argv[i];
 // Check if the file exists in the current directory
 if (access(file_path, F_OK) == 0) {
 printf("%s exists in the current directory.\n", file_path);
 } else {
 printf("%s does not exist in the current directory.\n", file_path);
 }
 }
 return EXIT_SUCCESS;
}
