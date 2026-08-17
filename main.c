#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <functions/tasks.h>

#include <stdlib.h>

typedef struct task{
    char nome [60];
    char programa[60];
    struct task *next;
}task;

void add_task(struct task **head, char *comando){
    struct task *aux = *head;
    if (aux==NULL){
        fgets(aux->nome,sizeof(aux->nome),stdin);
        fgets(aux->programa,sizeof(aux->programa),stdin);
        aux->next=NULL;
    }else{
        struct task* t2=(task *)malloc(sizeof(task));
        fgets(t2->nome,sizeof(t2->nome),stdin);
        fgets(t2->programa,sizeof(t2->programa),stdin); 
        t2->next=NULL;
        while(aux->next!=NULL){
            aux=aux->next;
        }
        aux->next=t2;
    }
}






int main(){
    //if (*argv==NULL){
        struct task *t=NULL;
        char command[120];
        while(1){
            printf("\nprocessflow> ");
            fgets(command,sizeof(command),stdin);
            
            if (*command==116){
                char aux[120];
                char aux2[120];
                for(int i=0;i<strlen(command);i++){
                    if(command[i]==32 ){
                        strncpy(aux,command,i);
                    }
                    
                }
                for(int i=0;i<strlen(aux);i++){
                    printf("%c %d\n",aux[i],i);}
                //add_task(,&t);
                printf("\nTask criada com sucesso");
            }



            if (*command==48){
                exit(1);
            }
        }
    
    return 0;
}