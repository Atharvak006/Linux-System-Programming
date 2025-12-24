#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

int main(void)
{
    char Filename[100];
    char Mode[10];

    int iRet = 0;
    printf("Enter the file name:\n");
    scanf("%s", Filename);

    struct stat sobj;
    int iret = stat(Filename,&sobj);

    if(iret == -1){
        perror("stat");
        return 1;
    }

    printf("\n----- File Information -----\n");

    printf("File Size    : %lld bytes\n", sobj.st_size);
    printf("Inode Number : %llu\n", sobj.st_ino);
    printf("Hard Links   : %hu\n", sobj.st_nlink);
    printf("Owner UID    : %d\n", sobj.st_uid);
    printf("Owner GID    : %d\n", sobj.st_gid);
    
    time_t lastaccess = sobj.st_atimespec.tv_sec;
    time_t lastmodified = sobj.st_mtimespec.tv_sec;
    printf("Last access time: %s\n",ctime(&lastaccess));
    printf("Last modified time : %s\n",ctime(&lastmodified));

    if(S_ISREG(sobj.st_mode)){
        printf("File type: Regular File\n");
    }
    else if(S_ISDIR(sobj.st_mode)){
        printf("File type: Directory File\n");
    }
    else if(S_ISCHR(sobj.st_mode)){
        printf("File type: Character File\n");
    }
    else if(S_ISBLK(sobj.st_mode)){
        printf("File type: Block File\n");
    }
    else if(S_ISLNK(sobj.st_mode)){
        printf("File type: Symbolic link File\n");
    }
    else{
        printf("File type: Other\n");
    }

    printf("Permissions: \n");

    if (sobj.st_mode & S_IRUSR)
        printf("r");
    else
        printf("-");

    if (sobj.st_mode & S_IWUSR)
        printf("w");
    else
        printf("-");

    if (sobj.st_mode & S_IXUSR)
        printf("x");
    else
        printf("-");

    return 0;
}