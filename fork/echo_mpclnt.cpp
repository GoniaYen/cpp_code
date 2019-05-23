#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;

using namespace std;
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);

#define BUF_SIZE 1024
int main(int argc, char **argv)
{
    int sock;
    pid_t pid;
    char msg[BUF_SIZE];
    struct sockaddr_in serv_addr;
    if (argc != 2)
    {
        cout << "缺少参数：port" << endl;
        return -1;
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);

    if (sock == -1)
    {
        perror("socket() error");
        return -1;
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("connect() error");
        return -1;
    }
    else
    {
        fputs("Connected...", stdout);
    }
    pid = fork();
    if (pid == 0)
    {
        write_routine(sock, msg);
    }
    else
    {
        read_routine(sock, msg);
    }
    close(sock);

    return 0;
}
void read_routine(int sock, char *buf)
{
    while (1)
    {
        int str_len = read(sock, buf, BUF_SIZE);
        if (str_len == 0)
        {
            return;
        }
        buf[str_len] = 0;
        cout << "Message from server : " << buf << endl;
    }
}
void write_routine(int sock, char *buf)
{
    while (1)
    {
        //fputs("Input message(Q or q to quit):", stdout);
        fgets(buf, BUF_SIZE, stdin);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
        {
            shutdown(sock,SHUT_WR);
            return;
        }
        write(sock,buf,strlen(buf));
    }
}