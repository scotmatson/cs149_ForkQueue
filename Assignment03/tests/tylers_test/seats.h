#ifndef TICKET_H
#define TICKET_H
struct Tickets {
    char seller_name[25];
    char customer_name[25];
    char* priority;;
    int seat_number;
    bool availability;
};
#endif /* TICKET_H */
