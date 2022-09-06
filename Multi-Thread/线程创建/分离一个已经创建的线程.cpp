#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
void* tfnl(void* arg) {
    printf("the sub thread sleeping for 5 seconds\n");
    sleep(5); /* 休眠5s，等待主线程退出并将线程设置为分离状态 */
    printf("the thread done\n");
    return NULL;
}

int main() {
    int iRet;
    pthread_t tid;
    iRet = pthread_create(&tid, NULL, tfnl, NULL);
    /* 创建一个线程，这个线程和结束状态是分离的 */
    if(iRet) {
        printf("can't create thread %s\n", strerror(iRet));
        return iRet;
    }
    iRet = pthread_detach(tid); /* 设置线程为分离状态 */
    if(iRet) {
        printf("can't detach thread %s\n", strerror(iRet));
        return iRet;
    }
    iRet = pthread_join(tid, NULL);
    /* 由于状态分离，因此得不到线程的结束状态信息，此函数会出错 */
    if(iRet) {
        printf("thread has been detached\n");
    }
    printf("the main thread sleeping for 8 seconds\n");
    sleep(8);
    printf("the main thread done.\n");
    return 0;
}