/* 
 * Header file for the priority queue to be used with tmsim.c
 * Solves CS149 Homework#3
 * @author Tyler Jones
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "buyers.h"

typedef struct PriorityQueue
{
    int capacity;//Total number of Customers
    int size;//Number of customers in queue
    int front;//Index of first customer
    int rear;//Index of last customer
    struct Buyers *buyers;//Pointer to customer array
} PriorityQueue;

//List all functions
PriorityQueue * createPriorityQueue(int numOfBuyers); //Create the priority queue
int isEmpty(PriorityQueue *PQ); //Check if priority queue is empty
struct Buyers peek(PriorityQueue *PQ); //Look at first element of priority queue
struct Buyers poll(PriorityQueue *PQ); //Remove an element from the priority queue
void add(PriorityQueue *PQ, struct Buyers buyer); //Add an element to the priority queue

#endif /* PRIORITYQUEUE_H */
