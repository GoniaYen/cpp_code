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
    int serv_sock, clnt_sock;
    int str_len, i;

    char msg[BUF_SIZE];

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;

    socklen_t clnt_addr_size;

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        return -1;
    }

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9999);
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

    for (i = 0; i < 5; i++)
    {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1)
        {
            perror("accept() error");
            return -1;
        }else{
            cout<<"Connect client"<<i+1<<endl;;
        }
        while((str_len = read(clnt_sock,msg,BUF_SIZE))!=0){
            write(clnt_sock,msg,str_len);
        }
        close(clnt_sock);
        
    }

    close(serv_sock);
    
    return 0;
}