#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

using namespace std;
int main(int argc,char **argv)
{
    int tcp_sock,udp_sock;
    int sock_type;
    socklen_t oplen;
    int state;

    oplen = sizeof(sock_type);
    tcp_sock = socket(PF_INET,SOCK_STREAM,0);
    udp_sock = socket(PF_INET,SOCK_DGRAM,0);

    cout<<"tcp_sock:"<<tcp_sock<<endl;
    cout<<"udp_sock:"<<udp_sock<<endl;

    state = getsockopt(tcp_sock,IPPROTO_TCP,TCP_NODELAY,(void*)&sock_type,&oplen);
    if(state){
        perror("getsockopt() error :");
    }
    cout<<"sock type one "<<sock_type<<endl;

    state = getsockopt(udp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&oplen);
    if(state){
        perror("getsockopt() error :");
    }
     cout<<"sock type two "<<sock_type<<endl;



    return 0;
}