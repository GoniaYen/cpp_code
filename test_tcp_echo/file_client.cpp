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
    FILE *fp;
    char buf[BUF_SIZE];
    int read_serv;
    int sock;

    struct sockaddr_in serv_addr;
    if (argc != 2)
    {
        cout << "缺少参数　port:" << endl;
        return -1;
    }
    fp = fopen("serv.txt", "wb+");
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("socket() error : ");
        return -1;
    }
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr =inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(atoi(argv[1]));

    connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));


    while((read_serv=read(sock,buf,BUF_SIZE))!=0){
        fwrite((void*)buf,1,read_serv,fp);
    }
    
    cout<<"收到数据"<<endl;
    write(sock,"Thank you !",10);
    fclose(fp);
    close(sock);
    return 0;
}