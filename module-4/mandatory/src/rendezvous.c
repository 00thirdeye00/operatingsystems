/**
 * Rendezvous
 *
 * Two threads executing chunks of work in lock step.
 *
 * Author: Nikos Nikoleris <nikos.nikoleris@it.uu.se>
 *
 */

#include <stdio.h>     /* printf() */
#include <stdlib.h>    /* abort(), [s]rand() */
#include <unistd.h>    /* sleep() */
#include <pthread.h>   /* pthread_...() */
//#include <semaphore.h>

#include "psem.h"

#define LOOPS 10
#define NTHREADS 3
#define MAX_SLEEP_TIME 3

// Declare global semaphore variables. Note, they must be initialized before use.
psem_t *sem;

//sem_t *sem;

/* TODO: Make the two threads perform their iterations in lockstep. */

void *
threadA(void *param __attribute__((unused)))
{
    int i;

    for (i = 0; i < LOOPS; i++) {
        //psem_wait(sem);
        printf("A%d\n", i);
        sleep(rand() % MAX_SLEEP_TIME);
        //sleep(1);

        //printf("not yet signaled...\n");
        psem_signal(sem);
        psem_wait(sem);
        //sem_post(sem);
    }

    pthread_exit(0);
}


/* TODO: Make the two threads perform their iterations in lockstep. */

void *
threadB(void *param  __attribute__((unused)))
{
    int i;

    for (i = 0; i < LOOPS; i++) {
        psem_wait(sem);

        printf("B%d\n", i);
        sleep(rand() % MAX_SLEEP_TIME);
        //sleep(1);
        
        psem_signal(sem);
        //printf("threadB(%d) waiting on a semaphore...\n", i);
        //psem_wait(sem);
        //sem_wait(sem);
    }

    pthread_exit(0);
}

int
main()
{
    pthread_t tidA, tidB;

    // Todo: Initialize semaphores.
    sem = psem_init(0);
    //sem_init(sem, 0, 0);

    //sem = psem_init(666);
    
    srand(time(NULL));
    pthread_setconcurrency(3);

    if (pthread_create(&tidA, NULL, threadA, NULL) ||
        pthread_create(&tidB, NULL, threadB, NULL)) {
        perror("pthread_create");
        abort();
    }
    if (pthread_join(tidA, NULL) != 0 ||
        pthread_join(tidB, NULL) != 0) {
        perror("pthread_join");
        abort();
    }

    // Todo: Destroy semaphores.
    psem_destroy(sem);
    //sem_destroy(sem);

    return 0;
}
