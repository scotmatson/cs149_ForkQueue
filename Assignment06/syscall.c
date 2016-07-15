#include <stdio.h>  /* for printf() */
#include <unistd.h> /* for pipe(), fork(), and close() */
#include <stdlib.h> /* for exit() */

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
    int     i;
    int     fd[2];
    pid_t   pid;
    char    data;

    /* Accepting user input */
    printf("Awaiting input... ");
    scanf("%[^\n]%*c", &data);
    printf("\n%s\n", &data);
    fflush(stdout);

    /* Generating 5 pipes */
    pipe(fd); // fd is equivilent to &fd[0]
    //pipe(fd);
    //pipe(fd);
    //pipe(fd);
    //pipe(fd);

    /* Creating forked processes */
    if ((pid = fork()) < 0) {
        /* Err: Unable to Fork */
        perror("fork");
        exit(1);
    } 
    /* 
     * For parent to receive data from child,
     * Parent closes fd[1]
     * Child closes fd[0]
     *
     * For parent to send data to child,
     * Parent closes fd[0]
     * Child closes fd[1]
     */
    else if (pid == 0) {
        /* Child Process */
        printf("I am the child, my pid is %d\n", getpid());
        fflush(stdout);
        close(fd[0]); 
    } 
    else {
        /* Parent Process */
        printf("I am the parent. my pid is %d\n", getpid());
        fflush(stdout);
        close(fd[1]);
    }

    printf("Terminating process %d\n", getpid());
    fflush(stdout);
    exit(0);
}
