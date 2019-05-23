#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;
#define BUF_SIZE 1024
#define EPOLL_SIZE 50

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    char msg[BUF_SIZE];

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;
    int str_len;

    struct epoll_event *ep_events;//保存发生时间的文件描述符集合的结构体地址
    struct epoll_event event;//监视对象的事件类型

    int epfd, event_cnt;

    if (argc != 2)
    {
        cout << "缺少参数：port" << endl;
        return -1;
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        return -1;
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("bind() error");
        return -1;
    }
    if (listen(serv_sock, 5) == -1)
    {
        perror("listen() error");
        return -1;
    }
    epfd = epoll_create(EPOLL_SIZE);//创建epoll历程文件描述符
    ep_events = (struct epoll_event *)malloc(sizeof(struct epoll_event) * EPOLL_SIZE);

    event.events = EPOLLIN;//读事件
    event.data.fd = serv_sock;//被监视对象的文件描述符
    epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);//向例程中添加描述符serv_sock,监视事件为读

    while (1)
    {
        event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);//等待事件发生，将发生事件的文件描述符集合的结构体地址保存在ep_events中
        if (event_cnt == -1)
        {
            perror("epoll_wait() error");
            break;
        }
        for (int i = 0; i < event_cnt; i++)
        {
            if (ep_events[i].data.fd == serv_sock)//连接请求
            {
                clnt_addr_size = sizeof(clnt_addr);
                clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
                event.events = EPOLLIN;
                event.data.fd = clnt_sock;
                epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
                cout << "connect client: " << clnt_sock << endl;
            }
            else
            {
                str_len = read(ep_events[i].data.fd, msg, BUF_SIZE);//读数据
                if (str_len == 0)
                {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
                    close(ep_events[i].data.fd);
                    cout << "close client:" << ep_events[i].data.fd << endl;
                }
                else
                {
                    write(ep_events[i].data.fd, msg, str_len);//f返回
                }
            }
        }
    }

    close(serv_sock);
    close(epfd);
    return 0;
}