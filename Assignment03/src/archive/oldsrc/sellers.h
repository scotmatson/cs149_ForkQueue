#ifndef SELLERS_H
#define SELLERS_H
struct Sellers {
    char type; // priority of seller; eg, 'L', 'M', 'H'
    int service_time;
    PriorityQueue *ticket_line;
    //double avg_service_time;
    //char* priority; //Priority of seller. H, M, or L
    //char customerQueue[200]; //Customer line for the seller
};
#endif /* SELLERS_H */
