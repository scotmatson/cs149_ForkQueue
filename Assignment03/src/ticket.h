#ifndef _ticket_h
#define _ticket_h

typedef struct ticket {
    int ticket_type;             // is this a H, M, or L ticket
    char sold_by;                 // name of ticket seller: H1, M2, L3, etc
    int seat_number;             // 
    bool availability;
};

#endif
