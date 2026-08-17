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
    if (*argv==NULL){




        char *command=NULL;
        while(1){
            printf("processflow> ");
            fgets(command,"%s",stdin);


        }


    }



}