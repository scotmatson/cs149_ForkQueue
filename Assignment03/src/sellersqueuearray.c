/*
 * This file includes implementation of all functions in sellersqueuearray.h
 * Solves CS149 Homework#3
 * @author Tyler Jones
 */
#include "sellersqueuearray.h"
#include "priorityqueue.h"
#include "buyers.h"

/* Seller Logic */
static const int MEDIUM_PRICE_SELLERS = 3;
static const int LOW_PRICE_SELLERS = 6;

//void buildSellersQueueArray(SellersQueueArray *SQA, int numOfBuyers)
//PriorityQueue** buildSellersQueueArray(int numOfSellers, int numOfBuyers)
PriorityQueue** buildSellersQueueArray(int numOfBuyers)
{
    //PriorityQueue H0, M1, M2, M3, L1, L2, L3, L4, L5, L6, L7;
    // Create an array of PriorityQueues for later use
    // This is hack-ish, but I couldn't get malloc to work right here
    static PriorityQueue * sellersQueues[10];

    // Priority queues for the 10 Sellers
    PriorityQueue *H0 = createPriorityQueue(numOfBuyers);
    sellersQueues[0] = H0;
    PriorityQueue *M1 = createPriorityQueue(numOfBuyers);
    sellersQueues[1] = M1;
    PriorityQueue *M2 = createPriorityQueue(numOfBuyers);
    sellersQueues[2] = M2;
    PriorityQueue *M3 = createPriorityQueue(numOfBuyers);
    sellersQueues[3] = M3;
    PriorityQueue *L1 = createPriorityQueue(numOfBuyers);
    sellersQueues[4] = L1;
    PriorityQueue *L2 = createPriorityQueue(numOfBuyers);
    sellersQueues[5] = L2;
    PriorityQueue *L3 = createPriorityQueue(numOfBuyers);
    sellersQueues[6] = L3;
    PriorityQueue *L4 = createPriorityQueue(numOfBuyers);
    sellersQueues[7] = L4;
    PriorityQueue *L5 = createPriorityQueue(numOfBuyers);
    sellersQueues[8] = L5;
    PriorityQueue *L6 = createPriorityQueue(numOfBuyers);
    sellersQueues[9] = L6;

    //****************************************************************************
    // Create N Buyers with 
    //****************************************************************************

    int i, j;
    char str[5];
    char strNum[5];
    for (i = 1; i <= numOfBuyers; i++) {
        //**********************Create H0 queue buyers***********************
        struct Buyers h;
        //Create the buyers name
        if (i < 10) {
            strcpy(str, "H00");
            sprintf(strNum, "%d", i);
            strcat(str, strNum);
        }
        else {
            strcpy(str, "H0");
            sprintf(strNum, "%d", i);
            strcat(str, strNum);
        }
        strcpy(h.name, str);
        //Create the buyers arrival and sale times randomly
        h.arrival_time = rand() % 60; //0 to 59
        h.service_time = rand() % 2 + 1; //1 to 2 /* 
        //Assign a the sellers name  and priority to this buyer
        strcpy(h.seller_name, "H0");
        h.priority = 'H';
        //Add the buyer to the correct queue
        add(H0, h);

        //***********************Create M1 -M3 queue buyers*******************
        for(j = 1; j <= MEDIUM_PRICE_SELLERS; j++) {
            struct Buyers m;
            //Determin which of the 3 seller queues to work with via switch
            switch (j) {
                case 1:
                    //Create the buyers name
                    if(i < 10)
                    {
                        strcpy(str, "M10");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else
                    {
                        strcpy(str, "M1");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(m.name, str);
                    //Create the buyers arrival and sale times randomly
                    m.arrival_time = rand() % 60; //0 to 59
                    m.service_time = rand() % 2 + 2; //2 to 4
                    //Assign a the sellers name  and priority to this buyer
                    strcpy(m.seller_name, "M1");
                    m.priority = 'M';
                    //Add the buyer to the correct queue
                    add(M1, m);
                    break;
                case 2:
                    //Create the buyers name
                    if(i < 10)
                    {
                        strcpy(str, "M20");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else
                    {
                        strcpy(str, "M2");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(m.name, str);
                    //Create the buyers arrival and sale times randomly
                    m.arrival_time = rand() % 60; //0 to 59
                    m.service_time = rand() % 2 + 2; //2 to 4
                    //Assign a the sellers name  and priority to this buyer
                    strcpy(m.seller_name, "M2");
                    m.priority = 'M';
                    //Add the buyer to the correct queue
                    add(M2, m);
                    break;
                case 3:
                    //Create the buyers name
                    if(i < 10)
                    {
                        strcpy(str, "M30");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else
                    {
                        strcpy(str, "M3");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(m.name, str);
                    //Create the buyers arrival and sale times randomly
                    m.arrival_time = rand() % 60; //0 to 59
                    m.service_time = rand() % 2 + 2; //2 to 4
                    //Assign a the sellers name  and priority to this buyer
                    strcpy(m.seller_name, "M3");
                    m.priority = 'M';
                    //Add the buyer to the correct queue
                    add(M3, m);
                    break;
                default:
                    break;
            }
        }

        //***********************Create L1 -L6 queue buyers*******************
        for (j = 1; j <= LOW_PRICE_SELLERS; j++) {
            struct Buyers l;
            //Determin which of the 6 seller queues to work with via switch
            switch (j) {
                case 1:
                    //Create the buyers name
                    if (i < 10) {
                        strcpy(str, "L10");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else {
                        strcpy(str, "L1");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    //Create the buyers arrival and sale times randomly
                    l.arrival_time = rand() % 60; //0 to 59
                    l.service_time = rand() % 4 + 4; //4 to 7
                    //Assign a the sellers name  and priority to this buyer
                    strcpy(l.seller_name, "L1");
                    l.priority = 'L';
                    //Add the buyer to the correct queue
                    add(L1, l);
                    break;
                case 2:
                    //Create the buyers name
                    if(i < 10) {
                        strcpy(str, "L20");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else {
                        strcpy(str, "L2");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    //Create the buyers arrival and sale times randomly
                    l.arrival_time = rand() % 60; //0 to 59
                    l.service_time = rand() % 4 + 4; //4 to 7
                    //Assign a the sellers name  and priority to this buyer
                    strcpy(l.seller_name, "L2");
                    l.priority = 'L';
                    //Add the buyer to the correct queue
                    add(L2, l);
                    break;
                case 3:
                    //Create the buyers name
                    if(i < 10) {
                        strcpy(str, "L30");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else {
                        strcpy(str, "L3");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    //Create the buyers arrival and sale times randomly
                    l.arrival_time = rand() % 60; //0 to 59
                    l.service_time = rand() % 4 + 4; //4 to 7
                    //Assign a the sellers name  and priority to this buyer
                    strcpy(l.seller_name, "L3");
                    l.priority = 'L';
                    //Add the buyer to the correct queue
                    add(L3, l);
                    break;
                case 4:
                    //Create the buyers name
                    if (i < 10) {
                        strcpy(str, "L40");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else {
                        strcpy(str, "L4");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    //Create the buyers arrival and sale times randomly
                    l.arrival_time = rand() % 60; //0 to 59
                    l.service_time = rand() % 4 + 4; //4 to 7
                    //Assign a the sellers name  and priority to this buyer
                    strcpy(l.seller_name, "L4");
                    l.priority = 'L';
                    //Add the buyer to the correct queue
                    add(L4, l);
                    break;
                case 5:
                    //Create the buyers name
                    if(i < 10) {
                        strcpy(str, "L50");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else {
                        strcpy(str, "L5");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    //Create the buyers arrival and sale times randomly
                    l.arrival_time = rand() % 60; //0 to 59
                    l.service_time = rand() % 4 + 4; //4 to 7
                    //Assign a the sellers name  and priority to this buyer
                    strcpy(l.seller_name, "L5");
                    l.priority = 'L';
                    //Add the buyer to the correct queue
                    add(L5, l);
                    break;
                case 6:
                    //Create the buyers name
                    if(i < 10) {
                        strcpy(str, "L60");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else {
                        strcpy(str, "L6");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    //Create the buyers arrival and sale times randomly
                    l.arrival_time = rand() % 60; //0 to 59
                    l.service_time = rand() % 4 + 4; //4 to 7
                    //Assign a the sellers name  and priority to this buyer
                    strcpy(l.seller_name, "L6");
                    l.priority = 'L';
                    //Add the buyer to the correct queue
                    add(L6, l);
                    break;
                default:
                    break;
            }
        }
    }
return sellersQueues;
}

