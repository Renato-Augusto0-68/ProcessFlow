#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "task.h"
#include "tasks.h"
#include <stdlib.h>
/*
void run_terminal(task **t,char *compare, char **save){

            if (strcmp(compare,"task")==0){
                add_task(t,&save);
            }
            if (strcmp(compare,"show")==0){
                show_task(t);
            }
            if (strcmp(compare,"run")==0){
                char *comp2 = strtok_r(NULL," \n",save);
                run_task(t,&save, comp2);
            }
            if(strcmp(compare,"workdir")==0){
                char *comp2 = strtok_r(NULL," \n",&save);
                work_dir(comp2);
            }

            if (strcmp(compare,"exit")==0){
                exit(1);
            }
            wait(NULL);
}
*/
void work_dir(char *comp2){
        char s[100];
        printf("Estamos em: %s\n",getcwd(s, 100));
        int resultado = chdir(comp2);
        if (!resultado){
            printf("Mudança de diretório bem sucedida\n");
            printf("Agora estamos em: %s\n",getcwd(s, 100));
        }else{
            printf("ocorreu uma falha em mudar diretório, encerrando por segurança\n");
            return;
        }
    }
