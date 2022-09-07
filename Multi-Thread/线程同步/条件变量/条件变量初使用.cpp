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
        pthread_cond_wait(&qready, &qlock);
    }
    pthread_mutex_unlock(&qlock);
    sleep(3);
    cout << "func1 end" << endl;
}
