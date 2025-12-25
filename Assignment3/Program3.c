#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    char SourceDirectory[100], DestinationDirectory[100];
    char srcPath[200], destPath[200];
    struct dirent *ptr;
    struct stat sobj;
    int count = 0, iRet = 0;

    printf("Enter Source Directory: ");
    scanf("%s", SourceDirectory);

    printf("Enter Destination Directory: ");
    scanf("%s", DestinationDirectory);

    DIR *dptr = opendir(SourceDirectory);
    if (dptr == NULL)
    {
        perror("opendir failed");
        return 1;
    }

    while ((ptr = readdir(dptr)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0){
            continue;
        }

        sprintf(srcPath, "%s/%s", SourceDirectory, ptr->d_name);
        sprintf(destPath, "%s/%s", DestinationDirectory, ptr->d_name);

        stat(srcPath, &sobj);

        if (S_ISREG(sobj.st_mode))
        {
            iRet = rename(srcPath,destPath);
            if (iRet == 0)
            {
                count++;
            }
        }
    }

    closedir(dptr);

    printf("Total files moved: %d\n", count);
    return 0;
}
