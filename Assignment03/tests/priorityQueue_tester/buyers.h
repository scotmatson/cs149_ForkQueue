#ifndef BUYERS_H
#define BUYERS_H
struct Buyers {
//char* priority;
    int priority; // Changed priority from char to int. 1 = high, 2 = med, 3 = low
    char name[25];
    char seller_name[25];
    double wait_time;
    double start_time;
    double end_time;
    bool boughtTicket;
    int seat_number;
    int arrival_time;
    int sale_time;
};
#endif /* CUSTOMER_H */


