/*
 * scheduler.c
 *
 *  Created on: Nov 25, 2024
 *      Author: HP
 */
#include "scheduler.h"
Tasks_t tasks;

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
		tasks.head = NULL;
	}
}

uint32_t Scheduler_Add_Task(void (*pF)(void), uint32_t taskID, uint32_t DELAY,
		uint32_t PERIOD) {
	DELAY = DELAY / TICK;
	PERIOD = PERIOD / TICK;
	TaskNode *newTask = (TaskNode*) malloc(sizeof(TaskNode));
	if (tasks.nTasks >= MAX_TASKS || !newTask)
		return ADD_TASK_ERROR;
	newTask->pTask = pF;
	newTask->delay = DELAY;
	newTask->period = PERIOD;
	newTask->runMe = 0;
	newTask->TaskID = taskID;
	newTask->next = NULL;

	if (!tasks.head || DELAY <= tasks.head->delay) {
		// add at head
		if (tasks.head) {
			tasks.head->delay -= DELAY;
		}
		newTask->next = tasks.head;
		tasks.head = newTask;
	} else {
		// add at middle
		uint32_t sumDelay = 0;
		TaskNode *current = tasks.head;
		TaskNode *prev = NULL;
		for (int i = 0; i < tasks.nTasks; i++) {
			sumDelay += current->delay;
			if (sumDelay > DELAY) {
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
		// add at bottom
		if (!current && prev) {
			newTask->delay = DELAY - sumDelay;
			prev->next = newTask;
		}
	}
	tasks.nTasks++;
	return newTask->TaskID;
}

void Scheduler_Update(void) {
	if (!tasks.head)
		return;
	if (tasks.head->delay <= 0) {
		tasks.head->runMe = 1;
	} else
		tasks.head->delay--;
}

void Scheduler_Dispatch_Tasks(void) {
	if (!tasks.head)
		return;
	TaskNode *task = tasks.head;
	if (is_avail(task)) {
		task->pTask();
		if (task->period > 0) {
			Scheduler_Add_Task(task->pTask, task->TaskID, task->period * TICK,
					task->period * TICK);
		}
//		tasks.head = task->next;
//		free(task);
		Scheduler_Remove_Task(task->TaskID);
	}
}

uint8_t Scheduler_Remove_Task(uint32_t TaskID) {
	if (!tasks.head)
		return NOT_VALID_TASK_ID;
	TaskNode *current = tasks.head, *prev = NULL;

	for (uint32_t i = 0; i < tasks.nTasks; i++) {
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

