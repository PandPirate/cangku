#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include "cgic.h"
#include "global.h"


int main(int argc, const char *argv[])
{
    struct storage_env_info *updatedata = NULL;
   
    struct sembuf sops;
    int res, shmid, semid, i = 100;
    key_t key = ftok("/home", 1);
    if (key < 0)
    {
        perror("ftok");
        return -1;
    }
    printf("key = %x\n", key);
    // 信号灯集初始化
    semid = semget(key, 2, IPC_CREAT|0664);
      printf("semid = %d\n", semid);
    if (semid < 0)
    {
        perror("semget");
        return -1;
    }
    printf("semid = %d\n", semid);
    semctl(semid, 0, SETVAL, 0);
    semctl(semid, 1, SETVAL, 1);

    shmid = shmget(key, sizeof(struct storage_env_info), IPC_CREAT | 0664);
    if (shmid < 0)
    {
        perror("shmget");
        return -1;
    }
    printf("shmid = %d\n", shmid);
    updatedata = shmat(shmid, NULL, 0);
    if (updatedata == (void *)-1)
    {
        perror("shmat");
        return -1;
    }
    updatedata->temperature = 25.2;
    updatedata->humidity = 70;
    updatedata->illumination = 120;
    updatedata->x = 1;
    updatedata->y = 10;
    updatedata->z = 100;
    printf("%s\n", "start");
    while (i)
    {
        i--;
        sops.sem_num = 1;
        sops.sem_flg = 0;
        sops.sem_op = -1;
        semop(semid, &sops, 1);
        updatedata->temperature++;
        updatedata->humidity++;
        updatedata->illumination++;
        updatedata->x++;
        updatedata->y++;
        updatedata->z++;
        sops.sem_num = 0;
        sops.sem_flg = 0;
        sops.sem_op = +1;
        semop(semid, &sops, 1);
        sleep(2);
    }

    return 0;
}