#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void get_file_info(const char *file_path) {
    struct stat file_stat;

    // Get file information
    if (lstat(file_path, &file_stat) == 0) {
        // Determine file type
        const char *file_type;

        if (S_ISREG(file_stat.st_mode)) {
            file_type = "Regular File";
        } else if (S_ISDIR(file_stat.st_mode)) {
            file_type = "Directory";
        } else if (S_ISCHR(file_stat.st_mode)) {
            file_type = "Character Device";
        } else if (S_ISBLK(file_stat.st_mode)) {
            file_type = "Block Device";
        } else if (S_ISFIFO(file_stat.st_mode)) {
            file_type = "FIFO/Named Pipe";
        } else if (S_ISLNK(file_stat.st_mode)) {
            file_type = "Symbolic Link";
        } else if (S_ISSOCK(file_stat.st_mode)) {
            file_type = "Socket";
        } else {
            file_type = "Unknown Type";
        }

        // Print file information
        printf("%s: Inode=%lu, Type=%s\n", file_path, (unsigned long)file_stat.st_ino, file_type);
    } else {
        perror("Error");
    }
}

int main(int argc, char *argv[]) {
    // Check if there are command line arguments
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 file2 ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Process each file path provided as a command line argument
    for (int i = 1; i < argc; ++i) {
        get_file_info(argv[i]);
    }

    return EXIT_SUCCESS;
}
