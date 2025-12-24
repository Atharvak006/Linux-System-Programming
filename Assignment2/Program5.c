#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

int main(void)
{
    char DirectoryName[100];
    printf("Enter the Directory Name:\n");
    scanf("%99s", DirectoryName);

    struct dirent *ptr = NULL;
    struct stat sobj;
    DIR *dptr = NULL;

    dptr = opendir(DirectoryName);

    char LargestFile[100] = "";
    off_t MaxSize = 0;
    char path[200];

    if (dptr == NULL)
    {
        perror("opendir failed");
        return 1;
    }

    while ((ptr = readdir(dptr)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;

        /*
            Explanation for snprintf:
            DirectoryName = "Assignment2"
            ptr->d_name   = "Program5.c"

            snprintf ek asa function ahe je aplyala akhya path la build karayla madat krta.

            eg: Assignment2/Program5.c -> ha path aplyala stat() la dyava lagto.
        */

        snprintf(path, sizeof(path), "%s/%s", DirectoryName, ptr->d_name);

        int iRet = 0;

        iRet = stat(path,&sobj);
        if (iRet == 0)
        {
            if (S_ISREG(sobj.st_mode))
            {
                if (sobj.st_size > MaxSize)
                {
                    MaxSize = sobj.st_size;
                    strcpy(LargestFile, ptr->d_name);
                }
            }
        }
    }

    closedir(dptr);

    if (MaxSize > 0)
    {
        printf("Largest File Name: %s\n", LargestFile);
        printf("Size: %lld bytes\n", MaxSize);
    }
    else
    {
        printf("No regular files found in the directory\n");
    }

    return 0;
}
