/* 
 * Header file for the array of sellers priorityqueues to be used with tmsim.c
 * Solves CS149 Homework#3
 * @author Tyler Jones
 */

#ifndef SELLERSQUEUEARRAY_H
#define SELLERSQUEUEARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "priorityqueue.h"

typedef struct SellersQueueArray {
    PriorityQueue * sellersQueues;
} SellersQueueArray;

/*
 * List all functions
 * Create the array of complete sellers queues
 */
//PriorityQueue** buildSellersQueueArray(int numOfSellers, int numOfBuyers);
PriorityQueue** buildSellersQueueArray(int numOfBuyers);
#endif /* SELLERSQUEUEARRAY_H */
