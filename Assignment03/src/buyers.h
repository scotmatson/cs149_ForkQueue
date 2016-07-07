#ifndef BUYERS_H
#define BUYERS_H
struct Buyers {
    char name[5];
    char seller_name[3];
    char priority;
    int arrival_time;
    int sale_time;
    int sale_start_time;
    int sale_end_time;
    int service_time;
};
#endif /* BUYERS_H */


