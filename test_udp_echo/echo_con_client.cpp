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
int main(int argc,char **argv)
{
    int sock,str_len;
    char msg[BUF_SIZE];
    socklen_t addr_size;//多余
    struct sockaddr_in serv_addr,from_addr;//不再需要from_addr
    

    sock = socket(PF_INET,SOCK_DGRAM,0);
    if(sock==-1){
        perror("socket() error");
        return -1;
    }
    if(argc != 2){
        cout<<"缺少参数：prot"<<endl;
        return -1;
    }
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
    connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));//建立链接

    while(1)
    {
        fputs("Input message(Q or q to quit):",stdout);
        fgets(msg,BUF_SIZE,stdin);
        if(!strcmp(msg,"q\n")||!strcmp(msg,"Q\n")){
            break;
        }
        write(sock,msg,strlen(msg));
        str_len = read(sock,msg,sizeof(msg)-1);

        // sendto(sock,msg,strlen(msg),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
        // str_len = recvfrom(sock,msg,BUF_SIZE,0,(struct sockaddr*)&from_addr,&addr_size);
        
        msg[str_len]='\0';
        cout<<"message from server :"<<msg<<endl;
    }
    close(sock);

    return 0;
}
