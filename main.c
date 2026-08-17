#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "tasks.h"
#include <stdlib.h>


int main(){
    //if (*argv==NULL){
        struct task *t=NULL;
        char *save=NULL;
        char *tokn=NULL;
      
        char command[120];
        while(1){//apenas o commando, por enquanto
            printf("\nprocessflow> ");
            fgets(command,sizeof(command),stdin);
            char *compare = strtok_r(command," \n",&save);
            
            if (strcmp(compare,"task")==0){
                add_task(&t,&save);
            }
            if (strcmp(compare,"show")==0){
                show_task(t);
            }

            if (strcmp(compare,"exit")==0){
                exit(1);
            }
        }
    
    return 0;
}