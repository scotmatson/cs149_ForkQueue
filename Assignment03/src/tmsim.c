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
#include "seatmap.h"

/* Seller Logic */
static const int NUMBER_OF_SELLERS = 10;

/* Map Visualization */
static char * const EMPTY_SEAT = "----";

/* Utility */
static const char NEWLINE = '\n';

/* Thread stuff that I don't quite understand... yet */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* Statistics */
int total_sales = 0;
int total_unseated = 0;
 
// seatmap stuff   

struct Seatmap map;


/*
 * seller thread to serve one time slice (1 minute)
 */

void *sell(void *pq) {
    struct PriorityQueue *sellers_queue = (PriorityQueue *) pq;
    int thread_clock = 0;
    int buyer_seated = 0;
    
    while(!isEmpty(sellers_queue) && thread_clock < 60) {
        struct Buyers b = poll(sellers_queue);


        printf(
            "Buyer name = %s\n"
            "Arrival time = %d\n"
            "Service time = %d\n"
            "Priority = %c\n\n",
            b.name,
            b.arrival_time,
            b.service_time,
            b.priority);
        fflush(stdout);

        int buyer_seated = 0;
        b.sale_start_time = thread_clock;
        b.sale_end_time = thread_clock + b.service_time;
        b.sale_time = b.sale_end_time - b.sale_start_time;;
        
        print_seatmap(&map);
        fflush(stdout);

        while (thread_clock != b.sale_end_time) {
            thread_clock++;
        }
        
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
        
       /*  
        struct Seatmap map;

        initialize_seatmap(&map);
   
        print_seatmap(&map); 
    */

        
        buyer_seated = set_seat(&map, &b);

        if (buyer_seated == -1){
            total_unseated++;
        }
        else if (buyer_seated != -1) {
            total_sales++;
        }
        
        thread_clock++;
    }
    return NULL;
}

void wakeup_all_seller_threads() {
    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
}



   



/*
 * The main method
 */
int main(int argc, char * argv[2]) {

    
    initialize_seatmap(&map);
    
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
    //printf("Value of N: %d\n", n); /* TEST */
    printf("Initial amount of seat: 100\n");
    printf("%d customers for each seller\n", n);
    printf("Total customers: %d\n", n * 10);


    int i, j;                 /* Counters */
    int rc;                   /* Error Return Code */
    pthread_t tids[NUMBER_OF_SELLERS];
    srand(time(NULL));        /* Seeding the random number generator */

    
    
    // seatmap stuff   
      
    print_seatmap(&map);

 
    
    
    
    
    // Create NUMBER_OF_SELLERS sellerqueues, then create n buyers for each sellersQueue
    //  and put them into the correct sellersQueue based on buyer attributes. Then place
    //  all sellersQueues inthe SellersQueueArray ordered 
    //  [H0, M1, M2, M3, L1, L2, L3, L4, L5, L6], where each element is a complete sellersQueue
    // This must happen before the loop
    PriorityQueue** sqa = buildSellersQueueArray(NUMBER_OF_SELLERS, n);

    /* Thread Creation */
    for (i = 0; i < NUMBER_OF_SELLERS; i++) {
        PriorityQueue * pq = sqa[i];
        rc = pthread_create(&tids[i], NULL, sell, (void *) pq);
        if (rc) {
            fflush(stdout);
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }

    wakeup_all_seller_threads();
    /* THIS CAUSES CODE TO HANG, POSSIBLE DEADLOCK */
   /* 
    //Wait for all seller threads to exit 
    
    for (i = 0 ; i < NUMBER_OF_SELLERS ; i++) {
        rc = pthread_join(tids[i], NULL);
        if (rc) {
            fflush(stdout);
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }
   /* 
    for (i = 0 ; i < 10 ; i++) {

       Pthread_join(&tids[i], NULL);
    }
*/
    printf("Total sales: %d\n", total_sales);
    printf("Total unseated: %d\n", total_unseated);
    print_seatmap(&map);
    exit(EXIT_SUCCESS);
}
