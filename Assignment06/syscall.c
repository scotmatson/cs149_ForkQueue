#define _POSIX_C_SOURCE 200809L
#define PROCS 5
#include <stdio.h>    /* for printf() */
#include <unistd.h>   /* for pipe(), fork(), and close() */
#include <stdlib.h>   /* for exit(), srand(), rand() */
#include <time.h>     /* For seeing srand() */
#include <mach/mach_time.h> 
#include <sys/select.h>


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
    int            i,rv;           /* Reusable counters/return values */
    int            m1,m2,m3,m4,m5; /* Message counters */
    FILE           *fh;            /* File Handler to write piped message */
    char           data[20];       /* To store user input */
    pid_t          pid;            /* Temp Process ID for control filter */
    pid_t          p_pid;          /* Process ID for parent fork */ 
    pid_t          c_pid[PROCS];       /* Process ID for child forks */

    /* Time Management */
    static mach_timebase_info_data_t tb;
    uint64_t       start, stop;
    float          elapsed; 
    struct timeval timeout;        /* To timeout running processes */

    /* Start/Set the clocks */
    mach_timebase_info(&tb);
    start = mach_absolute_time();
    timeout.tv_sec = 30;           /* 30 Seconds */

    /* Prepare the File Descriptors for piping */
    struct fd_set fds;
    int           fd1[2],
                  fd2[2],
                  fd3[2],
                  fd4[2],
                  fd5[2];
    FD_ZERO(&fds);
    FD_SET(*fd1, &fds);
    FD_SET(*fd2, &fds);
    FD_SET(*fd3, &fds);
    FD_SET(*fd4, &fds);
    FD_SET(*fd5, &fds);

    /* IO for parent process */
    fh = fopen("out/output.txt", "w");
    if (fh == NULL) {
        fprintf(stderr, "ERROR; Unable to open file\n");
        exit(1);
    }

    /* Fork processes */
    for (i = 0; i < PROCS; i++) {
        if ((pid = fork()) < 0) {
            perror("ERROR; Unable to fork this process");
            exit(1);
        } 
        else if (pid == 0) {
            c_pid[i] = getpid();
            int fd[2]; /* File Descripter for the pipes */
            //fds[0] = *fd;
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

    m1=m2=m3=m4=m5=0;
    /* do { */
        srand(time(NULL));
        if (getpid() == c_pid[0]) {
            m1++;
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= 1000000000;
            // Send through pipe
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
            printf("Awaiting input... ");
            fflush(stdout);
            m5++;
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= 1000000000;
        //scanf("%[^\n]%*c", &data);
        // Send through pipe
        }
        else {
            // Parent
            printf("I am parent %d\n", getpid());
            rv = select(5+1, &fds, NULL, NULL, &timeout); /* Think this goes here */
            switch(rv) {
                case -1:
                    fprintf(stderr, "ERROR; Unable to select file descriptor\n");
                    break;
                case 1:
                    stop = mach_absolute_time();
                    elapsed = (float)(stop-start) * tb.numer/tb.denom;
                    elapsed /= 1000000000;
                    /* read proc data */
                    //fprintf(fh, "I am the parent, my pid is %d", getpid());
                    break;
                default:
                    printf("No data to be written\n");
                    break;
            }
        }
        sleep(rand() % 3);
        printf("Process %d waking back up\n", getpid());
    /*} while(30 second counter); */

    fclose(fh); 
    exit(0);
}
