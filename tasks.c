#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include <stdlib.h>

void limpar(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

typedef struct task{
    char nome [60];
    char programa[60];
    char argumentos [60];
    struct task *next;
}task;

void add_task(struct task **head, char **save){
    char empt[]=" ";
    struct task *aux = (task *)malloc(sizeof(task));
    if (*head==NULL){
        char *parc = strtok_r(NULL," \n",save);
        strcpy(aux->nome,parc);
        char *parc2 = strtok_r(NULL," \n",save);
        strcpy(aux->programa,parc2);
        char *parc3 = strtok_r(NULL," \n",save);
        strcpy(aux->argumentos,parc3);
        aux->next=NULL;
        *head = aux;
    }else{
        char *parc = strtok_r(NULL," \n",save);
        strcpy(aux->nome,parc);
        char *parc2 = strtok_r(NULL," \n",save);
        strcpy(aux->programa,parc2);
        char *parc3 = strtok_r(NULL," \n",save);
        strcpy(aux->argumentos,parc3);
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
            printf("%s\n%s\n%s\n",aux->nome,aux->programa, aux->argumentos);
            aux=aux->next;
        }
    }else{
        printf("\nNão há nada para mostrar");
    }
}

void run_task(struct task **head, char **save){
    task *aux = *head;
    char *parc = strtok_r(NULL," \n",save);
    while(aux!=NULL && strcmp(aux->nome,parc)!=0){
        aux=aux->next;
    }
    int resp = execlp(aux->programa,aux->argumentos);
}

void run_listar(){
    int resp = execlp("/bin/ls","-l");
}