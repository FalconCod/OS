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
    shmid = shmget((key_t)2345, 1024, 0666 | IPC_CREAT);

    printf("Key of shared memory is %d\n", shmid);
    shared_memory = (char *)shmat(shmid, NULL, 0);
    printf("Process attached at %p\n", shared_memory);

    while (1)
    {
        printf("Wrote: ");
        fgets(buff, 100, stdin);
        strcpy(shared_memory, buff);
        if (strcmp(shared_memory, "exit\n") == 0)
            break;
        while (shared_memory[0] != '\0')
        {
            sleep(1);
        }
        while (shared_memory[0] == '\0')
        {
            sleep(1);
        }
        printf("Received: %s", shared_memory);
        if (strncmp(shared_memory, "exit", 4) == 0)
            break;
        shared_memory[0] = '\0';
    }

    return 0;
}