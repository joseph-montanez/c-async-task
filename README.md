# c-async-task

A simple C library to do intervaled / once off async work in a loop. Current using for Arduino type hardware, using a single linked list to manage a dynamic array of tasks.

## Example

	#include "task.h"
	#include "task_manager.h"

	TaskManager *manager;
	const byte BLUE_LED = 3;

	void blue_led_off() {
	    digitalWrite(BLUE_LED, LOW);
	}

	void blue_led_on() {
	    digitalWrite(BLUE_LED, HIGH);

	    //-- Turn off LED in 1 second, and then the task should be deleted after running
	    task_manager_add_task(manager, task_create(TASK_TYPE_ONCE, 1000, blue_led_off));
	}


	void setup() {

	    //-- Create the task manager
	    manager = task_manager_create();

	    task_manager_add_task(manager, task_create(TASK_TYPE_REPEAT, 1000, blue_led_on));

	}

	void loop() {
	    now = millis();
	    task_manager_run(manager, &now);
	}