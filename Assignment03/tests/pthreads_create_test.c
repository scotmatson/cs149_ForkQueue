/* Attributions:
 *   http://computing.llnl.gov/tutorials/pthreads/
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static const int NUM_THREADS = 5;

/*
 * Prints hello world
 */
void * printHello(void * threadid) {
    long tid;
    tid = (long) threadid;
    printf("Hello, World! It's me, thread #%ld!\n", tid);
    printf("Thread #%ld exiting\n", tid);
    pthread_exit(NULL);
}

/*
 * Main
 */
int main(int argc, char * argv[]) {
    // Main is comprised of a single default thread

    pthread_t threads[NUM_THREADS]; // an array of threads

    int rc; // return code
    long t; // thread counter
    for (t=0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %ld\n", t);
        /*
         * pthread_create(thread, attr, start_routine, arg)
         *     thread: thread identifier
         *     attr: sets thread attributes
         *     start_routine: routine to execute upon thread init
         *     arg: single argument to pass to routine
         */
        rc = pthread_create(&threads[t], NULL, printHello, (void *) t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
        else {
            // Successful thread creation returns 0
            //printf("SUCCESS: return code from pthread_create() is %d\n", rc);
        }
    }

    /* Last thing that main() should do */
    printf("Main thread exiting\n");
    pthread_exit(NULL);
}
