#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>



using namespace std;

int main()
{
    int ser_sock;
    struct sockaddr_in ser_addr;
    char msg[512];

    ser_sock = socket(AF_INET,SOCK_STREAM,0);
    if(ser_sock==-1){
        perror("socket() error");
        return -1;
    }

    bzero(&ser_addr,sizeof(ser_addr));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port = htons(9999);
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(ser_sock,(struct sockaddr*)&ser_addr,sizeof(ser_addr))==-1){
        perror("connect() error");
        return -1;
    }
    if(read(ser_sock,msg,sizeof(msg))==-1){
        perror("read() error");
        return -1;
    }
    cout<<msg<<endl;
    close(ser_sock);


    return 0;
}
