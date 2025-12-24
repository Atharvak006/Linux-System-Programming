#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(void)
{
    char filename[50];
    int fd;

    printf("Enter the file name: ");
    scanf("%s",&filename[0]);

    fd = open(filename, O_RDWR);

    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }

    printf("File successfully opened\n");
    printf("File descriptor: %d\n", fd);

    close(fd);
    return 0;
}
