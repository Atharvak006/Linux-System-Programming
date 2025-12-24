#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(void)
{
    char filename[100];
    char Mode[10];

    printf("Enter the file name:\n");
    scanf("%s", filename);

    printf("Enter the mode:\n");
    scanf("%s", Mode);

    int fd = -1;

    if (strcmp(Mode, "R") == 0 || strcmp(Mode, "r") == 0) {
        fd = open(filename, O_RDONLY);
    }
    else if (strcmp(Mode, "W") == 0 || strcmp(Mode, "w") == 0) {
        fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    else if (strcmp(Mode, "RW") == 0 || strcmp(Mode, "rw") == 0) {
        fd = open(filename, O_RDWR | O_CREAT, 0644);
    }
    else if (strcmp(Mode, "A") == 0 || strcmp(Mode, "a") == 0) {
        fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    else {
        printf("Invalid choice\n");
        return 1;
    }

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("fd = %d\n", fd);

    close(fd);
    return 0;
}
