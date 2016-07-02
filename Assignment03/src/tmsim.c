/*
 *  Solves CS149 Assignment #3 
 *
 *  Authors: 
 *      Tyler Jones, 
 *      Scot Matson
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>     
#include <stdbool.h>
#include <ctype.h>

/* Business Logic */
static const int NUMBER_OF_SELLERS = 10;
static const int HIGH_PRICE_SELLERS = 1;
static const int MEDIUM_PRICE_SELLERS = 3;
static const int LOW_PRICE_SELLERS = 6;

/* Map Visualization */
static const int NUMBER_OF_ROWS = 10;
static const int SEATS_PER_ROW = 10;
static char * const EMPTY_SEAT = "--";

/* Utility */
static const char NEWLINE = '\n';

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * seller thread to serve one time slice (1 minute)
 */
void * sell(void * sellertype) {
    char  st;
    st = *((char*) sellertype);

    printf("Seller type %c\n", st);

    //while (true) { // Having more work to do...
    //    pthread_mutex_lock(&mutex);
    //    pthread_cond_wait(&cond, &mutex);
    //    pthread_mutex_unlock(&mutex);

        // Serve any buyer available in this seller queue that is ready
        // now to buy ticket till done with all relevant buyers in their queue
        //..................
    //}

    pthread_exit(NULL);
}

/*
 * Wakes up all of the seller threads
 */
void wakeup_all_seller_threads() {
    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
}

/*
 * The main method
 */
int main(int argc, char * argv[]) {

    /* I/O Handling */
    int n; 
    if (argc != 2) {
       printf("ERROR; Execution must be in form [./a.out] [int]\n"); 
       exit(EXIT_FAILURE);
    }
    else {
        if (!isdigit(*argv[1])) {
            printf("ERROR; User input must be type int\n");
            exit(EXIT_FAILURE);
        }
        else {
            n = atoi(argv[1]);
        }
    }

    int i, j, rc;          
    pthread_t tids[10];     

    // Create necessary data structures for the simulator.
    char * seatmap[NUMBER_OF_ROWS][SEATS_PER_ROW];
    for (i=0; i < NUMBER_OF_ROWS; i++) {
        for (j=0; j < SEATS_PER_ROW; j++) {
            seatmap[i][j] = EMPTY_SEAT;
        }
    }
    
    // Create buyers list for each seller ticket queue based on the
    // N value within an hour and have them in the seller queue.
   
    // Create 10 threads representing the 10 sellers.
    char sellertype;
    sellertype = 'H';
    for (i = 0; i < 1; i++) {
        rc = pthread_create(&tids[i], NULL, sell, &sellertype);
        if (rc) {
            printf("ERROR; return code from pthread_join is %d\n", rc);
        }
    }
   
    sellertype = 'M';
    for (i = 1; i < 4; i++) {
        rc = pthread_create(&tids[i], NULL, sell, &sellertype);
        if (rc) {
            printf("ERROR; return code from pthread_join is %d\n", rc);
        }
    }

    sellertype = 'L';
    for (i = 4; i < 10; i++) {
        rc = pthread_create(&tids[i], NULL, sell, &sellertype);
        if (rc) {
            printf("ERROR; return code from pthread_join is %d\n", rc);
        }
    }

    // wakeup all seller threads
    //wakeup_all_seller_threads();

    // Wait for all seller threads to exit
    for (i = 0 ; i < NUMBER_OF_SELLERS ; i++) {
        rc = pthread_join(tids[i], NULL); // SUCCESS == 0
        if (rc) {
            printf("ERROR; return code from pthread_join is %d\n", rc);
        }
    }

    // Printout simulation results
    printf("Seating Chart\n");
    for (i=0; i < NUMBER_OF_ROWS; i++) {
        for (j=0; j < SEATS_PER_ROW; j++) {
            printf("%-3s", seatmap[i][j]);
        }
        printf("%c", NEWLINE);
    } 

    exit(EXIT_SUCCESS);
}
