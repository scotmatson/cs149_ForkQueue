#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {

    printf("argc: %d\n", argc);    


    printf("argv:\n");
    int i;
    for (i = 0; i < argc; i++) {
        printf("%-1s* %s\n", "", argv[i]);
    }

    exit(0);
}
