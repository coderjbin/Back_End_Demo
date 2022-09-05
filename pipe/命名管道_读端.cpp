#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define P_FIFO "/tmp/p_fifo"

int main(int argc, char** argv) {
    char cache[100];
    int fd;
    memset(cache, 0, sizeof(cache)); /* 初始化内存 */
    if(access(P_FIFO, F_OK) == 0) { /* 管道文件存在 */
        execlp("rm", "-f", P_FIFO, NULL); /* 删掉 */
        printf("access.\n");
    }
    if(mkfifo(P_FIFO, 0777) < 0) {
        printf("create named pipe failed.\n");
    }
    /* 非阻塞方式打开，只读 */
    fd = open(P_FIFO, O_RDONLY | O_NONBLOCK);
    while(1) {
        memset(cache, 0, sizeof(cache));
        if((read(fd, cache, 100)) == 0) { /* 没有读到数据 */
            printf("no data~\n");
        }
        else {
            printf("get data: %s\n", cache); /* 读到数据 */
        }
        sleep(1); /* 休眠1s */
    }
    close(fd);
    return 0;
}