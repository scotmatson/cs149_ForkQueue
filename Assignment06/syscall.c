#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * References:
 *    (1) Creating Pipes in C 
 *        http://tldp.org/LDP/lpg/node11.html
 *
 *
 */
int main(int argc, char *argv[]) {
    printf("*** Executing syscall.c ***\n\n");

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
    int     fd[2];
    pid_t   pid;

    pipe(fd); // fd is equivilent to &fd[0]

    if ((pid = fork()) < 0) {
        /* Err: Unable to Fork */
        perror("fork");
        exit(1);
    } 
    /* 
     * For parent to receive data from child,
     * Parent closes fd[1]
     * Child closes fd[0]
     */
    else if (pid == 0) {
        /* Child Process */
        printf("I am the child\n");
        close(fd[0]); 
    } 
    else {
        /* Parent Process */
        printf("I am the parent.\n");
        close(fd[1]);
    }


}
