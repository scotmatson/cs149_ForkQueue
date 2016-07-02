#include <stdio.h>

static const int NUMBER_OF_ROWS = 10;
static const int SEATS_PER_ROW  = 10;
static char * const EMPTY_SEAT = "--";

int main(int argc, char * argv[]) {
    
    printf("Number of rows: %d\n", NUMBER_OF_ROWS);
    printf("Seats per row:  %d\n", SEATS_PER_ROW);

    char * seatmap[NUMBER_OF_ROWS][SEATS_PER_ROW];
    
    int i, j;
    for (i=0; i < NUMBER_OF_ROWS; i++) {
        for (j=0; j < SEATS_PER_ROW; j++) {
            seatmap[i][j] = EMPTY_SEAT;
            printf("%-3s", seatmap[i][j]);
        }
        printf("\n");
    }
}
