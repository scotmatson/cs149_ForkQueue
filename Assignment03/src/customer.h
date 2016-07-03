#ifndef CUSTOMER_H_
#define CUSTOMER_H_

struct customer {
    char* priority;
    char name[25];
    char seller_name[25];
    double wait_time;
    double start_time;
    double end_time;
    bool boughtTicket;
    int seat_number;
};

#endif // CUSTOMER_H_


