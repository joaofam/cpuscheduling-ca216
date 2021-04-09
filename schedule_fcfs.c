#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "task.h"
#include "list.h"
#include "cpu.h"
//Linked List working
//Reverse linked list 

struct node *head = NULL;
int tid = 0;


void add(char* name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->tid = tid++;
    task->priority = priority;
    task->burst = burst;

    insert(&head, task);
}

void reverse(struct node** head) //Revese function is created to reverse order of linked list so it is ordered in ascendng order
{
    struct node* prev = NULL;
    struct node* current = *head;
    struct node* next;
    while (current != NULL)
    {
        next = current->next;  
        current->next = prev;   
        prev = current;
        current = next;
    }
    *head = prev;
}

void schedule() //Reverse and run the list
{
    reverse(&head);
    for(struct node *tmp=head; tmp != NULL; tmp=tmp->next)
    {
        run(tmp->task, tmp->task->burst);
        delete(&head, tmp->task);
    }
}






/* Linked List Reverse - https://www.geeksforgeeks.org/data-structures-linked-list-question-5/ */