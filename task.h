#include <stdbool.h>

#ifndef TASK_H
#define TASK_H

#ifdef __cplusplus
extern "C" {
#endif

static const char TASK_TYPE_ONCE = 1;
static const char TASK_TYPE_REPEAT = 2;

typedef struct task {
    char type;
    int interval;
    unsigned long then;

    void (*fn)(void);
} Task;

Task task_create(const char type, int interval, void (*fn)(void));

bool task_is_due(Task (*task), unsigned long *now);

void task_reset(Task (*task), unsigned long *now);

void task_exec(Task (*task));

bool task_run(Task (*task), unsigned long *now);

#ifdef __cplusplus
}
#endif

#endif
