#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
    char Directory[100];
    char filePath[200];
    struct dirent *ptr;
    struct stat sobj;
    int count = 0;

    printf("Enter Directory Name: ");
    scanf("%s", Directory);

    DIR *dptr = opendir(Directory);
    if (dptr == NULL)
    {
        perror("opendir failed");
        return 1;
    }

    while ((ptr = readdir(dptr)) != NULL)
    {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
        {
            continue;
        }

        sprintf(filePath, "%s/%s", Directory, ptr->d_name);

        if (stat(filePath, &sobj) == 0)
        {
            if (S_ISREG(sobj.st_mode) && sobj.st_size == 0)
            {
                if (unlink(filePath) == 0)
                {
                    printf("Deleted: %s\n", ptr->d_name);
                    count++;
                }
            }
        }
    }

    closedir(dptr);

    printf("Total empty files deleted: %d\n", count);

    return 0;
}
