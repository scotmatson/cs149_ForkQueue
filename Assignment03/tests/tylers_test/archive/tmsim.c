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
#include <time.h>

#include "/Users/Natera/Documents/cs149_ForkQueue/Assignment03/src/customer.h"
#include "/Users/Natera/Documents/cs149_ForkQueue/Assignment03/src/ticket.h"
#include "/Users/Natera/Documents/cs149_ForkQueue/Assignment03/src/seller.h"

// must use string.h for strcpy, only way to assign strings to char[] without loops
#include <string.h>

struct box_office {
    int time;
 //   struct ticket available_tickets[500];
   // struct customer turned_away[500];
  //  struct ticket tickets_sold[500];
  //  struct customer customers_served[500];
};


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

/* Thread stuff that I don't quite understand... yet */
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

// this function generates and returns a random_service_time, the time it will 
// take to complete a single transaction with a customer
int gen_service_time(int min_service_time, int max_service_time) {
    srand (time(NULL));
    int random_service_time = (rand() % max_service_time) + min_service_time;
    return random_service_time;
}


/*
 * The main method
 */
int main(int argc, char * argv[]) {
    
    //customer testing
    struct customer customer1;
    customer1.seat_number = 5;
    customer1.priority = "H";
    strcpy(customer1.name, "martin");
    printf("%d\n", customer1.seat_number);
    printf("%c\n", *customer1.priority);
    printf("%s\n", customer1.name);
    
    // ticket testing
    struct ticket ticket1;
    ticket1.seat_number = 5;
    ticket1.priority = "H";

    printf("Tickets\n");
    printf("%d\n", ticket1.seat_number);
    printf("%c\n", *ticket1.priority);
   


    // I/O Handling
    int n; 
    if (argc != 2) {
       fprintf(stderr, "ERROR; Execution must be in form [./a.out] [int]\n"); 
       exit(EXIT_FAILURE);
    }
    else {
        if (!isdigit(*argv[1])) {
            fprintf(stderr, "ERROR; User input must be type int\n");
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
   
    char *testchar = "5";
    seatmap[5][5] = testchar;;
    // Create buyers list for each seller ticket queue based on the
    // N value within an hour and have them in the seller queue.
   
    // Create 10 threads representing the 10 sellers.
    char sellertype;
    sellertype = 'H';
    for (i = 0; i < 1; i++) {
        rc = pthread_create(&tids[i], NULL, sell, &sellertype);
        if (rc) {
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }
   
    sellertype = 'M';
    for (i = 1; i < 4; i++) {
        rc = pthread_create(&tids[i], NULL, sell, &sellertype);
        if (rc) {
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    sellertype = 'L';
    for (i = 4; i < 10; i++) {
        rc = pthread_create(&tids[i], NULL, sell, &sellertype);
        if (rc) {
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    // wakeup all seller threads
    //wakeup_all_seller_threads();

    // Wait for all seller threads to exit
    for (i = 0 ; i < NUMBER_OF_SELLERS ; i++) {
        rc = pthread_join(tids[i], NULL); // SUCCESS == 0
        if (rc) {
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
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
    } 

    exit(EXIT_SUCCESS);
}
