#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <functions/tasks.h>





int main(){
    //if (*argv==NULL){

        char command[120];
        while(1){
            printf("processflow> ");
            fgets(command,sizeof(command),stdin);
            
            if (*command==116){
                
            }



            if (*command==0){
                exit(1);
            }
        }
    
    return 0;
}