#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char * argv[]) {

    int i;
    for (i = 0; i < argc; i++) {
        if (isdigit(*argv[i])) {
            printf("%s is a digit!\n", argv[i]);
        }
        else {
            printf("%s is NOT a digit...\n", argv[i]);
        }
    }

    exit(EXIT_SUCCESS);
}
