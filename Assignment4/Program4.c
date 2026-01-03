#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int out_fd;
    int in_fd;
    char buffer[1024];
    int bytes_read;
    int i;

    if (argc < 3)
    {
        write(1, "Usage: ./merge <output> <file1> <file2> ...\n", 45);
        return 1;
    }

    out_fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_fd == -1)
    {
        write(1, "Error: Cannot create output file\n", 33);
        return 1;
    }

    for (i = 2; i < argc; i++)
    {
        in_fd = open(argv[i], O_RDONLY);
        if (in_fd == -1)
        {
            write(1, "Error: Cannot open input file\n", 30);
            close(out_fd);
            return 1;
        }

        while (1)
        {
            bytes_read = read(in_fd, buffer, sizeof(buffer));
            if (bytes_read == 0)
            {
                break;
            }
            if (bytes_read == -1)
            {
                write(1, "Error: Read failed\n", 20);
                close(in_fd);
                close(out_fd);
                return 1;
            }

            write(out_fd, buffer, bytes_read);
        }

        close(in_fd);
    }

    close(out_fd);

    write(1, "Files merged successfully\n", 26);

    return 0;
}
