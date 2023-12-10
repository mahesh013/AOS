// Read the current directory and display the name of the files, no of files in current directory
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
int main() {
 DIR *dir;
 struct dirent *entry;
 // Open the current directory
 if ((dir = opendir(".")) == NULL) {
 perror("opendir");
 exit(EXIT_FAILURE);
 }
 // Initialize file count
 int file_count = 0;
 // Read the directory entries
 while ((entry = readdir(dir)) != NULL) {
 // Exclude the special entries "." and ".."
 if (entry->d_name[0] != '.') {
 // Print the name of the file
 printf("%s\n", entry->d_name);
 // Increment the file count
 file_count++;
 }
 }
 // Close the directory
 closedir(dir);
 // Display the total number of files
 printf("Total number of files: %d\n", file_count);
 return EXIT_SUCCESS;
}