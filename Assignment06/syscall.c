#define _POSIX_C_SOURCE 200809L
#define PROCS 5             /* Number of processes (including parent)*/
#define PIPES 2             /* Pipes per process(read/write) */
#include <stdio.h>          /* for printf() */
#include <unistd.h>         /* for pipe(), fork(), and close() */
#include <stdlib.h>         /* for exit(), srand(), rand() */
#include <time.h>           /* For seeing srand() */
#include <mach/mach_time.h> /* For OSX Time Keeping */ 
#include <sys/select.h>     /* For select() */
#include <string.h>         /* For strcpy() */
#include <fcntl.h>          /* To disable blocking */

int main(int argc, char **argv) {
    printf("*** Executing syscall.c ***\n\n");
    fflush(stdout);
 
    int            i, retval;      /* Reusable counters/return values */
    int            m1,m2,m3,m4,m5; /* Message counters */
    char           readBuffer[20]; /* Buffer for parent to read from pipe */
    FILE           *fh;            /* File Handler to write piped message */

    /* Process IDs */
    pid_t          pid;            /* Control  filter for fork() */
    pid_t          p_pid;          /* Parent proc */ 
    pid_t          c_pid[PROCS];   /* Child procs */

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

    /* Prepare parent File Descriptor for piping */
    int p_fd[2];
    close(p_fd[1]);
    fcntl(*p_fd, F_SETFL, O_NONBLOCK);
    pipe(p_fd);

    /* Fork processes and setup child file descriptors */
    struct fd_set socket;
    int fds[PROCS][PIPES];
    FD_ZERO(&socket);
    for (i = 0; i < PROCS; i++) {
        if ((pid = fork()) < 0) {
            fflush(stdout);
            perror("ERROR; Unable to fork this process");
            fflush(stdout);
            exit(1);
        } 
        else if (pid == 0) {
            c_pid[i] = getpid();                 /* Store child process ID */
            FD_SET(*fds[i], &socket);            /* Set FIFO File Descriptor control */
            close(fds[i][0]);                    /* Close read side */
            //fcntl(*fds[i], F_SETFL, O_NONBLOCK); /* Prevent blocking behavior */
            pipe(fds[i]);                        /* Add File Descriptor to the pipe */
            break;
        } 
        else {
            p_pid = getpid();
        }
    }

    /* IO for parent process */
    fh = fopen("out/output.txt", "w");
    if (fh == NULL) {
        fprintf(stderr, "ERROR; Unable to open file\n");
        exit(1);
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

            //char msg5[20];
            //scanf("%[^\n]%*c", msg5);
            // Send through pipe
            //write(fd5[0], msg5, sizeof(msg5));
        }
        else {
            // Parent
            retval = select(6, &socket, NULL, NULL, &timeout); /* Think this goes here */
            switch(retval) {
                case -1:
                    fprintf(stderr, "ERROR; Unable to select file descriptor\n");
                    exit(1);
                    break;
                case 1:
                    stop = mach_absolute_time();
                    elapsed = (float)(stop-start) * tb.numer/tb.denom;
                    elapsed /= 1000000000;
                    /* read proc data */
                    printf("Parent: Reading from the pipe!\n");
                    read(p_fd[0], readBuffer, sizeof(readBuffer));
                    printf("Parent: %s\n", readBuffer);
                    printf("Parent: The pipe has been read!\n");
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
