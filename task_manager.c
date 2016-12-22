#include "task_manager.h"
#include <stdlib.h>

#define Nullptr(type) (type *)0

TaskManager* task_manager_create() {
    TaskManager *manager = (TaskManager*) malloc(sizeof(TaskManager));

    manager->head = Nullptr(TaskNode);

    return manager;
}


TaskNode* task_manager_last_task(TaskManager (*manager)) {
    TaskNode *node = manager->head;
    while (node != Nullptr(TaskNode)) {
        if (node->next == Nullptr(TaskNode)) {
            break;
        }
        node = node->next;
    }

    return node;
}

TaskNode* task_manager_add_task(TaskManager (*manager), Task task) {
    TaskNode *taskNode = (TaskNode*) malloc(sizeof(TaskNode));

    taskNode->value = task;
    taskNode->next = Nullptr(TaskNode);

    if (manager->head == Nullptr(TaskNode)) {
        manager->head = taskNode;
    } else {
        TaskNode *last_tasknode = task_manager_last_task(manager);

        if (last_tasknode != Nullptr(TaskNode)) {
            last_tasknode->next = taskNode;
        }
    }

    return taskNode;
}

bool task_manager_delete_task(TaskManager *manager, TaskNode *taskNode) {
    if (taskNode == Nullptr(TaskNode)) {
        return false;
    }

    TaskNode *node = manager->head;

    bool deleted = false;

    while (node != Nullptr(TaskNode)) {
        if (node->next == Nullptr(TaskNode)) {
            break;
        }
        //-- If the task node is the head
        else if (node == taskNode) {
            if (taskNode->next != Nullptr(TaskNode)) {
                manager->head = taskNode->next;
            } else {
                manager->head = Nullptr(TaskNode);
            }
            deleted = true;
            break;
        }
        else if (node->next == taskNode) {
            if (taskNode->next != Nullptr(TaskNode)) {
                node->next = taskNode->next;
            } else {
                node->next = Nullptr(TaskNode);
            }
            deleted = true;
            break;
        }
        node = node->next;
    }

    if (deleted) {
        free(taskNode);
    }

    return deleted;
}

void task_manager_run(TaskManager (*manager), unsigned long *now) {
    TaskNode *node = manager->head;
    TaskNode *node_next;
    while (node != Nullptr(TaskNode)) {
        bool ran = task_run(&node->value, now);

        if (node->value.type == TASK_TYPE_ONCE && ran) {
            node_next = node->next;
            task_manager_delete_task(manager, node);
            node = node_next;
        } else {
            node = node->next;
        }

    }
}