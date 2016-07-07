#ifndef SEATMAP_H
#define SEATMAP_H
#define NUM_OF_ROWS  10			
#define SEATS_PER_ROW 10		

#include "buyers.h"

/*
 *   seatmap is an array of char*, which hold the id of whoever bought a
 *   ticket, or no one. 
*/
struct Seatmap {
	struct Buyers* seatmap[NUM_OF_ROWS][SEATS_PER_ROW]; // records who owns seat
};


// function to get a seat from a particular section H M L
int sell_seat(struct Seatmap* map, struct Buyers* b);

// function to set a seat as sold, or return error if no more seats
int set_seat(struct Seatmap* map, struct Buyers* b);


//function to printout the seat map in ascii
void print_seatmap(struct Seatmap* map);

// constructor for seatmap 
void initialize_seatmap(struct Seatmap* map);
#endif /* SEATMAP_H */
