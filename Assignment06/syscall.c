#define _POSIX_C_SOURCE 200809L
#define PROCS  5             /* Number of processes (including parent)*/
#define IO     2             /* Pipes per process(read/write) */
#define MILLI  1000000000    /* Division needed to convert time to milliseconds */
#define READ   0             /* Read side for File Descriptors */
#define WRITE  1             /* Write side for File Descriptors */
#define BUFFER 255           /* Universal character output buffer */
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
    int            mNum;               /* Message counter */
    char           rBuf[BUFFER];       /* Buffer for parent to read from pipe */
    char           wBuf[BUFFER];       /* Buffer for children to write to pipe */
    FILE           *fh;                /* File Handler to write piped message */
    
    /* Process IDs */
    pid_t          pid;                /* Control  filter for fork() */
    pid_t          p_pid;              /* Parent proc */ 
    pid_t          c_pid[PROCS];       /* Child procs */

    /* Time Management */
    static mach_timebase_info_data_t tb;
    struct timeval timeout;
    uint64_t       start, stop;
    float          elapsed; 
    float          runtime;
    float          maxtime;

    /* Start/Set the clocks */
    mach_timebase_info(&tb);
    start = mach_absolute_time();
    timeout.tv_sec  = 0;
    timeout.tv_usec = 0;
    maxtime         = 30.0f;

    /* Setup file descriptors */
    struct fd_set socket;
    int fds[PROCS][IO];
    FD_ZERO(&socket);
    for (i = 0; i < PROCS; i++) {
        FD_SET(*fds[i], &socket);
        pipe(fds[i]);
    }

    /* Last minute initialization prior to forking */
    setbuf(stdin, NULL);
    mNum = 0;

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

    /* Message passing loop */
    runtime = 0.0f;
    while (runtime < maxtime) {
        srand(time(NULL));
        if (getpid() == c_pid[0]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            runtime=elapsed /= MILLI;
            mNum++;
            snprintf(wBuf, sizeof(wBuf), "0:%06.3f: Child 1 message %d\n", elapsed, mNum);
            write(fds[0][WRITE], &wBuf, sizeof(wBuf));
        }    
        else 
        if (getpid() == c_pid[1]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            runtime=elapsed /= MILLI;
            mNum++;
            snprintf(wBuf, sizeof(wBuf), "0:%06.3f: Child 2 message %d\n", elapsed, mNum);
            write(fds[1][WRITE], &wBuf, sizeof(wBuf));
        }
        else
        if (getpid() == c_pid[2]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            runtime=elapsed /= MILLI;
            mNum++;
            snprintf(wBuf, sizeof(wBuf), "0:%06.3f: Child 3 message %d\n", elapsed, mNum);
            write(fds[2][WRITE], &wBuf, sizeof(wBuf));
        }
        else
        if (getpid() == c_pid[3]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            runtime=elapsed /= MILLI;
            mNum++;
            snprintf(wBuf, sizeof(wBuf), "0:%06.3f: Child 4 message %d\n", elapsed, mNum);
            write(fds[3][WRITE], &wBuf, sizeof(wBuf));
        }
        else
        if (getpid() == c_pid[4]) {
            stop = mach_absolute_time();
            elapsed = (float)(stop-start) * tb.numer/tb.denom;
            runtime=elapsed /= MILLI;
            mNum++;
            char str[30];
            printf("%d$ ", getpid());
            scanf("%[^\n]%*c", str);
            snprintf(wBuf, sizeof(wBuf), "0:%06.3f: Child 5 message %d : %s\n", 
                elapsed, mNum, str);
            write(fds[4][WRITE], &wBuf, sizeof(wBuf));
        }
        else {
            /* Parent process */
            FD_ZERO(&socket);
            for (i = 0; i < PROCS; i++) {
                FD_SET(*fds[i], &socket);
            }
            retval = select(FD_SETSIZE, &socket, NULL, NULL, &timeout);
            if (retval > 0) {
                for (i = 0; i < PROCS; i++) {
                    if (FD_ISSET(fds[i][READ], &socket)) {
                        stop = mach_absolute_time();
                        elapsed = (float)(stop-start) * tb.numer/tb.denom;
                        runtime=elapsed /= MILLI;
                        read(fds[i][READ], rBuf, sizeof(rBuf));
                        fprintf(fh, "%f - %s", elapsed, rBuf); 
                    }
                }
            }
            else     
            if (retval < 0) { 
                fprintf(stderr, "ERROR; Unable to select file descriptor\n");
                exit(1);
            }
        }
        sleep(rand() % 3);
    }

    /* Close up File Descriptors and Handlers */
    for (i = 0; i < PROCS; i++) {
        close(fds[i][READ]);
        close(fds[i][WRITE]);
    }
    fclose(fh); 
    exit(0);
}
