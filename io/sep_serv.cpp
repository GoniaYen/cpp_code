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
    FILE *readfp;
    FILE *writefp;

    char msg[BUF_SIZE]={0,};

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    struct timeval timeout;
    socklen_t clnt_addr_size;

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
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
    readfp = fdopen(clnt_sock,"r");
    writefp = fdopen(clnt_sock,"w");
    fputs("from server:hi~ client? \n",writefp);
    fputs("I love all of the world \n",writefp);
    fputs(" u r awesome! \n",writefp);
    fflush(writefp);

    fclose(writefp);
    fgets(msg,sizeof(msg),readfp);
    fputs(msg,stdout);
    fclose(readfp);

    return 0;
}