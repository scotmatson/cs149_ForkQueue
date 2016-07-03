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
#include <stdbool.h>

/* Business Logic */
static const int NUMBER_OF_SELLERS = 10;
static const int HIGH_PRICE_SELLERS = 1;
static const int MEDIUM_PRICE_SELLERS = 3;
static const int LOW_PRICE_SELLERS = 6;

/* Map Visualization */
static const int NUMBER_OF_ROWS = 10;
static const int SEATS_PER_ROW = 10;
static char * const EMPTY_SEAT = "----";

/* Utility */
static const char NEWLINE = '\n';

//**************************************Customer struct************************************
struct Customer {
    char name[5];
    int arrivalTime;
    int saleTime;
};
//**************************************Seller struct************************************
struct Seller {
    char name[3];
    struct PriorityQueue pq;
};
//**************************************Seat struct**************************************
struct Seat {
    char name[5];
    int row;
    int col;
    bool available;
};
//*****************************Priority Queue struct to hold customers*********************************
typedef struct PriorityQueue
{
    int capacity;//Total number of Customers
    int size;//Number of customers in queue
    int front;//Index of first customer
    int rear;//Index of last customer
    struct customer *customers;//Pointer to customer array
}PriorityQueue;

//CreatePriortityQueue takes the number of customers, and creates
//a PriorityQueue and returns a pointer to the PriorityQueue.
PriorityQueue * createPriorityQueue(int numOfCustomers)
{
        PriorityQueue *PQ;
        PQ = (PriorityQueue*)malloc(sizeof(PriorityQueue));
        //Initialize attributes
        PQ->customers = (struct Customer*)malloc(sizeof(struct Customer) * numOfCustomers);
        PQ->size = 0;
        PQ->capacity = numOfCustomers;
        PQ->front = 0;
        PQ->rear = -1;
        //Return the pointer to the PriorityQueue
        return PQ;
}

struct Customer peek(PriorityQueue *PQ)
{
    return PQ->customers[PQ->front];
}

struct customer poll(PriorityQueue *PQ)
{
    //Removing a customer is just incrementing index of front
    Q->size--;
    Q->front++;
    return PQ->customers[PQ->(front - 1)];
}

void add(PriorityQueue *PQ, struct Customer customer)
{
    int index = PQ->rear;
    while(customer.arrivalTime > PQ->customers[i].arrivalTime && index >= 0)
    {
        PQ->customers[index+1] = PQ->customers[index];
        index--;
    }
    //Finally add the customer in correct space
    PQ->size++;
    PQ->customers[i+1] = customer;
}
//**************************************End code for sturcts************************************


/* Thread stuff that I don't quite understand... yet */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * seller thread to serve one time slice (1 minute)
 */
void * sell(void * sellertype) {
    char  st;
    int clock = 0;
    st = *((char*) sellertype);

    printf("Seller type %c\n", st);

    //while (true) { // Having more work to do...
    while(clock <= 59 && 
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);

        // Serve any buyer available in this seller queue that is ready
        // now to buy ticket till done with all relevant buyers in their queue
        //..................

    }

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

    // Create necessary data structures for the simulator.
    int i, j, rc;
    // A 2D array representing the seats
    char * seatmap[NUMBER_OF_ROWS][SEATS_PER_ROW];
    for (i=0; i < NUMBER_OF_ROWS; i++) {
        for (j=0; j < SEATS_PER_ROW; j++) {
            seatmap[i][j] = EMPTY_SEAT;
        }
    }

    // Priority queues for the 10 Sellers
    PriorityQueue *H0 = createPriorityQueue(n);
    PriorityQueue *M1 = createPriorityQueue(n);
    PriorityQueue *M2 = createPriorityQueue(n);
    PriorityQueue *M3 = createPriorityQueue(n);
    PriorityQueue *L4 = createPriorityQueue(n);
    PriorityQueue *L5 = createPriorityQueue(n);
    PriorityQueue *L6 = createPriorityQueue(n);
    PriorityQueue *L7 = createPriorityQueue(n);
    PriorityQueue *L8 = createPriorityQueue(n);
    PriorityQueue *L9 = createPriorityQueue(n);


    // Create buyers list for each seller ticket queue based on the
    // N value within an hour and have them in the seller queue.
    int seed = time(NULL);
    srand(seed);
    for(i = 1; i <= n; i++)
    {
        //Create H0 customers
        struct Customer h;
        char str[5];
        if(i < 10)
        {
            strcpy(str, "H00");
            strcat(str, i);
        }
        else
        {
            strcpy(str, "H0");
            strcat(str, i);
        }
        h.name = str;
        h.arrivalTime = rand() % 60; //0 to 59
        h.saleTime = rand() % 2 + 1; //1 to 2
        add(H0, h);

        //Create M1 - M3 customers
        for(j = 1; j <= MEDIUM_PRICE_SELLERS; j++)
        {
            struct Customer m;
            char str[5];
            if(i < 10)
            {
                strcpy(str, "M00");
                strcat(str, i);
            }
            else
            {
                strcpy(str, "M0");
                strcat(str, i);
            }
            m.name = str;
            m.arrivalTime = rand() % 60; //0 to 59
            m.saleTime = rand() % 2 + 2; //2 to 4
            char pqName[3]
            strcpy(pqName, "M");
            strcat(pqName, j);
            add(pqName, m);
        }

        //Create L1 - L6 customers
        for(j = 1; j <= LOW_PRICE_SELLERS; j++)
        {
            struct Customer l;
            char str[5];
            if(i < 10)
            {
                strcpy(str, "L00");
                strcat(str, i);
            }
            else
            {
                strcpy(str, "L0");
                strcat(str, i);
            }
            l.name = str;
            l.arrivalTime = rand() % 60; //0 to 59
            l.saleTime = rand() % 4 + 4; //4 to 7
            char pqName[3]
            strcpy(pqName, "L");
            strcat(pqName, j);
            add(pqName, l);
        }
    }


    // Create 10 threads representing the 10 sellers.
    pthread_t tids[10];
    char sellertype;
    sellertype = 'H';
    //Thread id = 0
    for (i = 0; i < 1; i++) {
        rc = pthread_create(&tids[i], NULL, sell, &sellertype);
        if (rc) {
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }
   
    sellertype = 'M';
    //Thread ids = 1-3
    for (i = 1; i < 4; i++) {
        rc = pthread_create(&tids[i], NULL, sell, &sellertype);
        if (rc) {
            fprintf(stderr, "ERROR; return code from pthread_join is %d\n", rc);
            exit(EXIT_FAILURE);
        }
    }

    sellertype = 'L';
    //Thread ids = 4-9
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
