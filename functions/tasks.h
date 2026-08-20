#include "task.h"
#ifndef TASKS_H
#define TASKS_H

void limpar(void);

void add_task(struct task **head, char **save);

void show_task(task *head);

void run_task(task **head, char **save, char *comp);

void run_listar();

//void work_dir(char *head);

#endif