// Print the type of file and inode number where file name accepted through Command Line
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
 if (argc != 2) {
 fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
 exit(EXIT_FAILURE);
 }
 const char *file_path = argv[1];
 struct stat file_stat;
 // Use stat system call to get file information
 if (stat(file_path, &file_stat) == -1) {
 perror("Error");
 exit(EXIT_FAILURE);
 }
 // Determine file type
 const char *file_type = S_ISREG(file_stat.st_mode) ? "Regular File" :
 S_ISDIR(file_stat.st_mode) ? "Directory" :
 S_ISCHR(file_stat.st_mode) ? "Character Device" :
 S_ISBLK(file_stat.st_mode) ? "Block Device" :
 S_ISFIFO(file_stat.st_mode) ? "FIFO/Named Pipe" :
 S_ISSOCK(file_stat.st_mode) ? "Socket" :
 S_ISLNK(file_stat.st_mode) ? "Symbolic Link" :
 "Unknown Type";
 // Print file type and inode number
 printf("File Type: %s\n", file_type);
 printf("Inode number: %ld\n", (long)file_stat.st_ino);
 return EXIT_SUCCESS;
}
