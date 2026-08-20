#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "task.h"
#include <stdlib.h>
#define MAX_PIPES 4

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
                wait(NULL);
                aux=aux->next;
                comp = strtok_r(NULL," \n",save);
                
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
        task *orig = *head;
        int i=0;
        task *storage[MAX_PIPES];
        //VOU ENCONTRAR OS N PROCESSOS. DPS QUE ENCONTRAR, ARMAZENAR, P DAI RODAR... NO CASO COMO SÃO STRINGS, PRA 'RASTREAR' É MAIS SIMPLES... MAS PRA ITERAR A LISTA ENCADEADA... A PERA AI 
        while(aux!=NULL){
        //ou seja aogra preciso poder mover pra onde precisa
            if (strcmp(aux->nome, comp)==0){
                storage[i]=aux;
                aux = orig;
                comp = strtok_r(NULL," \n",save);
                i++;
            }
            aux = aux->next;
        }
        int numb;
        int fd[2];
        for (int g=0;g<i;g++){
            if(pipe(fd)==-1){
                return 1;
            }
            int id = (storage[g])->id =fork();
            if (id==-1)
                return 2;

            if (id==0 && g!=(i-1)){
                dup2(fd[1],STDOUT_FILENO);

                close(fd[0]);
                close(fd[1]);            
                int resp = execvp((storage[g])->args[0],(storage[g])->args);
               
            }else if(id==0){
                dup2(fd[0],STDIN_FILENO);

                close(fd[0]);
                close(fd[1]);            
                int resp = execvp((storage[g])->args[0],(storage[g])->args);
            }
        }
        for(int g=0;g<i;g++){
            close(fd[0]);
            close(fd[1]);
        }
        for(int g=0;g<i;g++){
            waitpid(storage[g],NULL,0);
        }
    }
    if (strcmp(comp,"pipe")!=0){   
        while(aux!=NULL){
        //ou seja aogra preciso poder mover pra onde precisa
            if (strcmp(aux->nome, comp)==0){
                aux->id = fork();
                break;
            }
            aux = aux->next;
        }
        if(aux!=NULL){
            if (aux->id==0){
               int resp = execvp(aux->args[0], aux->args);
            //while(waitpid(aux->id,NULL,WNOHANG)){ int resp = execvp(aux->args[0], aux->args);}
            }else{wait(NULL);}
        }else{
            printf("processo não existe, não é possível executar-lo\n");
        }
    }
}

void run_listar(char **head){
    char *arg[] ={"/bin/ls","ls"," -l"};  
    int resp = execvp(arg[0],arg);
}

