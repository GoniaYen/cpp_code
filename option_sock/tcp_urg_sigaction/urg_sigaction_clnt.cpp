#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

int main(int argc, char * argv[])
{
    if ( argc <3 )
    {
        perror("缺少参数：");
        return 1;
    }

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family = PF_INET;
    address.sin_addr.s_addr = htonl(atoi(argv[1]))
    address.sin_port = htons(atoi(argv[2]));

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert (sockfd >= 0);
    if ( connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0 )
    {
        perror("connect() failed");
    }
    else
    {
        const char *oob_data = "abcdef";
        const char *normal_data = "1234";
        send(sockfd, oob_data, strlen("abcdef"), MSG_OOB);
        sleep(1);
        send(sockfd, normal_data,strlen("1234"),0);
        send(sockfd, normal_data,strlen("1234"),0);
    }

    close(sockfd);
    return 0;
}
