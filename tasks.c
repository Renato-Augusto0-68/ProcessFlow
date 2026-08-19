#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "task.h"
#include <stdlib.h>

void limpar(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void add_task(struct task **head, char **save){
    char empt[]=" ";
    struct task *aux = (task *)malloc(sizeof(task));
    
    if (*head==NULL){
        char *parc = strtok_r(NULL," \n",save);
        strcpy(aux->nome,parc);
        char *parc2 = strtok_r(NULL," \n",save);
        int i=0;
        while(parc2!=NULL && i < MAX_ARGS - 1){

            aux->args[i]=strdup(parc2);
            i++;
            parc2 = strtok_r(NULL," \n",save);
        }
        aux->args[i]=NULL;
        aux->next=NULL;
        *head = aux;
    }else{
        char *parc = strtok_r(NULL," \n",save);
        strcpy(aux->nome,parc);
        char *parc2 = strtok_r(NULL," \n",save);
        int i=0;
        while(parc2!=NULL && i < MAX_ARGS - 1){
            
            aux->args[i]=strdup(parc2);
            i++;
            parc2 = strtok_r(NULL," \n",save);
        }
        aux->args[i]=NULL;
        aux->next=NULL;
        struct task *head_aux = *head;
        while(head_aux->next!=NULL){
            head_aux=head_aux->next;
        }
        head_aux->next=aux;
    }
}

void show_task(struct task *head){
    if (head!=NULL){
        struct task *aux=head;
        while(aux!=NULL){      
            printf("Processo: %s Ação: %s\n",aux->nome,aux->args);
            aux=aux->next;
        }
    }else{
        printf("\nNão há nada para mostrar");
    }
}

void run_task(struct task **head, char **save, char *comp){
    task *aux = *head;

    if (strcmp(comp,"sequential")==0 ^ (strcmp(comp,"parallel")==0)){
        if (strcmp(comp,"sequential")==0){
            while(strcmp(comp,aux->nome) && aux!=NULL){
                aux->id = fork();
                if (aux->id==0){
                    execvp(aux->args[0],aux->args);
                    exit(0);
                }
                aux=aux->next;
                comp = strtok_r(NULL," \n",save);~
                wait(NULL);
            }
        }else{
            while(strcmp(comp,aux->nome) && aux!=NULL){
                aux->id = fork();
                if (aux->id==0){
                    execvp(aux->args[0],aux->args);
                    waitpid(aux->id,NULL,WNOHANG);
                }
                aux=aux->next;
                comp = strtok_r(NULL," \n",save);~
                wait(NULL);
            }
        }
    }
    if (strcmp(comp, "pipe")==0){
        // a parte de pipe
    }
    if (strcmp(comp,"sequential")!=0 && (strcmp(comp,"parallel")!=0)){
        while(aux!=NULL){
        //ou seja aogra preciso poder mover pra onde precisa
            if (strcmp(aux->nome, comp)==0){
                aux->id = fork();
                break;
            }
            aux = aux->next;
        }
        if(aux!=NULL){
            while(waitpid(aux->id,NULL,WNOHANG)){ int resp = execvp(aux->args[0], aux->args);}
        }else{
            printf("processo não existe, não é possível executar-lo\n");

        }
    }
}

void run_listar(char **head){
    char *arg[] ={"/bin/ls","ls"," -l"};  
    int resp = execvp(arg[0],arg);
}
