#define _POSIX_C_SOURCE 200809L
#define PROCS 6             /* Number of processes (including parent)*/
#define PIPES 2             /* Pipes per process(read/write) */
#include <stdio.h>          /* for printf() */
#include <unistd.h>         /* for pipe(), fork(), and close() */
#include <stdlib.h>         /* for exit(), srand(), rand() */
#include <time.h>           /* For seeing srand() */
#include <mach/mach_time.h> /* For OSX Time Keeping */ 
#include <sys/select.h>     /* For select() */
#include <string.h>         /* For strcpy() */

int main(int argc, char **argv) {
    printf("*** Executing syscall.c ***\n\n");
    fflush(stdout);

    int            i, retval;      /* Reusable counters/return values */
    int            m1,m2,m3,m4,m5; /* Message counters */
    FILE           *fh;            /* File Handler to write piped message */

    /* Process IDs */
    pid_t          pid;            /* Control  filter for fork() */
    pid_t          p_pid;          /* Parent proc */ 
    pid_t          c_pid[PROCS-1];   /* Child procs */

    /* Time Management */
    static mach_timebase_info_data_t tb;
    uint64_t       start, stop;
    float          elapsed; 

    /* Start/Set the clocks */
    mach_timebase_info(&tb);
    start = mach_absolute_time();

    /* Prepare the File Descriptors for piping */
    struct fd_set socket;
    int fds[PROCS][PIPES];
    FD_ZERO(&socket);
    for (i = 0; i < PROCS; i++) {
        FD_SET(*fds[i], &socket);
    }

    /* IO for parent process */
    fh = fopen("out/output.txt", "w");
    if (fh == NULL) {
        fprintf(stderr, "ERROR; Unable to open file\n");
        exit(1);
    }

    /* Fork processes */
    for (i = 0; i < PROCS-1; i++) {
        if ((pid = fork()) < 0) {
            perror("ERROR; Unable to fork this process");
            exit(1);
        } 
        else if (pid == 0) {
            c_pid[i] = getpid();
            int fd[2]; /* File Descripter for the pipes */
            close(fds[i][0]); /* Close read side */
            pipe(fds[i]);
            break;
        } 
        else {
            /* Doing this 5 times is a little redundant.... meh */
            p_pid = getpid();
            close(fds[5][1]); /* Close write side */
            pipe(fds[5]);
        }
    }

    /* Last chance to initialize any variables */
    m1=m2=m3=m4=m5=0;
    /* do { */
        /* Loop runs for 30 seconds (real time) */
        srand(time(NULL));
        if (getpid() == c_pid[0]) {
            m1++;
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= 1000000000;

            /* Sending through pipe */
            //char msg[] = "Message from child.\n";
            //printf("Child: Sending my message\n");
            //write(fd1[0], msg, sizeof(msg));
            //printf("Child: Message has been sent\n");
        }    
        else 
        if (getpid() == c_pid[1]) {
            m2++;
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= 1000000000;
            // Send through pipe
        }
        else
        if (getpid() == c_pid[2]) {
            m3++;
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= 1000000000;
            // Send through pipe
        }
        else
        if (getpid() == c_pid[3]) {
            m4++;
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= 1000000000;
            // Send through pipe
        }
        else
        if (getpid() == c_pid[4]) {
            //printf("Process %d is awaiting input...\n>> ", getpid());
            m5++;
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= 1000000000;

            char msg5[20];
            //scanf("%[^\n]%*c", msg5);
            // Send through pipe
            //write(fd5[0], msg5, sizeof(msg5));
        }
        else {
            // Parent
            //printf("I am parent %d\n", getpid());
            printf("Parent: Selecting pipe from which to read\n");
            fflush(stdout);
            retval = select(6, &socket, NULL, NULL, NULL); /* Think this goes here */
            printf("Parent: I have made my selection\n");
            fflush(stdout);
            switch(retval) {
                case -1:
                    fprintf(stderr, "ERROR; Unable to select file descriptor\n");
                    exit(1);
                    break;
                case 1:
                    printf("\nfd0w is %d\n", FD_ISSET(fds[0][0], &socket));
                    printf("fd1w is %d\n", FD_ISSET(fds[1][0], &socket));
                    printf("fd2w is %d\n", FD_ISSET(fds[2][0], &socket));
                    printf("fd3w is %d\n", FD_ISSET(fds[3][0], &socket));
                    printf("fd4w is %d\n", FD_ISSET(fds[4][0], &socket));
                    printf("fd5w is %d\n", FD_ISSET(fds[5][0], &socket));
                    fflush(stdout);

                    printf("\nfd0r is %d\n", FD_ISSET(fds[0][1], &socket));
                    printf("fd1r is %d\n", FD_ISSET(fds[1][1], &socket));
                    printf("fd2r is %d\n", FD_ISSET(fds[2][1], &socket));
                    printf("fd3r is %d\n", FD_ISSET(fds[3][1], &socket));
                    printf("fd4r is %d\n", FD_ISSET(fds[4][1], &socket));
                    printf("fd5r is %d\n", FD_ISSET(fds[5][1], &socket));
                    fflush(stdout);

                    //printf("Parent is going to read from the pipe\n");
                    stop = mach_absolute_time();
                    elapsed = (float)(stop-start) * tb.numer/tb.denom;
                    elapsed /= 1000000000;
                    /* read proc data */
                    //fprintf(fh, "I am the parent, my pid is %d", getpid());
                    break;
                default:
                    printf("No data to be read from the pipe\n");
                    break;
            }
        }
        sleep(rand() % 3);
        //printf("Process %d waking back up\n", getpid());
    /*} while(30 second counter); */

    fclose(fh); 
    exit(0);
}
