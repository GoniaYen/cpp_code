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
int main()
{
    int sock,str_len;
    char msg[BUF_SIZE];
    struct sockaddr_in serv_addr;
    

    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock==-1){
        perror("socket() error");
        return -1;
    }

    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port = htons(9999);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1){
        perror("connect() error");
        return -1;
    }else
    {
        fputs("Connected...",stdout);
    }
    while(1)
    {
        fputs("Input message(Q or q to quit):",stdout);
        fgets(msg,BUF_SIZE,stdin);
        if(!strcmp(msg,"q\n")||!strcmp(msg,"Q\n")){
            break;
        }
        write(sock,msg,strlen(msg));
        str_len = read(sock,msg,BUF_SIZE-1);
        msg[str_len]='\0';
        cout<<"message from server :"<<msg<<endl;
    }
    close(sock);

    return 0;
}
