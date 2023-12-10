// Write a C Program that demonstrates redirection of standard output to a file
#include <stdio.h>
int main() {
 // Open the file for writing (creates a new file or truncates an existing file)
 FILE *file = freopen("output.txt", "w", stdout);
 if (file == NULL) {
 perror("freopen");
 return 1;
 }
 // Now, stdout is redirected to the file "output.txt"
 // Print some output
 printf("This text is redirected to the file.\n");
 // Close the file
 fclose(file);
 // The redirection is no longer in effect, and output will go to the console
 // Print some more output
 printf("This text is displayed in the console.\n");
 return 0;
}