#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    FILE *fp;
    char buf[BUF_SIZE];
    int read_clnt;
    int serv_sock, clnt_sock;
    socklen_t clnt_sock_size;
    struct sockaddr_in serv_addr, clnt_addr;
    if (argc != 2)
    {
        cout << "缺少参数　port:" << endl;
        return -1;
    }
    fp = fopen("file_server.cpp", "rb");
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        perror("socket() error : ");
        return -1;
    }
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("bind() error :");
        return -1;
    }

    if (listen(serv_sock, 5) == -1)
    {
        perror("bind() error :");
        return -1;
    }
    clnt_sock_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_sock_size);

    if (clnt_sock == -1)
    {
        perror("accept() error :");
        return -1;
    }

    while (1)
    {
        read_clnt = fread((void *)buf, 1, BUF_SIZE, fp);
        if (read_clnt < BUF_SIZE)
        {
            write(clnt_sock, buf, read_clnt);
            break;
        }
        write(clnt_sock, buf, BUF_SIZE);
    }

    shutdown(clnt_sock, SHUT_WR);
    
    
    
    bzero(buf, BUF_SIZE);
    read(clnt_sock, buf, BUF_SIZE);

    cout << "message from client : " << buf << endl;
    fclose(fp);
    close(clnt_sock);
    close(serv_sock);

    return 0;
}