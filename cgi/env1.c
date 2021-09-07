#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include "cgic.h"
#include "global.h"

int cgiMain(int argc, const char *argv[])
{
    struct storage_env_info *updatedata = NULL;

    int res, shmid, semid;
    struct sembuf sops;
    key_t key = ftok("/home", 1);
    if (key < 0)
    {
        perror("ftok");
        return -1;
    }

    // 信号灯集初始化
    semid = semget(key, 2, IPC_CREAT | 0664);
    if (semid < 0)
    {
        perror("semget");
        return -1;
    }
    semctl(semid, 0, SETVAL, 0);
    semctl(semid, 1, SETVAL, 1);

    // 共享内存初始化
    shmid = shmget(key, sizeof(struct storage_env_info), IPC_CREAT | 0664);
    if (shmid < 0)
    {
        perror("shmget");
        return -1;
    }
    updatedata = shmat(shmid, NULL, SHM_RDONLY);
    if (updatedata == (void *)-1)
    {
        perror("shmat");
        return -1;
    }

    // p操作
    sops.sem_num = 0;
    sops.sem_flg = 0;
    sops.sem_op = -1;
    semop(semid, &sops, 1);
    cgiHeaderContentType("text/html");
    fprintf(cgiOut, "<p><span class='sp1'>当前温度 </span><span class='sp2'>： %.2f</span></p>", updatedata->temperature);
    fprintf(cgiOut, "<p><span class='sp1'>当前湿度 </span><span class='sp2'>：%.2f</span></p>", updatedata->humidity);
    fprintf(cgiOut, "<p><span class='sp1'>当前光照 </span><span class='sp2'>：%.2f</span></p>", updatedata->illumination);
    fprintf(cgiOut, "<p><span class='sp1'>电池电压 </span><span class='sp2'>：%.2f</span></p>", updatedata->battery);
    fprintf(cgiOut, "<p><span class='sp1'>采集电压</span><span class='sp2'>：%.2f</span></p>", updatedata->adc);
    fprintf(cgiOut, "<p><span class='sp1'>当前X轴 </span><span class='sp2'>：%2d</span></p>", updatedata->x);
    fprintf(cgiOut, "<p><span class='sp1'>当前Y轴 </span><span class='sp2'>：%2d</span></p>", updatedata->y);
    fprintf(cgiOut, "<p><span class='sp1'>当前Z轴 </span><span class='sp2'>： %2d</span></p>", updatedata->z);

    // v操作
    sops.sem_num = 1;
    sops.sem_flg = 0;
    sops.sem_op = +1;
    semop(semid, &sops, 1);

    return 0;
}
