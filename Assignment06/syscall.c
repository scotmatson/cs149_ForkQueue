#define _POSIX_C_SOURCE 200809L
#include <stdio.h>    /* for printf() */
#include <unistd.h>   /* for pipe(), fork(), and close() */
#include <stdlib.h>   /* for exit(), srand(), rand() */
#include <time.h>     /* For seeing srand() */
#include <mach/mach_time.h> 

int main(int argc, char **argv) {
    printf("*** Executing syscall.c ***\n\n");
    fflush(stdout);

    /*
     * To create a simple pipe, we use the pip() system call which
     * takes a single argument - an Array with two integers.
     *
     * The first integer (element 0) is for reading.
     * The second integer (element 1) is for writing.
     *
     * Note: 1. The output for fd[1] becomes the input for fd[0].
     *       2. All data travelling through the pipe moves 
     *          through the kernel.
    */
    int      i;            /* Counter */
    //int      fd[2];      /* File Descripter for the pipes */
    pid_t    pid;          /* Temp Process ID for control filter */
    pid_t    ppid;         /* Process ID for parent fork */ 
    pid_t    cpid[5];      /* Process ID for child forks */
    char     data;         /* Data to pass between pipes */
    FILE     *fh;          /* File Handler */


    /* Time Management */
    static mach_timebase_info_data_t tb;
    uint64_t start, stop;
    float    elapsed; 

    /* Start the clock */
    mach_timebase_info(&tb);
    start = mach_absolute_time();

    /* Accepting user input */
    printf("Awaiting input... ");
    scanf("%[^\n]%*c", &data);
    printf("\n%s\n", &data);
    fflush(stdout);

    //pipe(fd); /* fd is equivilent to &fd[0] */

    fh = fopen("out/output.txt", "w");
    if (fh == NULL) {
        fprintf(stderr, "ERROR; Unable to open file\n");
        exit(1);
    }

    for (i = 0; i < 5; i++) {
        if ((pid = fork()) < 0) {
            perror("ERROR; Unable to fork this process");
            exit(1);
        } 
        else if (pid == 0) {
            printf("I am child #%d, my pid is %d\n", i, getpid());
            fflush(stdout);
            cpid[i] = getpid();
            int fd[2]; /* File Descripter for the pipes */
            pipe(fd);
            close(fd[0]); /* [0] to send, [1] to recieve */
            break;
        } 
        else {
            /* TODO:Uses select() to determine if pipe has input */
            printf("I am the parent. my pid is %d\n", getpid());
            fflush(stdout);
            //fprintf(fh, "I am the parent, my pid is %d", getpid());
            
            /* Doing this 5 times is a little redundant.... */
            ppid = getpid();
            int fd[2];
            pipe(fd);
            close(fd[1]); /* [0] to send, [1] to receive */
        }
    }

    /* Test to see if we can access processes in the array */
    for (i = 0; i < 5; i++) {
        if (cpid[i] == getpid()) {
            printf("I am %d, it is my turn to speak!\n", getpid());
        }
    }
    if (ppid == getpid()) {
        printf("I am %d, the almighty creator!\n", getpid());
    }


    srand(time(NULL)); /* Seed after fork to ensure randomness */
    /*
    For 30 seconds, read user input,
    while () {

        sleep(rand() % 3);
        printf("Process %d waking back up\n", getpid());
    }
    */

    /* Calculate elapsed time and format */
    stop = mach_absolute_time();
    elapsed = (float)(stop-start) * tb.numer/tb.denom;
    elapsed /= 1000000000;
    //printf("Elapsed time for process %d: 00:%.4f\n", getpid(), elapsed);
    //fflush(stdout);
    fclose(fh);
    exit(0);
}
