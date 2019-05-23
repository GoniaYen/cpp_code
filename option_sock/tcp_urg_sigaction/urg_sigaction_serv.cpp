
#include <syslog.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <assert.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <libgen.h>


static int listenfd;
static int connfd;

#define BUF_SIZE 1024
void sig_urg(int sig)
{
    printf("sig_urg()");
    char buffe[BUF_SIZE];
    memset(buffe, '\0', BUF_SIZE);
    int ret = recv(connfd, buffe, BUF_SIZE - 1, MSG_OOB);
    printf("got %d bytes of oob data '%s'\n", ret, buffe);
    errno = save_errno;
}
void sig_urgs(int sig)
{
    printf("sig_urg()");
    char buffe[BUF_SIZE];
    int save_errno = errno;
    memset(buffe, '\0', BUF_SIZE);
    int ret = recv(connfd, buffe, BUF_SIZE - 1, MSG_OOB);
    printf("got %d bytes of oob data '%s'\n", ret, buffe);
    errno = save_errno;

}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
       perror("缺少参数");
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int ret = 0;
    struct sockaddr_in address;
      bzero(&address, sizeof(address));
        address.sin_family = PF_INET;
    address.sin_addr.s_addr = htonl(atoi(argv[1]))
    address.sin_port = htons(atoi(argv[2]));
  
 

    listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);
    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    if (ret == -1)
    {
        printf("errno id %s", strerror(errno));
        return 1;
    }
    ret = listen(listenfd, 5);
    assert(ret != -1);
    struct sockaddr_in client;
    socklen_t client_addrlenth = sizeof(client);
    connfd = accept(listenfd, (struct sockaddr *)&client, &client_addrlenth);
    if (connfd < 0)
    {
        printf("errno is: %d\n", errno);
    }
    else
    {
        struct sigaction sa;
        memset(&sa, '\0', sizeof(sa));
        sa.sa_handler = sig_urgs;

        sa.sa_flags = 0;
        sigemptyset(&sa.sa_mask); //屏蔽所有信号
        fcntl(connfd, F_SETOWN, getpid());
        int state = sigaction(SIGURG, &sig_urgs,NULL);
        char buffer[BUF_SIZE];
        while (1)
        {
            memset(buffer, '\0', BUF_SIZE);
            ret = recv(connfd, buffer, BUF_SIZE - 1, 0);
            if ((ret <= 0))
            {
                break;
            }

            printf("got %d bytes of normal data '%s'\n", ret, buffer);
        }

        close(connfd);
    }
    close(listenfd);
    return 1;
}
