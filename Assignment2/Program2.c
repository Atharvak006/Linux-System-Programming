#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
    char Filename[100];
    char mystring[100];

    int iRet = 0;
    int fd = 0;

    printf("Enter the file name: \n");
    scanf("%s",Filename);

    printf("Enter the string: \n");
    scanf(" %[^\n]",mystring);

    fd = open(Filename,O_RDWR | O_CREAT | O_APPEND, 0777);

    iRet = write(fd,mystring,strlen(mystring));

    if(iRet == -1){
        perror("Error in writing");
        return 1;
    }
    
    printf("Number of bytes wrote: %d\n", iRet);
    
    close(fd);
    return 0;
}