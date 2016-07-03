#ifndef TICKET_H_
#define TICKET_H_

struct ticket {
    char seller_name[25];
    char customer_name[25];
    char* priority;;
    int seat_number;
    bool availability;
};

#endif // TICKET_H_
