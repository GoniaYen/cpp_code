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
int main(int argc, char *argv[])
{
    int sock;
    char op_msg[BUF_SIZE];
    int result, opnd_cnt, i;
    struct sockaddr_in serv_addr;
    if (argc != 2)
    {
        cout << "缺少参数:ｐｏｒｔ" << endl;
        exit(1);
    }
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("socket() error");
        exit(1);
    }
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = PF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("connect() error");
        exit(1);
    }
    }
    cout << "操作数的个数：";
    cin >> opnd_cnt;

    op_msg[0] = (char)opnd_cnt;
    for (int i = 0; i < opnd_cnt; i++)
    {
        cout << "第" << i+1 << "个数：";
        cin >> op_msg[i * OPSZ + 1];
    }
    cout << "输入操作符（+,-,*)：";
    cin >> op_msg[opnd_cnt * OPSZ + 1];

    for (int i = 0; i < opnd_cnt + 1; i++)
    {
        cout << op_msg[i * OPSZ + 1] << endl;
    }
    cout << "长度" << strlen(op_msg) << endl;

    if(write(sock, op_msg, opnd_cnt * OPSZ + 2)==-1){
        perror("write() error");
    }
    
    read(sock, &result, RLT_SIZE);
    cout << "结果：" << ntohl(result) << endl;

    close(sock);
    return 0;
}