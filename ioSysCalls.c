#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
int main() {
    const char *filename = "example.txt";
    // 1. open
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    // 2. write
    const char *text = "Hello, UNIX/Linux I/O system calls!\n";
    if (write(fd, text, strlen(text)) < 0) {
        perror("write");
        close(fd);
        return 1;
    }
    // 3. lseek
    if (lseek(fd, 0, SEEK_SET) < 0) {
        perror("lseek");
        close(fd);
        return 1;
    }
    // 4. read
    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        perror("read");
        close(fd);
        return 1;
    }
    buffer[bytesRead] = '\0';
    printf("Read from file: %s", buffer);
    // 5. fcntl
    int flags = fcntl(fd, F_GETFL);
    if (flags < 0) {
        perror("fcntl");
    } else {
        printf("File access mode: %d\n", flags & O_ACCMODE);
    }
    // 6. close
    close(fd);
    // 7. stat
    struct stat fileStat;
    if (stat(filename, &fileStat) == 0) {
        printf("File size: %lld bytes\n", (long long)fileStat.st_size);
        printf("Last modified: %ld\n", (long)fileStat.st_mtime);
    } else {
        perror("stat");
    }
    // 8. opendir and readdir
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }
    printf("Directory contents:\n");
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("  %s\n", entry->d_name);
    }
    closedir(dir);
    return 0;
}
