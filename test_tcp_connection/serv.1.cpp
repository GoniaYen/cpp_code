#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int ser_sock;
    int cli_sock;
    struct timeval timeout;
    struct sockaddr_in ser_addr;
    struct sockaddr_in cli_addr;

    socklen_t cli_add_size;
    fd_set reads, cpy_reads;
    int fd_max, fd_num;

    char msg[] = "hello";

    ser_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (ser_sock == -1)
    {
        perror("socket error");
        return -1;
    }

    bzero(&ser_addr, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(9999);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(ser_sock, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) == -1)
    {
        perror("bind() error");
        return -1;
    }

    if (listen(ser_sock, 5) == -1)
    {
        perror("listen() error");
        return -1;
    }
    FD_ZERO(&reads);
    FD_SET(ser_sock, &reads);
    fd_max = ser_sock;
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
                if (i == ser_sock) //链接请求
                {
                    cout << "start connect" << endl;
                    cli_add_size = sizeof(cli_addr);
                    cli_sock = accept(ser_sock, (struct sockaddr *)&cli_addr, &cli_add_size);
                    FD_SET(cli_sock, &reads);
                    if (fd_max < cli_sock)
                    {
                        fd_max = cli_sock;
                    }

                    cout << "connect client:" << cli_sock << endl;
                }
               
            }
            close(i);
        }
    }
  

    close(ser_sock);
    return 0;
}