#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "functions/tasks.h"
#include "functions/task.h"
#include "functions/terminal.h"
#include <stdlib.h>


int main(){
    //if (*argv==NULL){
        struct task *t=NULL;
        char *save=NULL;
        char *tokn=NULL;
        char command[220];
        while(1){
            printf("\nprocessflow> ");
            fgets(command,sizeof(command),stdin);
            char *compare = strtok_r(command," \n",&save);
            
            if (strcmp(compare,"task")==0){
                add_task(&t,&save);
            }
            if (strcmp(compare,"show")==0){
                show_task(t);
            }
            if (strcmp(compare,"run")==0){
                char *comp2 = strtok_r(NULL," \n",&save);
                run_task(&t,&save, comp2);
            }
            if(strcmp(compare,"workdir")==0){
                char *comp2 = strtok_r(NULL," \n",&save);
                work_dir(comp2);
            }
            if(strcmp(compare," ")==0){
                printf("Falha, digite algum comando para executar");
                
            }
            if (strcmp(compare,"exit")==0){
                exit(1);
            }
            wait(NULL);
        }
    
    return 0;
}