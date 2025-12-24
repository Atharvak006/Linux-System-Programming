#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>       
#include <dirent.h>
#include<string.h>

int main(void)
{
    char DirectoryName[100], FileName[100];
    DIR* dptr = NULL;
    struct dirent* ptr = NULL;
    int found = 0;

    printf("Enter Directory name: ");
    scanf("%s",DirectoryName);

    printf("Enter File name: ");
    scanf("%s",FileName);

    dptr = opendir(DirectoryName);

    if(dptr == NULL){
        perror("Directory could not be opened");
        return 1;
    }

    while((ptr = readdir(dptr)) != NULL){

        if(strcmp(ptr -> d_name, FileName) == 0){
            found = 1;
            break;
        }
    }

    if(found == 1)
    {
        printf("File is present in the directory\n");
    }
    else{
        printf("File not present in the directory\n");
    }

    return 0;
}