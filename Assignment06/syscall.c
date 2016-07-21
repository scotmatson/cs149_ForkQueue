#define _POSIX_C_SOURCE 200809L
#define PROCS  5             /* Number of processes (including parent)*/
#define IO     2             /* Pipes per process(read/write) */
#define MILLI  1000000000    /* Division needed to convert time to milliseconds */
#define READ   0             /* Read side for File Descriptors */
#define WRITE  1             /* Write side for File Descriptors */
#define BUFFER 60            /* Universal character output buffer */
#include <stdio.h>           /* for printf() */
#include <unistd.h>          /* for pipe(), fork(), and close() */
#include <stdlib.h>          /* for exit(), srand(), rand() */
#include <time.h>            /* For seeding srand() */
#include <mach/mach_time.h>  /* For OSX Time Keeping */ 
#include <sys/select.h>      /* For select() */
#include <string.h>          /* For strcpy() */

int main() {
    printf("*** Executing syscall.c ***\n\n");
    fflush(stdout);
 
    int            i, retval;          /* Reusable counters/return values */
    int            messageNum;         /* Message counter */
    char           readBuffer[BUFFER]; /* Buffer for parent to read from pipe */
    FILE           *fh;                /* File Handler to write piped message */
    
    /* Process IDs */
    pid_t          pid;                /* Control  filter for fork() */
    pid_t          p_pid;              /* Parent proc */ 
    pid_t          c_pid[PROCS];       /* Child procs */

    /* Time Management */
    static mach_timebase_info_data_t tb;
    uint64_t       start, stop;
    float          elapsed; 
    struct timeval timeout;

    /* Start/Set the clocks */
    mach_timebase_info(&tb);
    start = mach_absolute_time();
    timeout.tv_sec  = 0;
    timeout.tv_usec = 0;

    /* Setup file descriptors */
    struct fd_set socket;
    int fds[PROCS][IO];
    FD_ZERO(&socket);
    for (i = 0; i < PROCS; i++) {
        FD_SET(*fds[i], &socket);
        pipe(fds[i]);
    }

    /* Last minute initialization prior to forking */
    messageNum = 0;

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
            close(fds[i][WRITE]);
        }
    }

    /* IO for parent process */
    fh = fopen("out/output.txt", "w");
    if (fh == NULL) {
        fprintf(stderr, "ERROR; Unable to open file\n");
        exit(1);
    }

    /* Last chance to initialize any variables */
    int j = 0;
    /* Loop runs for 30 seconds (real time) */
    while (j < 10) {
        j++;
        srand(time(NULL));
        /* Read that this has to happen inside the main loop, it seems to help, but needs work */

        if (getpid() == c_pid[0]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= MILLI;
            messageNum++;
            char buf0[BUFFER];
            snprintf(buf0, sizeof(buf0), "0:%06.3f: Child 1 message %d\n", elapsed, messageNum);
            write(fds[0][WRITE], &buf0, sizeof(buf0));
        }    
        else 
        if (getpid() == c_pid[1]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= MILLI;
            messageNum++;
            char buf1[BUFFER];
            snprintf(buf1, sizeof(buf1), "0:%06.3f: Child 2 message %d\n", elapsed, messageNum);
            write(fds[1][WRITE], &buf1, sizeof(buf1));
        }
        else
        if (getpid() == c_pid[2]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= MILLI;
            messageNum++;
            char buf2[BUFFER];
            snprintf(buf2, sizeof(buf2), "0:%06.3f: Child 3 message %d\n", elapsed, messageNum);
            write(fds[2][WRITE], &buf2, sizeof(buf2));
        }
        else
        if (getpid() == c_pid[3]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= MILLI;
            messageNum++;
            char buf3[BUFFER];
            snprintf(buf3, sizeof(buf3), "0:%06.3f: Child 4 message %d\n", elapsed, messageNum);
            write(fds[3][WRITE], &buf3, sizeof(buf3));
        }
        else
        if (getpid() == c_pid[4]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            elapsed /= MILLI;
            messageNum++;
            printf("%d$ ", getpid());
            char buf4[BUFFER];
            scanf("%[^\n]%*c", buf4);
            snprintf(buf4, sizeof(buf4), "0:%06.3f: Child 5 message %d\n", elapsed, messageNum);
            write(fds[4][WRITE], &buf4, sizeof(buf4));
        }
        else {
            /* Parent process */
            FD_ZERO(&socket);
            for (i = 0; i < PROCS; i++) {
                FD_SET(*fds[i], &socket);
            }
            retval = select(PROCS+1, &socket, NULL, NULL, &timeout);
            if (retval > 0) {
                for (i = 0; i < PROCS; i++) {
                    if (FD_ISSET(fds[i][READ], &socket)) {
                        /* TODO: Prefix child output with parent time */
                        stop = mach_absolute_time();
                        elapsed = (float)(stop-start) * tb.numer/tb.denom;
                        elapsed /= MILLI;
                        read(fds[i][READ], readBuffer, sizeof(readBuffer));
                        fprintf(fh, "%s", readBuffer); 
                    }
                }
            }
            else     
            if (retval < 0) { 
                fprintf(stderr, "ERROR; Unable to select file descriptor\n");
                exit(1);
            }
            else {
               printf("No data to be read from the pipe\n");
               fflush(stdout);
            }
        }
        sleep(rand() % 3);
    }

    /* Close all IO */
    /*
    for (i = 0; i < PROCS; i++) {
        close(fds[i][READ]);
        close(fds[i][WRITE]);
    }
    */
    fclose(fh); 
    exit(0);
}
