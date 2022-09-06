#include <stdio.h>
#include <pthread.h>
class Hello {
public:
    static void* say_hello(void* args) {
        printf("hello from thread\n");
        pthread_exit((void*)1);
    }
};

int main() {
    pthread_t tid;
    /* 参数：创建的线程id、线程参数、调用函数名、传入的函数参数 */
    int iRet = pthread_create(&tid, NULL, Hello::say_hello, NULL);
    if(iRet) {
        printf("pthread_create error: iRet=%d\n", iRet);
        return iRet;
    }
    void *retVal;
    iRet = pthread_join(tid, &retVal);
    if(iRet) {
        printf("pthread_join error: iRet=%d\n", iRet);
        return iRet;
    }
    printf("retVal = %ld\n", (long)retVal);
    return 0;
}