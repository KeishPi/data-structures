/*
 * Assignment 5
 * Name: Keisha Arnold
 * Description: Use the heap-based Priority Queue to implement a to-do list application.
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return the new task
 */
Task* taskNew(int priority, char* name)
{
    // FIXME: implement
	struct Task *newTask = malloc(sizeof(struct Task));
	strcpy(newTask -> name, name);
	newTask -> priority = priority;
	
	return newTask;
}

/*
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/*
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left   Task pointer.
 * @param right  Task pointer.
 * @return 
 */
int taskCompare(void* left, void* right)
{
    // FIXME: implement
	struct Task* l;
	struct Task* r;
	l = (struct Task*)left;
	r = (struct Task*)right;
	
	if(l -> priority < r -> priority)
		return -1;
	else if(l -> priority > r -> priority)
		return 1;
	else  // left's priority == right's priority
		return 0;
}

/*
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("(%d, %s)", task->priority, task->name);
}
