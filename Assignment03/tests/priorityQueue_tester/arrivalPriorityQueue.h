#ifndef ARRIVALPRIORITYQUEUE_H
#define ARRIVALPRIORITYQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "buyers.h"

// Header file for the arrival priority queue to be used with tmsim.c
// Solves CS149 Homework#3
// @author Tyler Jones
typedef struct PriorityQueue
{
    int capacity;//Total number of Customers
    int size;//Number of customers in queue
    int front;//Index of first customer
    int rear;//Index of last customer
    struct Buyers *buyers;//Pointer to customer array
}PriorityQueue;

//List all functions
PriorityQueue * createPriorityQueue(int numOfBuyers); //Create the arrival priority queue
int isEmpty(PriorityQueue *PQ); //Check if arrival priority queue is empty
struct Buyers peek(PriorityQueue *PQ); //Look at first element of arrival priority queue
struct Buyers poll(PriorityQueue *PQ); //Remove an element from the arrival priority queue
void add(PriorityQueue *PQ, struct Buyers buyer); //Add an element to the arrival priority queue

#endif // ARRIVALPRIORITYQUEUE_H
