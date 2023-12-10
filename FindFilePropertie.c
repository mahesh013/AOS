// Write a C program to find file properties such as inode number, number of hard link, File 
// permissions, File size, File access and modification time and so on of a given file using stat() 
// system call.
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
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
 // Display file properties
 printf("File Properties for: %s\n", file_path);
 printf("Inode number: %ld\n", (long)file_stat.st_ino);
 printf("Number of hard links: %ld\n", (long)file_stat.st_nlink);
 printf("File permissions: %o\n", file_stat.st_mode & 0777); // Display as octal
 printf("File size: %ld bytes\n", (long)file_stat.st_size);
 // Convert access and modification times to a human-readable format
 char access_time[20], modify_time[20];
 strftime(access_time, sizeof(access_time), "%Y-%m-%d %H:%M:%S", 
localtime(&file_stat.st_atime));
 strftime(modify_time, sizeof(modify_time), "%Y-%m-%d %H:%M:%S", 
localtime(&file_stat.st_mtime));
 printf("Last access time: %s\n", access_time);
 printf("Last modification time: %s\n", modify_time);
 return EXIT_SUCCESS;
}
