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
    int str_len=0, i;

    char msg[BUF_SIZE];

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;

    socklen_t clnt_addr_size;

    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (serv_sock == -1)
    {
        return -1;
    }
    if(argc!=2){
        cout<<"缺少参数：port"<<endl;
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

    clnt_addr_size = sizeof(clnt_addr);

    while(1){
        str_len = recvfrom(serv_sock,msg,BUF_SIZE,0,(struct sockaddr *)&clnt_addr,&clnt_addr_size);
        sendto(serv_sock,msg,str_len,0,(struct sockaddr *)&clnt_addr,clnt_addr_size);       
    }
    

    close(serv_sock);
    
    return 0;
}