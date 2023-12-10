// Write a C program to Identify the type (Directory, character device, Block device, Regular 
// file, FIFO or pipe, symbolic link or socket) of given file using stat() system call.
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
void identify_file_type(const char *file_path) {
 struct stat file_stat;
 // Use stat to get information about the file
 if (stat(file_path, &file_stat) == -1) {
 perror("stat");
 exit(EXIT_FAILURE);
 }
 // Check the file type based on the mode
 if (S_ISREG(file_stat.st_mode)) {
 printf("%s is a regular file.\n", file_path);
 } else if (S_ISDIR(file_stat.st_mode)) {
 printf("%s is a directory.\n", file_path);
 } else if (S_ISCHR(file_stat.st_mode)) {
 printf("%s is a character device.\n", file_path);
 } else if (S_ISBLK(file_stat.st_mode)) {
 printf("%s is a block device.\n", file_path);
 } else if (S_ISFIFO(file_stat.st_mode)) {
 printf("%s is a FIFO or pipe.\n", file_path);
 } else if (S_ISLNK(file_stat.st_mode)) {
 printf("%s is a symbolic link.\n", file_path);
 } else if (S_ISSOCK(file_stat.st_mode)) {
 printf("%s is a socket.\n", file_path);
 } else {
 printf("%s is of unknown type.\n", file_path);
 }
}
int main(int argc, char *argv[]) {
 // Check if a file path is provided as a command-line argument
 if (argc != 2) {
 fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
 exit(EXIT_FAILURE);
 }
 // Identify the type of the given file
 identify_file_type(argv[1]);
 return EXIT_SUCCESS;
}
