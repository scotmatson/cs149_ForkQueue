#ifndef SELLER_H
#define SELLER_H
struct Sellers {
    // service times: there is a min/max per seller-type, but a random service time must be
    // generated for each individual ticket-sold event
    int  min_service_time;
    int  max_service_time;
    double avg_service_time;
    char* name[3]; //Name of seller. E.G M1 or L3
    char* priority; //Priority of seller. H, M, or L
    char customerQueue[200]; //Customer line for the seller
};
#endif /* SELLER_H */
