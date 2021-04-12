#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "task.h"
#include "list.h"
#include "cpu.h"


struct node *head = NULL;
int tid = 0;

void add(char* name, int priority, int burst) //add function to add task variables
{
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->tid = tid++;
    task->priority = priority;
    task->burst = burst;

    insert(&head, task); //insert function to add node to list
}

void schedule()
{
    struct node *tmp;

    int quantum = 10; //assign quantum variable as 10 as quantum is 10ms
    while(head != NULL) //iterate until head is empty
    {
        tmp = head; //head is equal to the variable tmp as a temporary head
        for(struct node *tmp=head; tmp != NULL; tmp=tmp->next) //iterate through nodes until tmp is empty
        {
            if(tmp->task->burst >0) //if burst iterations are greater than 0 then process can continue
            {
                if(tmp->task->burst > 0 && tmp->task->burst <= quantum)
                {
                    run(tmp->task, tmp->task->burst); //run program
                    delete(&head, tmp->task); //processes are terminated
                }
                else
                {
                    run(tmp->task, quantum); //run program
                    tmp->task->burst -= quantum; //remove quantum from burst time
                }

            }
            else
            {
                delete(&head, tmp->task); //processes are terminated
            }
        }
    }
}

/* rr - https://www.geeksforgeeks.org/program-round-robin-scheduling-set-1/ */
/* rr - https://www.guru99.com/round-robin-scheduling-example.html */
/* rr - https://www.studytonight.com/operating-system/round-robin-scheduling */