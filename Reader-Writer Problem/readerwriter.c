#include "readerwriter.h"

//Initializes the reader-writer lock struct
void rwlock_init(rwlock_t *rw) {
    rw->readers = 0;
    sem_init(&rw->wait, 0, 1); //Access Lock
    sem_init(&rw->rlock, 0, 1);
    sem_init(&rw->writelock, 0, 1);
}

//Reader threads go here to get writelock
void rwlock_acquire_readlock(rwlock_t *rw) {
    sem_wait(&rw->rlock);
    rw->readers++;  //Incrementing number of readers in critical section
    if (rw->readers == 1) // first reader gets writelock
        sem_wait(&rw->writelock);
    sem_post(&rw->rlock);
}

//Reader threads go here to let go of writelock
void rwlock_release_readlock(rwlock_t *rw) {
    sem_wait(&rw->rlock);
    rw->readers--; //Decrementing number of readers in critical section
    if (rw->readers == 0) // last reader lets it go
        sem_post(&rw->writelock);
    sem_post(&rw->rlock);
}

//Writer threads go here to aquire writelock
void rwlock_acquire_writelock(rwlock_t *rw) {
    sem_wait(&rw->writelock);  
}

//Writer threads go here to release writelock
void rwlock_release_writelock(rwlock_t *rw) {
    sem_post(&rw->writelock);
}


void* readThread(rwlock_t *lock){
    sem_wait(&lock->wait); //Universal lock for both readers and writers
    rwlock_acquire_readlock(lock);
    sem_post(&lock->wait);
    printf("Reader Is Reading\n");
    reading_writing(); //Accessing critical section
    printf("Reader Done %d\n", lock->readers);
    rwlock_release_readlock(lock);
}

void* writeThread(rwlock_t *lock){
    sem_wait(&lock->wait); //Universal lock for both readers and writers
    rwlock_acquire_writelock(lock);
    printf("Writer Is Writing\n");
    reading_writing(); //Accessing critical section
    printf("Writer Done\n");
    rwlock_release_writelock(lock);
    sem_post(&lock->wait);
}

//Function is used to act as threads accessing data.
void reading_writing(){ 
    int x = 0, T; 
    T = rand() % 30000; 
    for(int i = 0; i < T; i++) 
        for(int j = 0; j < T; j++) 
            x=i*j; 
}