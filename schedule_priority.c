#include <stdio.h>
#include <stdlib.h>
#include "schedulers.h"
#include "task.h"
#include "list.h"
#include "cpu.h"

//SJF shortest burst
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

void reverseList(struct node** head) //Revese function is created to reverse order of linked list so it is ordered in ascendng order
{
    struct node* tmp = *head;
    struct node* next;
    struct node* previous = NULL;
    while(tmp != NULL)
    {
        next = tmp->next;  
        tmp->next = previous;   
        previous = tmp;
        tmp = next;
    }
    *head = previous;
}

void schedule()
{

    int num = 0;

    struct node *tmp=head;

    int *waitTime = (int*)malloc(sizeof(int)); //array of wait times
    int *turnAroundTime = (int*)malloc(sizeof(int));//array of turnAround
    float awt;
    float atat;
    reverseList(&head); // code to organise list to correct order

    // sort by burst time

    struct node *main = head; //assign head a node, in this case we assign main as we are still using main head
    struct node *swap = NULL; //assign a node as swap as it will be utilized to swap thrpugh nodes
    Task *temp;
    
    while(main != NULL) //run until main is empty
    {  
        swap = main->next;
                  
        while(swap != NULL) //run until swap is empty
        {
            if(main->task->priority > swap->task->priority) //if swap node priority is less than the main node priority
            {  
                temp = main->task; //temporary variable is assigned to the main head task
                main->task = swap->task; //main task now becomes swap task
                swap->task = temp; //swap node becmones temp 
            }  
            swap = swap->next; //move to new swap node
        }  
        main = main->next; //move to next main head node
    }   

    for(struct node *tmp=head; tmp != NULL; tmp=tmp->next)
    {
        run(tmp->task, tmp->task->burst);
        //delete(&head, tmp->task);
    }

    int burstTime[100]; //make burstTime a list to collect burst time variables
    
    for(struct node *tmp=head; tmp != NULL; tmp=tmp->next) //loop through nodes
    {
        burstTime[num++] = tmp->task->burst; //add burst times to list
    }

    //times for first process
    waitTime[0] = 0;
    turnAroundTime[0] = burstTime[0];

    for(int i = 1; i < num; i++) //waiting time calculation
    {
        waitTime[i] = waitTime[i-1] + burstTime[i-1]; 
    }

    for (int i = 0; i < num; i++) //Turn Around Time calculation
    {
        turnAroundTime[i] = waitTime[i] + burstTime[i]; 
    }
    
    for(int i = 0; i < num; i++)
    {
        awt = awt + waitTime[i];
        atat = atat + turnAroundTime[i]; 
    }
    //averages calculated
    awt = awt/num;
    atat = atat/num;

    printf("\nTIMES:\nAverage Waiting Time = %.2f ms\nAverage Turnaround Time = %.2f ms\n", awt, atat);
    delete(&head, tmp->task);//terminate processes
}

//Average Waiting Time is all waiting times added together

/* sort linked list - https://www.javatpoint.com/program-to-sort-the-elements-of-the-singly-linked-list */
/* avgwt - https://www.javatpoint.com/os-non-preemptive-priority-scheduling */


/*                  JOAO PEREIRA                
                      19354106          */