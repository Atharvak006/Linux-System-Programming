#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include<stdlib.h>

int main(void)
{
    char Filename[100];
    char Mode[10];
    int fd = 0;
    int iRet = 0;
    printf("Enter the file name:\n");
    scanf("%s", Filename);

    char *Buffer = NULL;

    int N = 0;
    printf("Enter the number of bytes to read: \n");
    scanf("%d",&N);

    fd = open(Filename,O_RDWR);

    if(fd == -1){
        perror("Unable to open the file\n");
        return 1;
    }

    Buffer = (char*)malloc(sizeof(char) * N);

    if(Buffer == NULL){
        perror("Memory allocation failed");
        close(fd);
        return 1;
    }

    iRet = read(fd,Buffer,N);

    if (iRet == -1)
    {
        perror("Read failed");
        free(Buffer);
        close(fd);
        return 1;
    }

    write(1, Buffer, iRet);

    // printf("\nBytes read: %d\n", iRet);

    // printf("%s",Buffer);
    free(Buffer);
    close(fd);

    return 0;
}