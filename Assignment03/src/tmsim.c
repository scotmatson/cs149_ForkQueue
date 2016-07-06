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
//#include "seats.h"
#include "priorityqueue.h"
#include "buyers.h"
#include "sellers.h"

<<<<<<< HEAD
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
=======
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
 * make a seller 
 *
 */

/*
 * seller thread to serve one time slice (1 minute)
 */
void * sell(void * s) {
    struct Sellers *seller = (struct Sellers*) s;
    printf("Type: %c - Time: %d\n", seller->type, seller->service_time);
    fflush(stdout);
    
    // this is beginning of thread; set thread clock to 0;
    int thread_clock = 0;
    // if there are buyers in the seller.ticket_line && there is time left
    /* 
    while (!seller.ticket_line.isEmpty() && thread_clock < ONE_HOUR) {
        // poll for a buyer
        Buyer b = seller.ticket_line.poll();
        
        // generate a random service time
        int service_time = gen_random_service_time(b.priority);

        // set the start of the actual sale
        b.start_sale_time = clock;

        // set end of the sale as current + service_time 
        b.end_sale_time = thread_clock + service_time;

        // set the actual sale_time as interval between start and end of 
        // actual sale
        b.sale_time = b.end_sale_time - b.start_sale_time

        // if the thread_clock is not the same as the time the sale is 
        // supposed to occur, then increment the thread_clock
        while (thread_clock != b.end_sale_time) {
            thread_clock++;
        }
        
        // at time of sale, ask to get the lock
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex)

        // ask the seatmap to seat the buyer

        seat_this_buyer(buyer_queue.poll());

    }
    */
    return NULL;
}
>>>>>>> 981be5227b36c2e95f87eefbc83cd0a59ca5c93f

    /* Thread stuff that I don't quite understand... yet */
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    struct Buyers *seatmap[NUMBER_OF_ROWS][SEATS_PER_ROW];
    bool seats_available = true; // Starts true because 100 seats are open
    int UNSERVED_SIZE = 150;
    //#define UNSERVED_SIZE 150
   // PriorityQueue *unserved_buyers = createPriorityQueue(UNSERVED_SIZE);
    

    void seat_this_buyer(struct Buyers b){
    
       char priority_of_buyer = b.priority;

        if(seats_available == true)
        {
            switch(priority_of_buyer)
            {
        
                case 'H': //Assign buyer a high priority seating, starting from row 1
                    for(int i = 0; i < NUMBER_OF_ROWS; i++)
                    {
                        for(int j = 0; j < SEATS_PER_ROW; j++)
                        {
                           if(seatmap[i][j] == NULL)
                           { // Change to NULL after switching to hold objecti
                               seatmap[i][j] = &b; // Need to change seatmap to hold object
                                goto end; //Break out switch statement if seat is assigned
                           }
                        }
                    }
                    seats_available = false; // Change to false if no empty seats are found
                    break;

                case 'M'://Assign buyer a med priority seating, starting from row 4
                    for(int i = 3; i < NUMBER_OF_ROWS; i++)
                    {
                        for(int j = 0; j < SEATS_PER_ROW; j++)
                        {
                            if(seatmap[i][j] == NULL)
                            {//Change to NULL after switching to hold objects
                                seatmap[i][j] = &b;
                                goto end; //Break out switch statement if seat is assigned
                            }
                        }
                    }
                    seats_available = false; //Change to false if no empty seats are found
                    break;

                /*Low algo will start from row 10, sell from left to right,
                 *then decrement down a row when current row is filled up */
                case 'L':
                    for(int i = NUMBER_OF_ROWS - 1; i >= 0; i--)
                    {
                        for(int j = 0; j < SEATS_PER_ROW; j++){
                            if(seatmap[i][j] == NULL){//Change to NULL after switching to hold object
                                seatmap[i][j] = &b; //Need to change seatmap to hold object
                                goto end; //Break out switch statement if seat is assigned
                            }
                        }
                    }
                    seats_available = false; //Change to false if no empty seats are found
                    break;
            
            }
        }  
        //else, put the buyer into unserved list
      //  else{
    //        add(unserved_buyers, b);
       // }
            end:;//Label to break out switch statement
    }
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
        PriorityQueue *unserved_buyers = createPriorityQueue(150);

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
    //for (i=0; i < NUMBER_OF_ROWS; i++) {
      //  for (j=0; j < SEATS_PER_ROW; j++) {
        //    seatmap[i][j] = EMPTY_SEAT;
        //}
    //}
   
    /* Declare a Box Office that stores venue information */
    // TODO
    
    /* Make the line for customers to 'line up' to be served by a Seller  */
    PriorityQueue *ticket_line = createPriorityQueue(n);

    /* Generate N Buyer structs */
    printf("*** Generating %d Buyers ***\n", n);
    for (i = 0; i <= n; i++) {

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

        /* Buyer gets in the back of the line */
        add(ticket_line, buyer);
        printf("C%d\n", i);
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
        sellers[i].ticket_line = ticket_line;
        
        PriorityQueue *internal_ticket_line = createPriorityQueue(n);
 
        // TODO Add box_office reference
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
        sellers[i].ticket_line = ticket_line;
        // TODO Add box_office reference
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
        sellers[i].ticket_line = ticket_line;
        // TODO Add box_office reference
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
            if(seatmap[i][j] == NULL){
                printf("%-3s", EMPTY_SEAT);
            }
        }
        printf("%c", NEWLINE);
        fflush(stdout);
    } 

    struct Buyers buyer;
    buyer.priority = 'H';
   // buyer.name[0] = 'f';
//
struct Buyers b2;
b2.priority = "H";
seat_this_buyer(b2);
    seat_this_buyer(buyer);
 //   seatmap[2][3] = &buyer;
struct Buyers m1;
m1.priority = "M";
seat_this_buyer(m1);
 // Printout simulation results
    printf("Seating Chart\n");
    for (i=0; i < NUMBER_OF_ROWS; i++) {
        for (j=0; j < SEATS_PER_ROW; j++) {
            if(seatmap[i][j] == NULL){
                printf("%-3s", EMPTY_SEAT);
            }else
            {
     //       printf("%c", buyer.name[0]);
                printf("%c", seatmap[i][j]->priority);
            }
        }
        printf("%c", NEWLINE);
        fflush(stdout);
    } 


    exit(EXIT_SUCCESS);
}
