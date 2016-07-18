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
    int      i;              /* Reusable counter */
    int      m1,m2,m3,m4,m5; /* Message counters */
    FILE     *fh;            /* File Handler to write piped message */
    char     data[20];       /* To store user input */
    pid_t    pid;            /* Temp Process ID for control filter */
    pid_t    p_pid;          /* Process ID for parent fork */ 
    pid_t    c_pid[5];       /* Process ID for child forks */

    /* Time Management */
    static mach_timebase_info_data_t tb;
    uint64_t start, stop;
    float    elapsed; 

    /* Start the clock */
    mach_timebase_info(&tb);
    start = mach_absolute_time();

    /* IO for parent process */
    fh = fopen("out/output.txt", "w");
    if (fh == NULL) {
        fprintf(stderr, "ERROR; Unable to open file\n");
        exit(1);
    }

    /* Fork processes */
    for (i = 0; i < 5; i++) {
        if ((pid = fork()) < 0) {
            perror("ERROR; Unable to fork this process");
            exit(1);
        } 
        else if (pid == 0) {
            c_pid[i] = getpid();
            int fd[2]; /* File Descripter for the pipes */
            pipe(fd);
            close(fd[0]); /* [0] to send, [1] to recieve */
            break;
        } 
        else {
            /* Doing this 5 times is a little redundant.... meh */
            p_pid = getpid();
            int fd[2];
            pipe(fd);
            close(fd[1]); /* [0] to send, [1] to receive */
        }
    }

    /*while (30 seconds) {*/
    srand(time(NULL));
    if (getpid() == c_pid[0]) {
        sprintf(data, "I am child %d\n", getpid());
        write(fd[0], data,sizeof(data));
    }    
    else 
    if (getpid() == c_pid[1]) {
        printf("I am child %d\n", getpid());
        fflush(stdout);
    }
    else
    if (getpid() == c_pid[2]) {
        printf("I am child %d\n", getpid());
        fflush(stdout);
    }
    else
    if (getpid() == c_pid[3]) {
        printf("I am child %d\n", getpid());
        fflush(stdout);
    }
    else
    if (getpid() == c_pid[4]) {
        printf("I am child %d\n", getpid());
        printf("Awaiting input... ");
        fflush(stdout);
        //scanf("%[^\n]%*c", &data);
    }
    else {
        // Parent
        printf("I am parent %d\n", getpid());
        //fprintf(fh, "I am the parent, my pid is %d", getpid());
        wait(NULL);
    }
    sleep(rand() % 3);
    //printf("Process %d waking back up\n", getpid());
    /*}*/

    /* Calculate elapsed time and format */
    stop = mach_absolute_time();
    elapsed = (float)(stop-start) * tb.numer/tb.denom;
    elapsed /= 1000000000;
    printf("Elapsed time for process %d: 00:%.4f\n", getpid(), elapsed);
    fflush(stdout);

    fclose(fh);
    exit(0);
}
