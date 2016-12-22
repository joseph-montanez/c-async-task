#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tasknode {
    Task value;
    struct tasknode *next;
} TaskNode;

struct taskmanager {
    TaskNode *head;


};

typedef struct taskmanager TaskManager;

TaskManager* task_manager_create();

TaskNode* task_manager_last_task(TaskManager (*manager));

TaskNode* task_manager_add_task(TaskManager (*manager), Task task);

bool task_manager_delete_task(TaskManager (*manager), TaskNode (*taskNode));

void task_manager_run(TaskManager (*manager), unsigned long *now);

#ifdef __cplusplus
}
#endif

#endif