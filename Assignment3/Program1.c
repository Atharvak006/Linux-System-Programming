#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
    char SourceFile[100], DestinationFile[100];
    char Buffer[1024];
    int fd1, fd2;
    int iRet;
    struct stat sobj;

    printf("Enter Source file and destination file:\n");
    scanf("%s %s", SourceFile, DestinationFile);

    fd1 = open(SourceFile, O_RDONLY);
    if (fd1 == -1) {
        perror("Source file could not be opened");
        return 1;
    }

    fd2 = open(DestinationFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 == -1) {
        perror("Destination file could not be opened");
        close(fd1);
        return 1;
    }

    while ((iRet = read(fd1, Buffer, sizeof(Buffer))) > 0) {
        write(fd2, Buffer, iRet);
    }

    stat(SourceFile,&sobj);

    chmod(DestinationFile,sobj.st_mode);
    if (iRet == -1) {
        perror("Read failed");
    }

    close(fd1);
    close(fd2);

    return 0;
}
