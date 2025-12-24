#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include <sys/stat.h>
#include<sys/types.h>
#include <dirent.h>

int main(void)
{
    char DirectoryName[100];
    printf("Enter the Directory Name: \n");
    scanf("%s",DirectoryName);
    char path[100];
    struct dirent* ptr = NULL;
    struct stat sobj;
    DIR * dptr = NULL;

    dptr = opendir(DirectoryName);

    if(dptr == NULL)
    {
        perror("Directory couldnt be opened: ");
        return 1;
    }

    while((ptr = readdir(dptr)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0){
            continue;
        }


        if (S_ISREG(sobj.st_mode)){
            printf("Regular File\n");
        }
        else if (S_ISDIR(sobj.st_mode)){
            printf("Directory\n");
        }
        else if (S_ISLNK(sobj.st_mode)){
            printf("Symbolic Link\n");
        }
        else if (S_ISFIFO(sobj.st_mode)){
            printf("FIFO\n");
        }
        else if (S_ISSOCK(sobj.st_mode)){
            printf("Socket\n");
        }
        else if (S_ISCHR(sobj.st_mode)){
            printf("Character Device\n");
        }
        else if (S_ISBLK(sobj.st_mode))
        {
            printf("Block Device\n");
        }
        else{
            printf("Unknown\n");
        }

    }

    return 0;
}