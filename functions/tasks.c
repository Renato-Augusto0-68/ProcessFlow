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
            task *orig = *head;
            int i=0;
            task *storage[MAX_PIPES];
            comp = strtok_r(NULL," \n",save);
            while(aux!=NULL){
                if (strcmp(aux->nome,comp)==0){
                    storage[i]=aux;
                    aux = orig;
                    comp = strtok_r(NULL," \n",save);
                    i++;
                    if (comp==NULL){break;}
                }
                aux=aux->next;                
            }
            for(int g=0;g<i;g++){
                (storage[g])->id = fork();
                if((storage[g])->id==-1)
                    return;
                if((storage[g])->id!=0){
                    execvp((storage[g])->args[0],(storage[g])->args);
                }
                if((storage[g])->id!=0){
                    waitpid((storage[g])->id,NULL,0);
                }                
            }
        return;
        }else{
           while(strcmp(comp,aux->nome) && aux!=NULL){
                aux->id = fork();
                if (aux->id==0){
                    execvp(aux->args[0],aux->args);
                }
                if (aux->id!=0)
                    wait(NULL);
                    aux=aux->next;
                    comp = strtok_r(NULL," \n",save);
                
            }
        }
    }
    
    if (strcmp(comp, "pipe")==0){
        task *orig = *head;
        int i=0;
        comp = strtok_r(NULL," \n",save);
        task *storage[MAX_PIPES];
        //VOU ENCONTRAR OS N PROCESSOS. DPS QUE ENCONTRAR, ARMAZENAR, P DAI RODAR... NO CASO COMO SÃO STRINGS, PRA 'RASTREAR' É MAIS SIMPLES... MAS PRA ITERAR A LISTA ENCADEADA... A PERA AI 
        while(aux!=NULL){
        //ou seja aogra preciso poder mover pra onde precisa
            if (strcmp(aux->nome, comp)==0){
                storage[i]=aux;
                aux = orig;
                i++;
                comp = strtok_r(NULL," \n",save);
                if (comp==NULL){
                    break;
                }
            }
            aux = aux->next;
        }

        int numb;
        int fd[2];
        int prev_fd=-1;
        for (int g=0;g<i;g++){
            
            if (g!=(i-1)){
                if(pipe(fd)==-1){
                    return ;
                }
            }
            (storage[g])->id = fork();
            if ((storage[g])->id==-1)
                return ;

            if ((storage[g])->id==0){
                if (g>0){
                    dup2(prev_fd,STDIN_FILENO);
                    close(prev_fd);
                }
                if(g<i-1){
                    dup2(fd[1],STDOUT_FILENO);
                    close(fd[0]);
                    close(fd[1]); 
                } 
                if((execvp((storage[g])->args[0],(storage[g])->args))==-1){
                    printf("encerrando, ocorreu uma falha");
                    exit(-1);
                }
            }else{
                if (g>0){
                    close(prev_fd);  
                }
                if(g<i-1){
                    prev_fd=fd[0];
                    close(fd[1]);
                }
            }
        }
        close(fd[0]);
        close(fd[1]);
        for(int g=0;g<i;g++){
            waitpid(storage[g]->id,NULL,0);
        }
        return;
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

