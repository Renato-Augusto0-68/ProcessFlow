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
    aux->id = fork();
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
           
            printf("Processo: %s Ação: %s PID: %d\n",aux->nome,aux->args,aux->id);
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

        }else{

        }


    }
    
    if (strcmp(comp,"sequential")!=0 && (strcmp(comp,"parallel")!=0)){
        while(aux!=NULL){
        //ou seja aogra preciso poder mover pra onde precisa
            if (strcmp(aux->nome, comp)==0 && aux->id==0){
                int resp = execvp(aux->args[0], aux->args);
            }
            if (aux->id!=0){
                printf("processo %s acabou\n",aux->nome);
            }
            aux->id=waitpid(aux->id,NULL,WNOHANG);
            aux = aux->next;
            
        }
    }
}

void run_listar(char **head){
    char *arg[] ={"/bin/ls","ls"," -l"};  
    int resp = execvp(arg[0],arg);
}