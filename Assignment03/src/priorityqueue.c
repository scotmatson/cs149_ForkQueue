#include "arrivalPriorityQueue.h"\
//This file includes implementation of all functions in arrivalPriorityQueue.h
// Solves CS149 Homework#3
// @author Tyler Jones

//****************************************************************************************
//CreatePriortityQueue takes the number of customers, and creates
//a PriorityQueue and returns a pointer to the PriorityQueue.
//****************************************************************************************
PriorityQueue * createPriorityQueue(int numOfBuyers)
{
        PriorityQueue *PQ;
        PQ = (PriorityQueue*)malloc(sizeof(PriorityQueue));
        //Initialize attributes
        PQ->buyers = (struct Buyers*)malloc(sizeof(struct Buyers) * numOfBuyers);
        PQ->size = 0;
        PQ->capacity = numOfBuyers;
        PQ->front = 0;
        PQ->rear = -1;
        //Return the pointer to the PriorityQueue
        return PQ;
}

//****************************************************************************************
//Check if arrival priority queue is empty
//****************************************************************************************
int isEmpty(PriorityQueue *PQ)
{
    if(PQ->size <= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//****************************************************************************************
//Look at first element of arrival priority queue
//****************************************************************************************
struct Buyers peek(PriorityQueue *PQ)
{
    return PQ->buyers[PQ->front];
}

//****************************************************************************************
//Remove an element from the arrival priority queue
//****************************************************************************************
struct Buyers poll(PriorityQueue *PQ)
{
    //Removing a buyer is just incrementing index of front
    PQ->size--;
    PQ->front++;
    //return PQ->buyers[PQ->(front - 1)];
    return PQ->buyers[PQ->front-1];
}

//****************************************************************************************
//Add an element to the arrival priority queue
//****************************************************************************************
void add(PriorityQueue *PQ, struct Buyers buyer)
{
    int index = PQ->rear;
    while(buyer.arrival_time < PQ->buyers[index].arrival_time && index >= 0)
    {
        PQ->buyers[index+1] = PQ->buyers[index];
        index--;
    }
    //Finally add the buyer in correct space
    PQ->size++;
    PQ->rear++;
    PQ->buyers[index+1] = buyer;
}
