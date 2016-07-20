#define _POSIX_C_SOURCE 200809L
#define PROCS 5             /* Number of processes (including parent)*/
#define PIPES 2             /* Pipes per process(read/write) */
#define MILLI 1000000000    /* Division needed to convert time to milliseconds */
#define READ  0             /* Read side for File Descriptors */
#define WRITE 1             /* Write side for File Descriptors */
#include <stdio.h>          /* for printf() */
#include <unistd.h>         /* for pipe(), fork(), and close() */
#include <stdlib.h>         /* for exit(), srand(), rand() */
#include <time.h>           /* For seeing srand() */
#include <mach/mach_time.h> /* For OSX Time Keeping */ 
#include <sys/select.h>     /* For select() */
#include <string.h>         /* For strcpy() */
#include <fcntl.h>          /* To disable blocking */

int main() {
    printf("*** Executing syscall.c ***\n\n");
    fflush(stdout);
 
    int            i, retval;      /* Reusable counters/return values */
    int            m0,m1,m2,m3,m4; /* Message counters */
    char           readBuffer[20]; /* Buffer for parent to read from pipe */
    FILE           *fh;            /* File Handler to write piped message */

    /* Process IDs */
    pid_t          pid;          /* Control  filter for fork() */
    pid_t          p_pid;        /* Parent proc */ 
    pid_t          c_pid[PROCS]; /* Child procs */

    /* Time Management */
    static mach_timebase_info_data_t tb;
    uint64_t       start, stop;
    float          elapsed; 
    struct timeval timeout;

    /* Start/Set the clocks */
    mach_timebase_info(&tb);
    start = mach_absolute_time();
    timeout.tv_sec  = 3;
    timeout.tv_usec = 0;

    /* Setup file descriptors */
    struct fd_set socket;
    int fds[PROCS][PIPES];
    FD_ZERO(&socket);
    for (i = 0; i < PROCS; i++) {
        FD_SET(*fds[i], &socket);
        pipe(fds[i]);
    }

    /* Fork parent process */
    for (i = 0; i < PROCS; i++) {
        if ((pid = fork()) < 0) {
            fflush(stdout);
            perror("ERROR; Unable to fork this process");
            fflush(stdout);
            exit(1);
        } 
        else if (pid == 0) {
            c_pid[i] = getpid();      /* Store child process ID */
            close(fds[i][READ]);      /* Close read side */
            break;                    /* Break here, we don't want children looping */
        } 
        else {
            p_pid = getpid();
            //close(fds[i][WRITE]);
        }
    }

    /* IO for parent process */
    fh = fopen("out/output.txt", "w");
    if (fh == NULL) {
        fprintf(stderr, "ERROR; Unable to open file\n");
        exit(1);
    }

    /* Last chance to initialize any variables */
    m0=m1=m2=m3=m4=0;
    i = 0;
    while (i < 10) {
        i++;
        /* Loop runs for 30 seconds (real time) */
        srand(time(NULL));
        if (getpid() == c_pid[0]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= MILLI;
            m0++;

            /* Sending through pipe */
            char buf0[30];
            snprintf(buf0, sizeof(buf0), "0:%02f: Child 1 message %d\n", elapsed, m0);
            write(fds[0][WRITE], &buf0, sizeof(buf0));
        }    
        else 
        if (getpid() == c_pid[1]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= MILLI;
            m1++;

            // Send through pipe
            char buf1[30];
            snprintf(buf1, sizeof(buf1), "0:%02f: Child 2 message %d\n", elapsed, m1);
            write(fds[1][WRITE], &buf1, sizeof(buf1));
        }
        else
        if (getpid() == c_pid[2]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= MILLI;
            m2++;
            
            // Send through pipe
            char buf2[30];
            snprintf(buf2, sizeof(buf2), "0:%02f: Child 3 message %d\n", elapsed, m2);
            write(fds[2][WRITE], &buf2, sizeof(buf2));
        }
        else
        if (getpid() == c_pid[3]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= MILLI;
            m3++;

            // Send through pipe
            char buf3[30];
            snprintf(buf3, sizeof(buf3), "0:%02f: Child 4 message %d\n", elapsed, m3);
            write(fds[3][WRITE], &buf3, sizeof(buf3));
        }
        else
        if (getpid() == c_pid[4]) {
            //printf("Process %d is awaiting input...\n>> ", getpid());
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= MILLI;
            m4++;

            // Send through pipe
            //char msg5[30];
            //scanf("%[^\n]%*c", msg5);
            //write(fd5[0], msg5, sizeof(msg5));
        }
        else {
            /* Parent process */
            retval = select(6, &socket, NULL, NULL, &timeout);
            switch(retval) {
                case -1:
                    fprintf(stderr, "ERROR; Unable to select file descriptor\n");
                    exit(1);
                    break;
                case 1:
                    printf("Parent: I have chosen a pipe!!\n");
                    if (FD_ISSET(fds[0][READ], &socket)) {
                        read(fds[0][READ], readBuffer, sizeof(readBuffer));
                        printf("RB: %s\n", readBuffer);
                    }
                    else
                    if (FD_ISSET(fds[1][READ], &socket)) {
                        read(fds[1][READ], readBuffer, sizeof(readBuffer));
                        printf("RB: %s\n", readBuffer);
                    }
                    else
                    if (FD_ISSET(fds[2][READ], &socket)) {
                        read(fds[2][READ], readBuffer, sizeof(readBuffer));
                        printf("RB: %s\n", readBuffer);
                    }
                    else
                    if (FD_ISSET(fds[3][READ], &socket)) {
                        read(fds[3][READ], readBuffer, sizeof(readBuffer));
                        printf("RB: %s\n", readBuffer);
                    }

                    stop = mach_absolute_time();
                    elapsed = (float)(stop-start) * tb.numer/tb.denom;
                    elapsed /= MILLI;

                    /* SAVE FOR NOW */
                    /* 
                    Need to prefix message with parent time,
                    i.e., time - child message
                          time - child message ...
                    */
                    /* read proc data */
                    //read(p_fd[0], readBuffer, sizeof(readBuffer)); /* Not getting child message :( */
                    //printf("RB: %s\n", readBuffer);
                    //fprintf(fh, "%s\n", readBuffer); 
                    break;
                default:
                    printf("No data to be read from the pipe\n");
                    break;
            }
        }
        sleep(rand() % 3);
    }

    /* Close all IO */
    for (i = 0; i < PROCS; i++) {
        close(fds[i][READ]);
        close(fds[i][WRITE]);
    }
    fclose(fh); 
    exit(0);
}
