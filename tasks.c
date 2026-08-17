#include <stdio.h>
#include <stdlib.h>

typedef struct task{
    char nome [60];
    char programa[60];
    struct task *next;
}task;

void fill_task(struct task **head){
    struct task *aux = *head;
    if (aux==NULL){
        fgets(aux->nome,sizeof(aux->nome),stdin);
        fgets(aux->programa,sizeof(aux->programa),stdin);
        aux->next=NULL;
        
    else{} 


}


void add_task(){
    struct task* t1=(task *)malloc(sizeof(task));
    
    t1->next = NULL;


}