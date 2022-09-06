#include <pthread.h>
#include <string.h>
#include <stdio.h>
struct arg_type {
    int a;
    char b[100];
};
void* say_hello(void* args) {
    arg_type arg_temp = *(arg_type*)args;
    printf("hello from thread, arg_temp.a=%d, arg_temp.b=%s\n",
        arg_temp.a, arg_temp.b);
        pthread_exit((void*)1);
}
int main() {
    pthread_t tid;
    arg_type arg_temp;
    arg_temp.a = 10;
    char temp[100] = "I am number one.";
    strncpy(arg_temp.b, temp, sizeof(temp));
    int iRet = pthread_create(&tid, NULL, say_hello, &arg_temp);
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