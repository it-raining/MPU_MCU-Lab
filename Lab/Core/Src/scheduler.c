/*
 * scheduler.c
 *
 *  Created on: Nov 25, 2024
 *      Author: HP
 */
#include "scheduler.h"
Tasks_t tasks;

static void Reorder_Tasks(void) {
	uint32_t sumDelay = 0;
	TaskNode *current = tasks.head;
	for (int i = 0; i < tasks.nTasks && current; i++) {
		current->delay -= sumDelay;
		sumDelay += current->delay;
		current = current->next;
	}
}
int is_avail(TaskNode *task) {
	return (task->runMe == 1);
}
void Scheduler_Init(void) {
	if (!tasks.head) {
		tasks.head = NULL;
		tasks.nTasks = 0;
	} else {
		TaskNode *current = tasks.head;
		for (uint8_t i = 0; i < tasks.nTasks; i++) {
			TaskNode *tmp = current;
			current = current->next;
			free(tmp);
		}
	}
}

uint32_t Scheduler_Add_Task(void (*pF)(void), const uint32_t DELAY,
		const uint32_t PERIOD) {
	TaskNode *newTask = (TaskNode*) malloc(sizeof(TaskNode));
	if (tasks.nTasks >= MAX_TASKS || !newTask)
		return ADD_TASK_ERROR;

	newTask->pTask = pF;
	newTask->delay = DELAY;
	newTask->period = PERIOD;
	newTask->runMe = 0;
	newTask->TaskID = tasks.nTasks + 1;
	newTask->next = NULL;

	if (!tasks.head || DELAY < tasks.head->delay) {
		newTask->next = tasks.head;
		tasks.head = newTask;
	} else {
		uint32_t sumDelay = 0;
		TaskNode *current = tasks.head; //at least one task
		TaskNode *prev = NULL;
		for (int i = 0; i < tasks.nTasks; i++) {
			sumDelay += current->delay;
			if (!current) {
				newTask->delay = DELAY - sumDelay;
				prev->next = newTask;
			}
			if (sumDelay >= DELAY) {
				newTask->delay = DELAY - (sumDelay - current->delay);
				current->delay -= newTask->delay;
				newTask->next = current;
				if (prev) {
					prev->next = newTask;
				}
				break;
			}
			prev = current;
			current = current->next;
		}
	}
	tasks.nTasks++;
	return newTask->TaskID;
}

void Scheduler_Update(void) {
	if (!tasks.head)
		return;
	tasks.head->delay--;
	if (tasks.head->delay == 0) {
		tasks.head->runMe = 1;
	}
}

void Scheduler_Dispatch_Tasks(void) {
	if (!tasks.head)
		return;
	TaskNode *task = tasks.head;
	if (is_avail(task)) {
		task->pTask();
		if (task->period > 0) {
			task->delay = task->period;
			tasks.head = task->next;
			tasks.nTasks--;
			Scheduler_Add_Task(task->pTask, task->delay, task->period);
			free(task);
		} else {
			tasks.head = task->next;
			free(task);
			tasks.nTasks--;
		}
	}

	Reorder_Tasks();
}

uint8_t Scheduler_Remove_Task(uint32_t TaskID) {
	if (!tasks.head)
		return NOT_VALID_TASK_ID;

	TaskNode *current = tasks.head, *prev = NULL;

	for (int i = 0; i < tasks.nTasks; i++) {
		if (current->TaskID == TaskID) {
			if (prev) {
				prev->next = current->next;
			} else {
				tasks.head = current->next;
			}
			free(current);
			tasks.nTasks--;
			return 1; // Task successfully removed
		}
		prev = current;
		current = current->next;
	}
	return NOT_VALID_TASK_ID;
}

