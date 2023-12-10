// Display all the files from current directory which are created in particular month
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
void display_files_created_in_month(const char *dir_path, int target_month) {
 DIR *dir;
 struct dirent *entry;
 // Open the directory
 if ((dir = opendir(dir_path)) == NULL) {
 perror("opendir");
 exit(EXIT_FAILURE);
 }
 // Get the current year
 time_t t = time(NULL);
 struct tm *tm_info = localtime(&t);
 int current_year = tm_info->tm_year + 1900;
 // Read the directory entries
 while ((entry = readdir(dir)) != NULL) {
 char file_path[256];
 snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, entry->d_name);
 struct stat file_stat;
 if (stat(file_path, &file_stat) == 0) {
 struct tm *file_tm_info = localtime(&file_stat.st_ctime);
 // Check if the file was created in the target month
 if (file_tm_info->tm_mon == target_month && file_tm_info->tm_year + 1900 == 
current_year) {
 printf("%s\n", entry->d_name);
 }
 }
 }
 // Close the directory
 closedir(dir);
}
int main() {
 // Specify the target month (0-based index, e.g., January is 0, February is 1, etc.)
 int target_month = 11; // December
 // Display files created in the specified month
 display_files_created_in_month(".", target_month);
 return EXIT_SUCCESS;
}
