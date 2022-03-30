#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//variables
typedef struct _rwlock_t {
    sem_t rlock; // binary semaphore for updating reader value (basic lock)
    sem_t writelock; // allow ONE writer/MANY readers
    sem_t wait; //Universal lock for both readers and writers
    int readers; // #readers in critical section
} rwlock_t;

void rwlock_init(rwlock_t *rw); //Initalizes lock
void rwlock_acquire_readlock(rwlock_t *rw); //Readers aquire there lock
void rwlock_release_readlock(rwlock_t *rw); //Readers release there lock
void rwlock_acquire_writelock(rwlock_t *rw); //Writers aquire there lock
void rwlock_release_writelock(rwlock_t *rw); //Writers release there lock

void* readThread(rwlock_t *lock); //Reader threads start here
void* writeThread(rwlock_t *lock); //Writer threads start here
void reading_writing(); //Accessing data section