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

/* Business Logic */
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
    printf("Seller type %c\n", seller->type);
    fflush(stdout);

    //while (true) { // Having more work to do...
    //    pthread_mutex_lock(&mutex);
    //    pthread_cond_wait(&cond, &mutex);
    //    pthread_mutex_unlock(&mutex)

    // Serve any buyer available in this sell queue that is ready
    // now to buy ticket till done with all relevant buyers in their queue

    //int gen_service_time(int min_service_time, int max_service_time) {
    //srand (time(NULL));
    //int random_service_time = (rand() % max_service_time) + min_service_time;
    //return random_service_time;
    return NULL;
}


/*
 * The main method
 */
int main(int argc, char * argv[]) {
  
    /* --- TESTING --- */
    // seller time
    //shtruct Sellers seller1;
    //struct Sellers seller2;
    //seller1.min_service_time = 1;
    //seller1.max_service_time = 5;
    //seller2.min_service_time = 1;
    //seller2.max_service_time = 5;
    
    // buyer testing
    struct Buyers buyer1;
    buyer1.seat_number = 5;
    buyer1.priority = "H";
    strcpy(buyer1.name, "martin");
    printf("%d\n", buyer1.seat_number);
    printf("%c\n", *buyer1.priority);
    printf("%s\n", buyer1.name);
    fflush(stdout);
    
    // ticket testing
    struct Tickets ticket1;
    ticket1.seat_number = 5;
    ticket1.priority = "H";

    printf("Tickets\n");
    printf("%d\n", ticket1.seat_number);
    printf("%c\n", *ticket1.priority);
    fflush(stdout);
    
    // ERROR IN THIS METHOD?? if run a.out, both of service times are same;
    // if run a.out twice, the number are the same to each other but different 
    // from run 1; does this have to do with the time slice?
    // ** gen_service_time does not work with x86_64 architectures
    //int service_time = gen_service_time(seller1.min_service_time, seller1.max_service_time);
    //int service_time2 = gen_service_time(seller2.min_service_time, seller2.max_service_time);
    //printf("Seller\n");
    //printf("%d\n", service_time);
    //printf("%d\n", service_time2);
    fflush(stdout);
    

    /* --- CODE STARTS HERE --- */
    // I/O Handling
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

    int i, j, rc;          
    int simulation_clock = 0;
    pthread_t tids[10];     

    // Create necessary data structures for the simulator.
    char * seatmap[NUMBER_OF_ROWS][SEATS_PER_ROW];
    for (i=0; i < NUMBER_OF_ROWS; i++) {
        for (j=0; j < SEATS_PER_ROW; j++) {
            seatmap[i][j] = EMPTY_SEAT;
        }
    }
   
    char *testchar = "5";
    seatmap[5][5] = testchar;;
    // Create buyers list for each seller ticket queue based on the
    // N value within an hour and have them in the seller queue.
   
    // Create 10 threads representing the 10 sellers.
    struct Sellers sellers[NUMBER_OF_SELLERS];
    for (i = 0; i < 1; i++) {
        sellers[i].type = 'H';
        rc = pthread_create(&tids[i], NULL, sell, &sellers[i]);
        if (rc) {
            fflush(stdout);
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }
   
    for (i = 1; i < 4; i++) {
        sellers[i].type = 'M';
        rc = pthread_create(&tids[i], NULL, sell, &sellers[i]);
        if (rc) {
            fflush(stdout);
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            fflush(stderr);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 4; i < 10; i++) {
        sellers[i].type = 'L';
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
