#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void print_permissions(mode_t mode)
{
    char perm[10];

    if (mode & S_IRUSR)
        perm[0] = 'r';
    else
        perm[0] = '-';

    if (mode & S_IWUSR)
        perm[1] = 'w';
    else
        perm[1] = '-';

    if (mode & S_IXUSR)
        perm[2] = 'x';
    else
        perm[2] = '-';

    if (mode & S_IRGRP)
        perm[3] = 'r';
    else
        perm[3] = '-';

    if (mode & S_IWGRP)
        perm[4] = 'w';
    else
        perm[4] = '-';

    if (mode & S_IXGRP)
        perm[5] = 'x';
    else
        perm[5] = '-';

    if (mode & S_IROTH)
        perm[6] = 'r';
    else
        perm[6] = '-';

    if (mode & S_IWOTH)
        perm[7] = 'w';
    else
        perm[7] = '-';

    if (mode & S_IXOTH)
        perm[8] = 'x';
    else
        perm[8] = '-';

    perm[9] = '\0';

    printf("%s ", perm);
}

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    char path[1024];

    if (argc != 2)
    {
        printf("Usage: ./Is_clone <directory_path>\n");
        return 1;
    }

    dp = opendir(argv[1]);
    if (dp == NULL)
    {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0)
            continue;

        if (strcmp(entry->d_name, "..") == 0)
            continue;

        sprintf(path, "%s/%s", argv[1], entry->d_name);

        if (lstat(path, &statbuf) == -1)
        {
            perror("lstat");
            continue;
        }

        printf("%s ", entry->d_name);

        if (S_ISREG(statbuf.st_mode)){
            printf("FILE ");
        }
        else if (S_ISDIR(statbuf.st_mode)){
            printf("DIR  ");
        }
        else if (S_ISLNK(statbuf.st_mode))
        {
            printf("LINK ");
        }
        else{
            printf("OTHER ");
        }
        printf("%ld ", statbuf.st_size);

        print_permissions(statbuf.st_mode);

        printf("%s", ctime(&statbuf.st_mtime));
    }

    closedir(dp);
    return 0;
}
