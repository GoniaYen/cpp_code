#include <iostream>
#include <unistd.h>


#define BUF_SIZE 30

using namespace std;

int main(int argc,char **argv)
{

    int fds[2];
    char buf[BUF_SIZE];
    char str[] = "who are you?";
    pid_t pid;

    pipe(fds);

    pid = fork();


    if(pid == 0){
        write(fds[1],str,sizeof(str));
    }else
    {
        read(fds[0],buf,BUF_SIZE);
        puts(buf);
    }
    

    return 0;
}
