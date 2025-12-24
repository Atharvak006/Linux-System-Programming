#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFFERSIZE 1024
int main(void)
{
    char filename[50];
    int fd;

    int iRet = 0;
    int totalbytes = 0;
    printf("Enter the file name: ");
    scanf("%s",&filename[0]);

    char buffer[BUFFERSIZE];

    fd = open(filename,O_RDONLY);

    if(fd == -1){
        printf("Unable to open the file\n");
    }

    while((iRet = read(fd,filename,BUFFERSIZE)) > 0){
        write(1,buffer,iRet);
        totalbytes += iRet;

    }   

    if(iRet == -1){
        perror("Read error\n");
    }

    printf("Total bytes read: %d",totalbytes);
    close(fd);

    return 0;
}
