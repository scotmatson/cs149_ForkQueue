/*
 *  Solves CS149 Assignment #3 
 *  Test Driver for tmsim.c
 *  Authors: 
 *      Tyler Jones, 
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
#include "priorityqueue.h"
#include "sellersqueuearray.h"
#include "buyers.h"

/* Seller Logic */
static const int NUMBER_OF_SELLERS = 10;

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
    //struct PriorityQueue *sellers_queue = (PriorityQueue *) pq;
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
    
    /*
     * start francisco void sell code
    int thread_clock = 0;
    int buyer_seated = 0;

    while (!sellers_queue.isEmpty() && thread_clock < 60) {
        Buyers b = sellers_queue.poll();
        int buyer_seated = 0;
        b.sale_start_time = thread_clock;
        b.sale_end_time = thread_clock + b.service_time;
        b.sale_time = b.sale_end_time - b.start_sale_time;
       
        while (thread_clock != b.sale_end_time) {
            thread_clock++;
        }
        
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);

        buyer_seated = seat_this_buyer(b);

        if (buyer_seated == -1){
            add(unserved_list, b);
        }
        thread_clock++;
    }
    // Serve any buyer available in this sell queue that is ready
    // now to buy ticket till done with all relevant buyers in their queue
    return NULL;
}


/*
 * The main method
 */
int main(int argc, char * argv[2]) {
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
    printf("Value of N: %d\n", n); /* TEST */

    int i, j;                 /* Counters */
    int rc;                   /* Error Return Code */
    pthread_t tids[NUMBER_OF_SELLERS];
    srand(time(NULL));        /* Seeding the random number generator */

    // Create necessary data structures for the simulator.
    char * seatmap[NUMBER_OF_ROWS][SEATS_PER_ROW];
    for (i = 0; i < NUMBER_OF_ROWS; i++) {
        for (j = 0; j < SEATS_PER_ROW; j++) {
            seatmap[i][j] = EMPTY_SEAT;
        }
    }
    printf("Seatmap has been initialized\n");

    /* SEGMENTATION FAULT ORIGIN IS BELOW */

    // Create NUMBER_OF_SELLERS sellerqueues, then create n buyers for each sellersQueue
    // and put them into the correct sellersQueue based on buyer attributes. Then place
    //all sellersQueues inthe SellersQueueArray ordered 
    //[H0, M1, M2, M3, L1, L2, L3, L4, L5, L6], where each element is a complete sellersQueue
    //SellersQueueArray *sellersQueues = createSellersQueueArray(NUMBER_OF_SELLERS, n);
    
    /* Thread Creation - SELLERS PRIORITY QUEUE */
    for (i = 0; i < NUMBER_OF_SELLERS; i++) {
        printf("Value of i: %d\n", i);

        //sellersQueues[i].sellersQueues;        

        //rc = pthread_create(&tids[i], NULL, sell, (void *) sellersQueues[i].sellersQueues);
        rc = pthread_create(&tids[i], NULL, sell, (void *) createSellersQueueArray(NUMBER_OF_SELLERS, n));
        if (rc) {
            fflush(stdout);
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }

    /* THIS IS MISSING? 
    wakeup_all_seller_threads();
    */

    /* Wait for all seller threads to exit */
    /*
    for (i = 0 ; i < NUMBER_OF_SELLERS ; i++) {
        rc = pthread_join(tids[i], NULL);
        if (rc) {
            fflush(stdout);
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }
    */

    /* Printout simulation results */
    /*
    printf("Seating Chart\n");
    for (i=0; i < NUMBER_OF_ROWS; i++) {
        for (j=0; j < SEATS_PER_ROW; j++) {
            printf("%-3s", seatmap[i][j]);
        }
        printf("%c", NEWLINE);
        fflush(stdout);
    } 
    */

    exit(EXIT_SUCCESS);
}
