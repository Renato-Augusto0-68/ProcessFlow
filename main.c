#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct task{
    char nome [60];
    char programa[60];
    struct task *next;
}task;




int main(){
    //if (*argv==NULL){

        char command[120];
        while(1){
            printf("processflow> ");
            fgets(command,sizeof(command),stdin);
            printf("%s",command);
            if (*command==97){
                exit(1);
            }
        }
    
    return 0;
}