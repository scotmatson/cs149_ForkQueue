#define _POSIX_C_SOURCE 200809L
#include <stdio.h>    /* for printf() */
#include <unistd.h>   /* for pipe(), fork(), and close() */
#include <stdlib.h>   /* for exit() */
#include <mach/mach_time.h>
/*
 * TODO: (1) Main must read from multiple files.
 *       (2) Main must read from the terminal.
 *
 * Definitions:
 *    (1) Pipe: A system call that creates a unidirecitonal
 *        communication link between two file descriptors.
 *    (2) Multiplexing: A way of sending multiple signals over
 *        a communications link at the same time. 
 *
 * References:
 *    (1) Creating Pipes in C 
 *        http://tldp.org/LDP/lpg/node11.html
 *    (2) C Tutorial: Pipes
 *        https://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/pipes.html
 *
 */
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
    int      i;           /* Counter */
    int      fd[2];       /* File Descripter for the pipes */
    pid_t    pid;         /* Process ID for the forks */
    char     data;        /* Data to pass between pipes */

    /* Time Management */
    static mach_timebase_info_data_t tb;
    uint64_t start, stop;
    float    elapsed; 
    mach_timebase_info(&tb);

    start = mach_absolute_time(); /* Starts the clock */

    /* Accepting user input */
    printf("Awaiting input... ");
    scanf("%[^\n]%*c", &data);
    printf("\n%s\n", &data);
    fflush(stdout);

    pipe(fd); /* fd is equivilent to &fd[0] */
    /*
    pipe(fd);
    pipe(fd);
    pipe(fd);
    pipe(fd);
    */
    if ((pid = fork()) < 0) {
        perror("ERR; Unable to fork this process");
        exit(1);
    } 
    else if (pid == 0) {
        printf("I am the child, my pid is %d\n", getpid());
        fflush(stdout);
        close(fd[0]); /* [0] to send, [1] to recieve */
    } 
    else {
        printf("I am the parent. my pid is %d\n", getpid());
        fflush(stdout);
        close(fd[1]); /* [0] to send, [1] to receive */
    }

    /* Calculate elapsed time and format */
    stop = mach_absolute_time();
    elapsed = (float)(stop-start) * tb.numer/tb.denom;
    elapsed /= 1000000000;
    printf("Elapsed time for process %d: %.4f\n", getpid(), elapsed);
    fflush(stdout);
    exit(0);
}
