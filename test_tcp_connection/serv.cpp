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

    struct  sockaddr_in ser_addr;
    struct  sockaddr_in cli_addr;
    
    socklen_t cli_add_size;

    char msg[]  = "hello";

    ser_sock = socket(AF_INET,SOCK_STREAM,0);
    if(ser_sock==-1){
        perror("socket error");
        return -1;
    }

    bzero(&ser_addr,sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port=htons(9999);
    ser_addr.sin_addr.s_addr=htonl(INADDR_ANY);

    if(bind(ser_sock,(struct sockaddr*)&ser_addr,sizeof(ser_addr))==-1){
        perror("bind() error");
        return -1;
    }

    if(listen(ser_sock,5)==-1){
        perror("listen() error");
        return -1;
    }
    cli_add_size= sizeof(cli_addr);
    cli_sock = accept(ser_sock,(struct sockaddr*)&cli_addr,&cli_add_size);
    if(cli_sock==-1){
        perror("accept() error");
        return -1;
    }
    
    cout<<"connect from "<<ntohl(cli_addr.sin_addr.s_addr) <<endl;

    write(cli_sock,msg,sizeof(msg));
    close(cli_sock);
    close(ser_sock);
    return 0;
}