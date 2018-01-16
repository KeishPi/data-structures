/*
 * Assignment 5
 * Name: Keisha Arnold
 * Description: Use the heap-based Priority Queue to implement a to-do list application.
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/*
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/*
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
	while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/*
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
	char filename[100];
	char taskName[100];
	char *nullPtr;
	Task *newTask;
	Task *firstTask;
	int priority;
	FILE *filePtr;
	DynamicArray *myList = list;
	
	if(command == 'l') {	//load to-do list from a file
		printf("Please enter the filename: ");
		//read filename from keyboard
		if(fgets(filename, sizeof(filename), stdin) != NULL) {
			//remove pesky trailing newline
			nullPtr = strchr(filename, '\n');
			if(nullPtr)
				*nullPtr = '\0';
		}
		//open the file
		filePtr = fopen(filename, "r"); //"r" = read
		if(filePtr == NULL)
			fprintf(stderr, "Cannot open %s\n", filename);
		else {
		//load to-do list from the file
		listLoad(myList, filePtr);
		//close the file
		fclose(filePtr);
		printf("The list has been loaded from file successfully.\n\n");
		}
	}
	
	else if(command == 's') { //save to-do list to a file
		if(dySize(list) > 0) { //check that list is not empty
			printf("Please enter the filename: ");
			//read filename from keyboard
			if(fgets(filename, sizeof(filename), stdin) != NULL) {
				//remove pesky trailing newline
				nullPtr = strchr(filename, '\n');
				if(nullPtr)
					*nullPtr = '\0';
			}
			//open the file
			filePtr = fopen(filename, "w"); //"w" = write
			if(filePtr == NULL)
				fprintf(stderr, "Cannot open %s\n", filename);
			//save to-do list to file
			listSave(myList,filePtr);
			//close the file
			fclose(filePtr);
			printf("Your list has been saved to the file successfully.\n\n");
		} else
			printf("Your list is empty.\n\n");
	}
	
	else if(command == 'a') { //add a new task
		printf("Please enter a task name: ");
		if(fgets(taskName, sizeof(taskName), stdin) != NULL) {
			//remove pesky trailing newline
			nullPtr = strchr(taskName, '\n');
			if(nullPtr)
				*nullPtr = '\0';
		}
		do {
			printf("Please enter a priority for this task (0-999): ");
			scanf("%d", &priority);
		} while(!(priority >= 0 && priority <= 999));
		
		//clear trailing newline
		while(getchar() != '\n');
		//make a new task and add it to the list (heap)
		newTask = taskNew(priority, taskName);
		dyHeapAdd(myList, newTask, taskCompare);
		printf("The task '%s' has been added to your list.\n\n", taskName);
		
	}
	
	else if(command == 'g') { //get the first task from the list
		if(dySize(list) > 0) { //check that list is not empty
			firstTask = (Task*)dyHeapGetMin(myList);
			printf("The first task is: %s\n\n", firstTask -> name);
		} else
			printf("Your list is empty.\n\n");
	}
	
	else if(command == 'r') { //remove the first task from the list
		if(dySize(list) > 0) { //check that list is not empty
				firstTask = (Task*)dyHeapGetMin(myList);
				dyHeapRemoveMin(myList, taskCompare);	//remove the root
				printf("The first task '%s' has been removed from your list.\n\n", firstTask -> name);
			free(firstTask);
		} else
			printf("Your list is empty.\n\n");
	}
	
	else if(command == 'p') { //print the list
		if(dySize(list) > 0)  //check that list is not empty
			listPrint(myList);
		else
			printf("Your list is empty.\n\n");
	}
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
	//I added this while loop to fix memory leaks!
	while(dySize(list) > 0) {
		taskDelete(dyHeapGetMin(list));
		dyHeapRemoveMin(list, taskCompare);
	}
    dyDelete(list);
    return 0;
}
