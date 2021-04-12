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
    while(tmp != NULL) //loop through every node
    {
        next = tmp->next; 
        tmp->next = previous;
        previous = tmp;
        tmp = next;
    }
    *head = previous;
}

void schedule() //Reverse linked list, run and calculate times for average waiting time and turn around time.
{
    //variables assigned
    int n = 0; 
    int total = 0;

    struct node *tmp=head; //assign linked list node and set pointer tmp to head as a temporary head

    int *waitTime = (int*)malloc(sizeof(int)); //array of wait times
    int *turnAroundTime = (int*)malloc(sizeof(int));//array of turnAround
    float awt;
    float atat;

    reverseList(&head); //reverse linked list function

    for(struct node *tmp=head; tmp != NULL; tmp=tmp->next) //iterate through linked list until tmp head is empty
    {
        run(tmp->task, tmp->task->burst); //run
        total++; //total number of process is calculated
    }

    int burstTime[100]; //make burstTime a list to collect burst time variables
    
    for(struct node *tmp=head; tmp != NULL; tmp=tmp->next) //loop through nodes
    {
        burstTime[n++] = tmp->task->burst; //add burst times to list
    }

    //times for first process
    waitTime[0] = 0;
    turnAroundTime[0] = burstTime[0];

    for(int i = 1; i < n; i++) //waiting time calculations
    {
        waitTime[i] = waitTime[i-1] + burstTime[i-1];
    }

    for(int i = 0; i < n; i++) //Turn Around Time calculations
    {
        turnAroundTime[i] = waitTime[i] + burstTime[i]; 
    }
    
    for(int i = 0; i < n; i++) //average waiting time (awt) and average turn around (avt) calculations
    {
        awt = awt + waitTime[i];
        atat = atat + turnAroundTime[i]; 
    }

    //averages calculated
    awt = awt/n;
    atat = atat/n;

    printf("\nTIMES:\n\nAverage Waiting Time = %.2f ms\nAverage Turnaround Time = %.2f ms\n", awt, atat);
    delete(&head, tmp->task);
}

//     Turn Around time = Exit time – Arrival time
//     Waiting time = Turn Around time – Burst time

/* Linked List Reverse - https://www.geeksforgeeks.org/data-structures-linked-list-question-5/ */
/* Linked Lsists -  https://www.cprogramming.com/tutorial/c/lesson15.html */
/* average waiting time - https://www.u-aizu.ac.jp/~yliu/teaching/os/lec10r.html */
/* awt - http://www.it.uu.se/edu/course/homepage/oskomp/vt07/lectures/scheduling_algorithms/handout.pdf */
/* awt and tat - https://www.geeksforgeeks.org/program-for-fcfs-cpu-scheduling-set-2-processes-with-different-arrival-times/ */
/* average wait and turn around time theory - https://www.studytonight.com/operating-system/first-come-first-serve */


/*                  JOAO PEREIRA                
                      19354106          */