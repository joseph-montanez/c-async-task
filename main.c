#include "millis.h"
#include "task.h"
#include "task_manager.h"
#include <stdio.h>

TaskManager *manager;
TaskNode *taskNode1;

unsigned long cycles = 0;

void green_led_off() {
    printf("GREEN OFF\n");

    task_manager_delete_task(manager, taskNode1);
}

void green_led_on() {
    printf("GREEN ON\n");

    taskNode1 = task_manager_add_task(manager, task_create(TASK_TYPE_REPEAT, 100, green_led_off));
}

void red_led_on() {
    printf("RED ON\n");
}

void tick_cycles() {
    printf("executed %lu cycles in one second\n", cycles);
    cycles = 0;
}


int main(int argc, char* argv[]) {
    unsigned long now;

    manager = task_manager_create();
    task_manager_add_task(manager, task_create(TASK_TYPE_REPEAT, 150, green_led_on));
    task_manager_add_task(manager, task_create(TASK_TYPE_REPEAT, 1000, tick_cycles));
    task_manager_add_task(manager, task_create(TASK_TYPE_ONCE, 5000, red_led_on));

    millis_start();

    while (1) {
        now = millis();
        task_manager_run(manager, &now);

        cycles++;
    }

    return 0;
}