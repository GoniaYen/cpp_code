#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;
#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    char msg[BUF_SIZE];

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    struct timeval timeout;
    socklen_t clnt_addr_size;

    fd_set reads, cpy_reads;
    int fd_max, fd_num, str_len;
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

    FD_ZERO(&reads);
    FD_SET(serv_sock, &reads);
    fd_max = serv_sock;
    cout << "start loop" << endl;

    while (1)
    {
        cpy_reads = reads;
        timeout.tv_sec = 2;
        timeout.tv_usec = 0;
        cout << "start select" << endl;
        fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout);
    
        if ((fd_num = select(fd_max + 1, &cpy_reads, 0, 0, &timeout)) == -1)
        {
            cout << " select ..." << endl;
            break;
        }
        if (fd_num == 0)
        {
            continue;
        }

        for (int i = 0; i < fd_max + 1; i++)
        {
            if (FD_ISSET(i, &cpy_reads))
            {
                if (i == serv_sock) //链接请求
                {
                    cout << "start connect" << endl;
                    clnt_addr_size = sizeof(clnt_addr);
                    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
                    FD_SET(clnt_sock, &reads);
                    if (fd_max < clnt_sock)
                    {
                        fd_max = clnt_sock;
                    }

                    cout << "connect client:" << clnt_sock << endl;
                }
                else //读数据
                {
                    cout << "start read" << endl;
                    str_len = read(i, msg, BUF_SIZE);
                    if (str_len == 0) //关闭连接
                    {
                        FD_CLR(i, &reads);
                        close(i);
                        cout << "close client: " << i << endl;
                    }
                    else
                    {
                        cout << "start write" << endl;
                        write(i, msg, str_len); //返回
                    }
                }
            }
        }
    }
    cout << "start close" << endl;
    close(serv_sock);

    return 0;
}