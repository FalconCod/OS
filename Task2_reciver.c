#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
int main()
{
    char *shared_memory;
    char buff[100];
    int shmid;
    shmid = shmget((key_t)2345, 1024, 0666);
    printf("Key of shared memory is %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0);
    printf("Process attached at %p\n", shared_memory);
    printf("Data read from shared memory is :\n");
    while (1)
    {
        while (shared_memory[0] == '\0')
        {
            sleep(1);
        }
        printf("Received: %s", shared_memory);
        if (strncmp(shared_memory, "exit", 4) == 0)
            break;
        shared_memory[0] = '\0';

        printf("Enter message: ");
        fgets(shared_memory, 100, stdin);
        if (strcmp(shared_memory, "exit\n") == 0)
            break;
        while (shared_memory[0] != '\0')
        {
            sleep(1);
        }
    }
}