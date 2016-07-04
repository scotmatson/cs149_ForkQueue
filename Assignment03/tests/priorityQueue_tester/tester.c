#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "arrivalPriorityQueue.h"
#include "buyers.h"

/* Business Logic */
static const int NUMBER_OF_SELLERS = 10;
static const int HIGH_PRICE_SELLERS = 1;
static const int MEDIUM_PRICE_SELLERS = 3;
static const int LOW_PRICE_SELLERS = 6;

int main(int argc, char * argv[]) {
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

    // Priority queues for the 10 Sellers
    PriorityQueue *H0 = createPriorityQueue(n);
    PriorityQueue *M1 = createPriorityQueue(n);
    PriorityQueue *M2 = createPriorityQueue(n);
    PriorityQueue *M3 = createPriorityQueue(n);
    PriorityQueue *L1 = createPriorityQueue(n);
    PriorityQueue *L2 = createPriorityQueue(n);
    PriorityQueue *L3 = createPriorityQueue(n);
    PriorityQueue *L4 = createPriorityQueue(n);
    PriorityQueue *L5 = createPriorityQueue(n);
    PriorityQueue *L6 = createPriorityQueue(n);

    // Create buyers list for each seller ticket queue based on the
    // N value within an hour and have them in the seller queue.
    int seed = time(NULL);
    srand(seed);
    int i, j;
    for(i = 1; i <= n; i++)
    {
        //Create H0 customers
        struct Buyers h;
        char str[5];
        char strNum[5];
        if(i < 10)
        {
            strcpy(str, "H00");
            sprintf(strNum, "%d", i);
            strcat(str, strNum);
        }
        else
        {
            strcpy(str, "H0");
            sprintf(strNum, "%d", i);
            strcat(str, strNum);
        }
        strcpy(h.name, str);
        h.arrival_time = rand() % 60; //0 to 59
        h.sale_time = rand() % 2 + 1; //1 to 2 /* 
        add(H0, h);

        //Create M1 - M3 customers
        for(j = 1; j <= MEDIUM_PRICE_SELLERS; j++)
        {
            struct Buyers m;
            char str[5];
            switch(j){
                case 1:
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
                    m.arrival_time = rand() % 60; //0 to 59
                    m.sale_time = rand() % 2 + 2; //2 to 4
                    add(M1, m);
                    break;
                case 2:
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
                    m.arrival_time = rand() % 60; //0 to 59
                    m.sale_time = rand() % 2 + 2; //2 to 4
                    add(M2, m);
                    break;
                case 3:
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
                    m.arrival_time = rand() % 60; //0 to 59
                    m.sale_time = rand() % 2 + 2; //2 to 4
                    add(M3, m);
                    break;
                default:
                    break;
            }
        }

        //Create L1 - L6 customers
        for(j = 1; j <= LOW_PRICE_SELLERS; j++)
        {
            struct Buyers l;
            char str[5];
            switch(j){
                case 1:
                    if(i < 10)
                    {
                        strcpy(str, "L10");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else
                    {
                        strcpy(str, "L1");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    l.arrival_time = rand() % 60; //0 to 59
                    l.sale_time = rand() % 4 + 4; //4 to 7
                    add(L1, l);
                    break;
                case 2:
                    if(i < 10)
                    {
                        strcpy(str, "L20");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else
                    {
                        strcpy(str, "L2");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    l.arrival_time = rand() % 60; //0 to 59
                    l.sale_time = rand() % 4 + 4; //4 to 7
                    add(L2, l);
                    break;
                case 3:
                    if(i < 10)
                    {
                        strcpy(str, "L30");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else
                    {
                        strcpy(str, "L3");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    l.arrival_time = rand() % 60; //0 to 59
                    l.sale_time = rand() % 4 + 4; //4 to 7
                    add(L3, l);
                    break;
                case 4:
                    if(i < 10)
                    {
                        strcpy(str, "L40");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else
                    {
                        strcpy(str, "L4");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    l.arrival_time = rand() % 60; //0 to 59
                    l.sale_time = rand() % 4 + 4; //4 to 7
                    add(L4, l);
                    break;
                case 5:
                    if(i < 10)
                    {
                        strcpy(str, "L50");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else
                    {
                        strcpy(str, "L5");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    l.arrival_time = rand() % 60; //0 to 59
                    l.sale_time = rand() % 4 + 4; //4 to 7
                    add(L5, l);
                    break;
                case 6:
                    if(i < 10)
                    {
                        strcpy(str, "L60");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    else
                    {
                        strcpy(str, "L6");
                        sprintf(strNum, "%d", i);
                        strcat(str, strNum);
                    }
                    strcpy(l.name, str);
                    l.arrival_time = rand() % 60; //0 to 59
                    l.sale_time = rand() % 4 + 4; //4 to 7
                    add(L6, l);
                    break;
                default:
                    break;
            }
        }
    }

    //Test print outs to show that priority queue is working
    while(!isEmpty(H0))
    {
        struct Buyers b = poll(H0);
        printf("\nBuyer name = " );
        printf("%s", b.name);
        printf("\nArrival time = " );
        printf("%d", b.arrival_time);
        printf("\nSale time = " );
        printf("%d", b.sale_time);
        fflush(stdout);
    }
    printf("\n\n");

    while(!isEmpty(M1))
    {
        struct Buyers b = poll(M1);
        printf("\nBuyer name = " );
        printf("%s", b.name);
        printf("\nArrival time = " );
        printf("%d", b.arrival_time);
        printf("\nSale time = " );
        printf("%d", b.sale_time);
        fflush(stdout);
    }
    printf("\n\n");

    while(!isEmpty(M3))
    {
        struct Buyers b = poll(M3);
        printf("\nBuyer name = " );
        printf("%s", b.name);
        printf("\nArrival time = " );
        printf("%d", b.arrival_time);
        printf("\nSale time = " );
        printf("%d", b.sale_time);
        fflush(stdout);
    }
    printf("\n\n");

    while(!isEmpty(L5))
    {
        struct Buyers b = poll(L5);
        printf("\nBuyer name = " );
        printf("%s", b.name);
        printf("\nArrival time = " );
        printf("%d", b.arrival_time);
        printf("\nSale time = " );
        printf("%d", b.sale_time);
        fflush(stdout);
    }
    printf("\n\n");
}
