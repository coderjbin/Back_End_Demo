#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#define SEM_KEY 4001
#define SHM_KEY 1234

union semun {
    int val;
};

int main() {
    /* create a shm */
    int semid, shmid;
    shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
    if(shmid < 0) {
        printf("create shm error\n");
        return -1;
    }
    void *shmptr;
    shmptr = shmat(shmid, NULL, 0);
    if(shmptr == (void*)-1) {
        printf("shmat error: %s\n", strerror(errno));
        return -1;
    }
    int *data = (int*)shmptr;
    /* 创建一个semid，并且拥有两个信号量 */
    semid = semget(SEM_KEY, 2, IPC_CREAT | 0666);
    union semun semun1; /* 下面四行初始化两个信号量，一个val=0，另一个val=1 */
    semun1.val = 0;
    semctl(semid, 0, SETVAL, semun1);
    semun1.val = 1;
    semctl(semid, 1, SETVAL, semun1);
    struct sembuf sembuf1;
    while(1) {
        sembuf1.sem_num = 0; /* sem_num = 0指的是下面操作只想第一个信号量, 上面设置可知其val=0 */
        sembuf1.sem_op = -1; /* 初始化值为0，再-1就会等待 */
        sembuf1.sem_flg = SEM_UNDO;
        semop(semid, &sembuf1, 1); /* reader会在这里阻塞，直到收到信号 */
        printf("the NUM: %d\n", *data); /* 输出结果 */
        sembuf1.sem_num = 1; /* 让writer再次就绪，这样循环 */
        sembuf1.sem_op = 1;
        sembuf1.sem_flg = SEM_UNDO;
        semop(semid, &sembuf1, 1);
    }
    return 0;
}