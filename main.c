#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <functions/tasks.h>

#include <stdlib.h>

void limpar(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

typedef struct task{
    char nome [60];
    char programa[60];
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
        aux->next=NULL;
        *head = aux;
    }else{
        char *parc = strtok_r(NULL," \n",save);
        strcpy(aux->nome,parc);
        char *parc2 = strtok_r(NULL," \n",save);
        strcpy(aux->programa,parc2);
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
            printf("%s %s\n",aux->nome,aux->programa);
            aux=aux->next;
        }
    }else{
        printf("\nNão há nada para mostrar");
    }
}


/*show - mostrar tasks
task - adicionar task

*/

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
            
            if (strcmp(compare,"task")==0){
                add_task(&t,&save);
            }

            if (strcmp(compare,"exit")==0){
                exit(1);
            }
        }
    
    return 0;
}