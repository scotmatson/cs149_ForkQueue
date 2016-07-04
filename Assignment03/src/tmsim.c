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
#include "priorityqueue.h"
#include "buyers.h"
#include "tickets.h"
#include "sellers.h"

/*
struct box_office {
    int time;
    struct Ticket available_tickets[500];
    struct Buyer turned_away[500];
    struct Ticket tickets_sold[500];
    struct Buyer customers_served[500];
};
*/

/* Seller Logic */
static const int NUMBER_OF_SELLERS = 10;
//static const int HIGH_PRICE_SELLERS = 1;
//static const int MEDIUM_PRICE_SELLERS = 3;
//static const int LOW_PRICE_SELLERS = 6;

/* Time */
static const int ONE_HOUR = 60;

/* Map Visualization */
static const int NUMBER_OF_ROWS = 10;
static const int SEATS_PER_ROW = 10;
static char * const EMPTY_SEAT = "--";

/* Utility */
static const char NEWLINE = '\n';

/* Thread stuff that I don't quite understand... yet */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * seller thread to serve one time slice (1 minute)
 */
void * sell(void * s) {
    struct Sellers *seller = (struct Sellers*) s;
    printf("Type: %c - Time: %d\n", seller->type, seller->service_time);
    fflush(stdout);

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
    pthread_t tids[10];       /* */
    srand(time(NULL));        /* Seeding the random number generator */
    n *= NUMBER_OF_SELLERS;   /* Number of customers */

    // Create necessary data structures for the simulator.
    char * seatmap[NUMBER_OF_ROWS][SEATS_PER_ROW];
    for (i=0; i < NUMBER_OF_ROWS; i++) {
        for (j=0; j < SEATS_PER_ROW; j++) {
            seatmap[i][j] = EMPTY_SEAT;
        }
    }
   
    /* Declare the buyer priority queue */
    PriorityQueue *ticket_line = createPriorityQueue(n);

    /* Generate N Buyer structs */
    printf("*** Generating %d Buyers ***\n", n);
    for (i = 0; i <= n; i++) {

        /* I don't entirely understand why we have so many variables -sm */
        struct Buyers buyer;
        buyer.arrival_time = rand() % ONE_HOUR;
        buyer.name;
        buyer.priority;
        buyer.wait_time;

        buyer.start_time;
        buyer.end_time;

        /* Assigned at time of sale */
        buyer.bought_ticket;
        buyer.seller_name;
        buyer.seat_number;
        buyer.sale_time;

        /* Buyer struct should be placed in Queue here */
        ticket_line
        printf("C%d", i);
    }
    printf("%c", NEWLINE);

    /* Thread Creation - SELLERS */
    struct Sellers sellers[NUMBER_OF_SELLERS];
    for (i = 0; i < 1; i++) {
        int min_time = 1;
        int max_time = 2;
        int service_time = rand() % (max_time + 1 - min_time) + min_time;

        sellers[i].type = 'H';
        sellers[i].service_time = service_time;
        // Reference to PQueue
        rc = pthread_create(&tids[i], NULL, sell, &sellers[i]);
        if (rc) {
            fflush(stdout);
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }
   
    for (i = 1; i < 4; i++) {
        int min_time = 2;
        int max_time = 4;
        int service_time = rand() % (max_time + 1 - min_time) + min_time;

        sellers[i].type = 'M';
        sellers[i].service_time = service_time;
        // Reference to PQueue
        rc = pthread_create(&tids[i], NULL, sell, &sellers[i]);
        if (rc) {
            fflush(stdout);
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 4; i < 10; i++) {
        int min_time = 4;
        int max_time = 7;
        int service_time = rand() % (max_time + 1 - min_time) + min_time;
        
        sellers[i].type = 'L';
        sellers[i].service_time = service_time;
        // Reference to PQueue
        rc = pthread_create(&tids[i], NULL, sell, &sellers[i]);
        if (rc) {
            fflush(stdout);
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }

    // wakeup all seller threads
    //wakeup_all_seller_threads();

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
