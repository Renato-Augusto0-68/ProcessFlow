#ifndef TASK_H
#define TASK_H

typedef struct task{
    char nome [60];
    char programa[60];
    char argumentos [60];
    struct task *next;
}task;

#endif