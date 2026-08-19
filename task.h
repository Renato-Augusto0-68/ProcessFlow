#include <unistd.h>
#ifndef TASK_H
#define TASK_H
#define MAX_ARGS 16

typedef struct task{
    char nome [60];
    char *args[MAX_ARGS];
    pid_t id;
    struct task *next;
}task;

#endif