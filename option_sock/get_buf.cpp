#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

using namespace std;
int main(int argc, char **argv)
{
    int sock;
    socklen_t len;
    int state, recv_buf, send_buf;
    sock = socket(PF_INET, SOCK_STREAM, 0);
    len = sizeof(send_buf);
    state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&send_buf, &len);
    if (state)
    {
        perror("getsockopt() error :");
    }
    cout << "send_buf:" << send_buf << endl;
    len = sizeof(recv_buf);
    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&recv_buf, &len);
    if (state)
    {
        perror("getsockopt() error :");
    }
    cout << "recv_buf:" << recv_buf << endl;

    

    return 0;
}