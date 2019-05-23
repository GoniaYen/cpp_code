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
#define BUF_SIZE 1024
void read_childproc(int sig)
{
    int statues;
    pid_t id = waitpid(-1, &statues, WNOHANG);
    cout << "Remove proc id:" << id << endl;
}
int main(int argc, char *argv[])
{
    int serv_sock, clnt_sock;
    int str_len = 0, state;
    pid_t pid;
    char msg[BUF_SIZE];

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    struct sigaction act;

    socklen_t clnt_addr_size;
    if (argc != 2)
    {
        cout << "缺少参数：port" << endl;
        return -1;
    }

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);

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
    while (1)
    {
        clnt_addr_size = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1)
        {
            continue;
        }
        else
        {
            puts("new client connected...");
        }
        pid = fork();
        if (pid == -1)
        {
            close(clnt_sock);
            continue;
        }
        if (pid == 0)

        {
            cout << "child serv_sock :" << serv_sock << "child serv_sock addr:" << &serv_sock << endl;
            cout << "child clnt_sock :" << clnt_sock << "child clnt_sock addr:" << &clnt_sock << endl;
            close(serv_sock);
            while ((str_len = read(clnt_sock, msg, BUF_SIZE)) != 0)
            {
                write(clnt_sock, msg, str_len);
            }
            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        }
        else

        {
            cout << "parent serv_sock :" << serv_sock << "parent serv_sock addr:" << &serv_sock << endl;
            cout << "parent clnt_sock :" << clnt_sock << "parent clnt_sock addr:" << &clnt_sock << endl;
            close(clnt_sock);
        }
    }
    close(serv_sock);

    return 0;
}