#define _POSIX_C_SOURCE 200809L
#define PROCS 5
#include <stdio.h>          /* for printf() */
#include <unistd.h>         /* for pipe(), fork(), and close() */
#include <stdlib.h>         /* for exit(), srand(), rand() */
#include <time.h>           /* For seeing srand() */
#include <mach/mach_time.h> /* For OSX Time Keeping */ 
#include <sys/select.h>     /* For select() */

int main(int argc, char **argv) {
    printf("*** Executing syscall.c ***\n\n");
    fflush(stdout);

    int            i,rv;           /* Reusable counters/return values */
    int            m1,m2,m3,m4,m5; /* Message counters */
    FILE           *fh;            /* File Handler to write piped message */
    char           data;       /* To store proc 5 input from stdin */

    /* Process IDs */
    pid_t          pid;            /* Control  filter for fork() */
    pid_t          p_pid;          /* Parent proc */ 
    pid_t          c_pid[PROCS];   /* Child procs */

    /* Time Management */
    static mach_timebase_info_data_t tb;
    uint64_t       start, stop;
    float          elapsed; 

    /* Start/Set the clocks */
    mach_timebase_info(&tb);
    start = mach_absolute_time();

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
            close(fd[0]); /* Close read side */
            break;
        } 
        else {
            /* Doing this 5 times is a little redundant.... meh */
            p_pid = getpid();
            int fd[2];
            pipe(fd);
            close(fd[1]); /* Close write side */
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
            printf("Process %d is awaiting input...\n>> ", getpid());
            m5++;
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= 1000000000;
            //scanf("%[^\n]%*c", &data);
            //printf("%s", &data);
            // Send through pipe
        }
        else {
            // Parent
            //printf("I am parent %d\n", getpid());
            rv = select(6, &fds, NULL, NULL, NULL); /* Think this goes here */
            switch(rv) {
                case -1:
                    fprintf(stderr, "ERROR; Unable to select file descriptor\n");
                    exit(1);
                    break;
                case 1:
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
