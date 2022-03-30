#include "readerwriter.h"

int main()
{
    rwlock_t lock;
    char rw;
    FILE *file;
    int error; //Flag to determine if threads fail to get created

    //open inputfile
    file = fopen("scenarios.txt", "r");

    //initialize lock
    rwlock_init(&lock);

    //for threads
    pthread_t thread;

    if (file)
    {
        //scan input file
        printf("Scenario Starts:\n");
        while (fscanf(file, "%c", &rw) != EOF)
        {

            if (rw == 'r')
            {

                //if read create a thread to run the readThread
                error = pthread_create(&thread, NULL, (void *)readThread, (void *)&lock);
                if (error != 0)
                {
                    printf("Can't create thread.\n");
                    return 1;
                }
            }

            else if (rw == 'w')
            {

                //if write create a thread to run the writeThread
                error = pthread_create(&thread, NULL, (void *)writeThread, (void *)&lock);
                if (error != 0)
                {
                    printf("Can't create thread.\n");
                    return 1;
                }
            }
        }
    }

    //close file
    fclose(file);
    
    //exit threads
    pthread_exit(NULL);
    
    printf("Program Completed");
    return 0;
}