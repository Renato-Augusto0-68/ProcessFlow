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
            printf("%s\n%s\n",aux->nome,aux->args);
            aux=aux->next;
        }
    }else{
        printf("\nNão há nada para mostrar");
    }
}

void run_task(struct task **head, char **save){
    task *aux = *head;
    //char *parc = strtok_r(NULL," \n",&save);
    //if( strcmp(aux->nome,parc)==0){

    int resp = execvp(aux->args[0], aux->args);
    //}
}

void run_listar(){
    int resp = execlp("/bin/ls"," -l");
}