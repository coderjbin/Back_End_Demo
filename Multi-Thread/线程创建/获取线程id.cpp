#include <stdio.h>
#include <pthread.h>
void *function(void* arg) {
    printf("thread id in pthread=%lu\n", pthread_self());
    pthread_exit((void*)1);
}

int main() {
    int i = 10;
    pthread_t thread;
    int iRet = pthread_create(&thread, NULL, function, &i);
    if(iRet) {
        printf("pthread_create error: iRet=%d\n", iRet);
        return iRet;
    }
    void *retVal;
    iRet = pthread_join(thread, &retVal);
    if(iRet) {
        printf("pthread_join error: iRet=%d\n", iRet);
        return iRet;
    }
    printf("retVal = %ld\n", (long)retVal);
    return 0;
}