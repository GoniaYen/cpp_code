#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4

using namespace std;
int calculate(int opnum, int opnds[], char op);
int main(int argc, char **argv)
{
    int result;
    char op_info[BUF_SIZE];
    int opnd_cnt, recv_len, recv_cnt,i;
    int clnt_sock, serv_sock;
    struct sockaddr_in clnt_addr;
    struct sockaddr_in serv_addr;
    socklen_t clnt_addr_len;

    if (argc != 2)
    {
        cout << "缺少参数:port" << endl;
        return -1;
    }
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        perror("socket() error ");
        return -1;
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("bind() error ");
        return -1;
    }
    if (listen(serv_sock, 5) == -1)
    {
        perror("listrn() error");
        return -1;
    }
    clnt_addr_len = sizeof(clnt_addr);
    for (i = 0; i < 5; i++)
    {
        opnd_cnt = 0;
        if (clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_len) == -1)
        {
            perror("accept() error");
            return -1;
        }
        read(clnt_sock, &opnd_cnt, 1);
        cout << "opnd_cnt : " << opnd_cnt << endl;
        recv_len = 0;
        while (opnd_cnt * OPSZ + 1 > recv_len)
        {
            recv_cnt = read(clnt_sock, &op_info, BUF_SIZE - 1);
            recv_len += recv_cnt;
        }

        result = calculate(opnd_cnt, (int *)op_info, op_info[recv_len - 1]);
        write(clnt_sock, (char *)&result, sizeof(result));
        close(clnt_sock);
    }
    close(serv_sock);

    return 0;
}
int calculate(int opnum, int opnds[], char op)
{
    int result = opnds[0];
    switch (op)
    {
    case '+':
        for (int i = 1; i < opnum; i++)
        {
            result += opnds[i];
        }
        break;
    case '-':
        for (int i = 1; i < opnum; i++)
        {
            result -= opnds[i];
        }
        break;
    case '*':
        for (int i = 1; i < opnum; i++)
        {
            result *= opnds[i];
        }
        break;

    default:
        break;
    }
    return result;
}