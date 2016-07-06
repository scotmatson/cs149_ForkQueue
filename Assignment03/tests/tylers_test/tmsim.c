/*
 *  Solves CS149 Assignment #3 
 *
 *  Authors: 
 *      Tyler Jones, 
 *      Scot Matson
 */
/* C libs */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>     
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

/* User libs */
//#include "boxoffice.h"
#include "seats.h"
#include "priorityqueue.h"
#include "buyers.h"

/* Seller Logic */
static const int NUMBER_OF_SELLERS = 10;
static const int MEDIUM_PRICE_SELLERS = 3;
static const int LOW_PRICE_SELLERS = 6;

/* Time */
static const int ONE_HOUR = 60;

/* Map Visualization */
static const int NUMBER_OF_ROWS = 10;
static const int SEATS_PER_ROW = 10;
static char * const EMPTY_SEAT = "----";

/* Utility */
static const char NEWLINE = '\n';

/* Thread stuff that I don't quite understand... yet */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * seller thread to serve one time slice (1 minute)
 */
void *sell(void *pq) {
    struct PriorityQueue *sellers_queue = (PriorityQueue *) pq;

    //Tester just to see if the queue made it
    while(!isEmpty(sellers_queue))
    {
        struct Buyers b = poll(sellers_queue);
        printf("\nBuyer name = " );
        printf("%s", b.name);
        printf("\nArrival time = " );
        printf("%d", b.arrival_time);
        printf("\nSale time = " );
        printf("%d", b.sale_time);
        printf("\nPriority = " );
        printf("%c", b.priority);
        printf("\n\n");
        fflush(stdout);
    }

    /* This while condition is by reference and shared
       by all sellers */
    //while (!seller.ticket_line.isEmpty()) {
    //    pthread_mutex_lock(&mutex);
    //    pthread_cond_wait(&cond, &mutex);
    //    pthread_mutex_unlock(&mutex)

    // Serve any buyer available in this sell queue that is ready
    // now to buy ticket till done with all relevant buyers in their queue
    return NULL;
}


/*
 * The main method
 */
int main(int argc, char * argv[]) {
  
    // I/O Handling - Do this first, if no arg given, kill execution
    int n; 
    if (argc != 2) {
       fflush(stdout);
       fprintf(stderr, "ERROR; Execution must be in form [./a.out] [int]\n"); 
       fflush(stderr);
       exit(EXIT_FAILURE);
    }
    else {
        if (!isdigit(*argv[1])) {
            fflush(stdout);
            fprintf(stderr, "ERROR; User input must be type int\n");
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
        else {
            n = atoi(argv[1]);
        }
    }

    int i, j;                 /* Counters */
    int rc;                   /* Error Return Code */
    int simulation_clock = 0; /* Simulated time represented by loop iterations */
    pthread_t tids[NUMBER_OF_SELLERS];       /* */
    srand(time(NULL));        /* Seeding the random number generator */

    // Create necessary data structures for the simulator.
    char * seatmap[NUMBER_OF_ROWS][SEATS_PER_ROW];
    for (i=0; i < NUMBER_OF_ROWS; i++) {
        for (j=0; j < SEATS_PER_ROW; j++) {
            seatmap[i][j] = EMPTY_SEAT;
        }
    }

    //PriorityQueue H0, M1, M2, M3, L1, L2, L3, L4, L5, L6, L7;
    // Create an array of PriorityQueues for later use
    PriorityQueue * sellersQueues[NUMBER_OF_SELLERS];
    // Priority queues for the 10 Sellers
    PriorityQueue *H0 = createPriorityQueue(n);
    sellersQueues[0] = H0;
    PriorityQueue *M1 = createPriorityQueue(n);
    sellersQueues[1] = M1;
    PriorityQueue *M2 = createPriorityQueue(n);
    sellersQueues[2] = M2;
    PriorityQueue *M3 = createPriorityQueue(n);
    sellersQueues[3] = M3;
    PriorityQueue *L1 = createPriorityQueue(n);
    sellersQueues[4] = L1;
    PriorityQueue *L2 = createPriorityQueue(n);
    sellersQueues[5] = L2;
    PriorityQueue *L3 = createPriorityQueue(n);
    sellersQueues[6] = L3;
    PriorityQueue *L4 = createPriorityQueue(n);
    sellersQueues[7] = L4;
    PriorityQueue *L5 = createPriorityQueue(n);
    sellersQueues[8] = L5;
    PriorityQueue *L6 = createPriorityQueue(n);
    sellersQueues[9] = L6;

    //****************************************************************************
    // Create buyers list for each seller ticket queue based on the
    // N value within an hour and put them in the correct seller queue.
    //****************************************************************************

    for (i = 1; i <= n; i++) {
        //**********************Create H0 queue buyers***********************
        struct Buyers h;
        char str[5];
        char strNum[5];
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
        h.sale_time = rand() % 2 + 1; //1 to 2 /* 
        h.priority = 'H';
        //Add the buyer to the correct queue
        add(H0, h);

        //***********************Create M1 -M3 queue buyers*******************
        for(j = 1; j <= MEDIUM_PRICE_SELLERS; j++) {
            struct Buyers m;
            char str[5];
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
                    m.sale_time = rand() % 2 + 2; //2 to 4
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
                    m.sale_time = rand() % 2 + 2; //2 to 4
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
                    m.sale_time = rand() % 2 + 2; //2 to 4
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
            char str[5];
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
                    l.sale_time = rand() % 4 + 4; //4 to 7
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
                    l.sale_time = rand() % 4 + 4; //4 to 7
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
                    l.sale_time = rand() % 4 + 4; //4 to 7
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
                    l.sale_time = rand() % 4 + 4; //4 to 7
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
                    l.sale_time = rand() % 4 + 4; //4 to 7
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
                    l.sale_time = rand() % 4 + 4; //4 to 7
                    l.priority = 'L';
                    //Add the buyer to the correct queue
                    add(L6, l);
                    break;
                default:
                    break;
            }
        }
    }

    /* Thread Creation - SELLERS PRIORITY QUEUE */
    for (i = 0; i < NUMBER_OF_SELLERS; i++) {
        rc = pthread_create(&tids[i], NULL, sell, (void *) sellersQueues[i]);
        if (rc) {
            fflush(stdout);
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }

    // wakeup all seller threads
    // wakeup_all_seller_threads();

    // Wait for all seller threads to exit
    for (i = 0 ; i < NUMBER_OF_SELLERS ; i++) {
        rc = pthread_join(tids[i], NULL);
        if (rc) {
            fflush(stdout);
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }

    // Printout simulation results
    printf("Seating Chart\n");
    for (i=0; i < NUMBER_OF_ROWS; i++) {
        for (j=0; j < SEATS_PER_ROW; j++) {
            printf("%-3s", seatmap[i][j]);
        }
        printf("%c", NEWLINE);
        fflush(stdout);
    } 

    exit(EXIT_SUCCESS);
}
