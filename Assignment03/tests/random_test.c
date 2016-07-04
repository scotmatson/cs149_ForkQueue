#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char * argv[]) {
    srand(time(NULL));

    int h, m, l;
    h = rand() % (2 + 1 - 1) + 1;
    m = rand() % (4 + 1 - 2) + 2;
    l = rand() % (7 + 1 - 4) + 4;

    printf("Expecting [1, 2]\n");
    printf("Random H: %d\n\n", h);

    printf("Expecting [2, 4]\n");
    printf("Random M: %d\n\n", m);

    printf("Expecting [4, 7]\n");
    printf("Random M: %d\n\n", l);
}
