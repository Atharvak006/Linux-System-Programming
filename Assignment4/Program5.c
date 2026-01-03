#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int fd;
    char ch;
    off_t size;

    if (argc != 2)
    {
        write(1, "Usage: ./reverse <file_name>\n", 30);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        write(1, "Error: Cannot open file\n", 24);
        return 1;
    }

    size = lseek(fd, 0, SEEK_END);
    if (size == -1)
    {
        write(1, "Error: lseek failed\n", 20);
        close(fd);
        return 1;
    }

    while (size > 0)
    {
        size = size - 1;
        lseek(fd, size, SEEK_SET);
        read(fd, &ch, 1);
        write(1, &ch, 1);
    }

    close(fd);

    return 0;
}
