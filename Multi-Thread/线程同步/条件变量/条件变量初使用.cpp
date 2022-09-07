#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

int x = 10;
int y = 20;
void *func1(void* arg) {
    cout << "func1 start" << endl;
    pthread_mutex_lock(&qlock);
    while(x < y) {
        cout << "x < y" << endl;
        /* 线程睡眠 并等待条件变量满足 */
        pthread_cond_wait(&qready, &qlock);
    }
    pthread_mutex_unlock(&qlock);
    sleep(3);
    cout << "func1 end" << endl;
}

void *func2(void* arg) {
    cout << "func2 start" << endl;
    pthread_mutex_lock(&qlock);
    x = 20;
    y = 10;
    cout << "has change x and y" << endl;
    pthread_mutex_unlock(&qlock);
    if(x > y) {
        /* 条件满足 向睡眠线程发送信号 */
        pthread_cond_signal(&qready);
    }
    cout << "func2 end" << endl;
}

int main() {
    pthread_t tid1, tid2;
    int iRet;
    iRet = pthread_create(&tid1, NULL, func1, NULL);
    if(iRet) {
        cout << "pthread 1 create error" << endl;
        return iRet;
    }
    sleep(2);
    iRet = pthread_create(&tid2, NULL, func2, NULL);
    if(iRet) {
        cout << "pthread 2 create error" << endl;
        return iRet;
    }
    sleep(5);
    return 0;
}
