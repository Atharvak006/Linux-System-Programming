#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(void)
{
    char Filename[100];
    char Mode[10];

    int iret = 0;
    int flag = 0;
    printf("Enter the file name:\n");
    scanf("%s", Filename);

    printf("Enter the mode:\n");
    scanf("%s", Mode);

    /*
        apan direct 4 2 1 pn use kru shakto
        pn it is not recomended, mhanun tyache equivalent flags use krto
    */
    if(strcmp(Mode,"read")== 0){
        flag = R_OK; // read chi permission (4)
    } 
    else if(strcmp(Mode,"write") == 0){
        flag = W_OK;  // write chi permission (2)
    }  
    else if(strcmp(Mode,"execute") == 0){
        flag = X_OK;    // execute chi permission (1);
    }
    else{
        printf("Invalid choice\n");
        return -1;
    }

    iret = access(Filename,flag);

    if(iret == 0){
        printf("File is accessible\n");
    }
    else{
        printf("File is not accessible\n");  
        perror("Reason: ");
        return 1; 
    }

    return 0;
}