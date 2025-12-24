#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include <sys/types.h>
#include <dirent.h>

int main(void)
{

    char DirectoryName[100];
    printf("Enter the Directory Name: \n");
    scanf("%s",DirectoryName);

    DIR* ptr = NULL; 
    struct dirent* dptr = NULL;
    ptr = opendir(DirectoryName);

    if(ptr == NULL){
        perror("Error: ");
        return 1;
    }

    while((dptr = readdir(ptr)) != NULL){
        if(strcmp(dptr -> d_name, ".") == 0 || strcmp(dptr -> d_name, "..") == 0){
            continue;
        }

        printf("%s\n",dptr -> d_name);
    }

    closedir(ptr);

    return 0;
}