#include "task.h"
#include "millis.h"
#include <stdlib.h>

Task task_create(const char type, int interval, void (*fn)(void)) {
    Task task;

    task.type = type;
    task.interval = interval;
    task.then = millis();
    task.fn = fn;

    return task;
}

bool task_is_due(Task (*task), unsigned long *now) {
    if (task->then == 0) {
        task_reset(task, now);
    }

    if (task->then > 0 && *now - task->then >= task->interval) {
        return true;
    }

    return false;
}

void task_reset(Task (*task), unsigned long *now) {
    task->then = *now;
}

void task_exec(Task (*task)) {
    task->fn();
}

bool task_run(Task (*task), unsigned long *now) {
    if (task_is_due(task, now)) {
        task_reset(task, now);
        task_exec(task);
        return true;
    }

    return false;
}