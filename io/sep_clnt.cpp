#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>


#define BUF_SIZE 1024
using namespace std;

int main(int argc,char **argv)
{
    int ser_sock;
    struct sockaddr_in ser_addr;
    char msg[BUF_SIZE];
    FILE *readfp;
    FILE *writefp;


    ser_sock = socket(AF_INET,SOCK_STREAM,0);
    if(ser_sock==-1){
        perror("socket() error");
        return -1;
    }

    bzero(&ser_addr,sizeof(ser_addr));
    ser_addr.sin_family=AF_INET;
    ser_addr.sin_port = htons(atoi(argv[1]));
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(ser_sock,(struct sockaddr*)&ser_addr,sizeof(ser_addr))==-1){
        perror("connect() error");
        return -1;
    }
    readfp = fdopen(ser_sock,"r");
    writefp = fdopen(ser_sock,"w");
    while (1)
    {
        if(fgets(msg,sizeof(msg),readfp)==NULL){
            break;
        }
        fputs(msg,stdout);
        fflush(stdout);
    }
    fputs("from client : thank you! \n",writefp);
    fflush(writefp);
    fclose(writefp);
    fclose(readfp);
  

    return 0;
}
