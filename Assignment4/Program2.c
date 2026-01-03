#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int src_fd;
    int dest_fd;
    char buffer[1024];
    int bytes_read;
    int offset;

    if (argc != 4)
    {
        write(1, "Usage: ./copy <source> <destination> <offset>\n", 48);
        return 1;
    }

    offset = atoi(argv[3]);

    src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1)
    {
        write(1, "Error: Cannot open source file\n", 31);
        return 1;
    }

    if (lseek(src_fd, offset, SEEK_SET) == -1)
    {
        write(1, "Error: Invalid offset\n", 22);
        close(src_fd);
        return 1;
    }

    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1)
    {
        write(1, "Error: Cannot create destination file\n", 39);
        close(src_fd);
        return 1;
    }

    while (1)
    {
        bytes_read = read(src_fd, buffer, sizeof(buffer));
        if (bytes_read == 0)
        {
            break;
        }
        if (bytes_read == -1)
        {
            write(1, "Error: Read failed\n", 20);
            close(src_fd);
            close(dest_fd);
            return 1;
        }

        write(dest_fd, buffer, bytes_read);
    }

    close(src_fd);
    close(dest_fd);

    write(1, "File copied from given offset\n", 30);

    return 0;
}
