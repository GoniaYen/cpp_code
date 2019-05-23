#include <iostream>
#include <unistd.h>


#define BUF_SIZE 30

using namespace std;

int main(int argc,char **argv)
{

    int fds[2];
    char buf[BUF_SIZE];
    char str1[] = "who are you?";
    char str2[] = "thanks your message!";
    pid_t pid;

    pipe(fds);
    pid = fork();

    if(pid == 0){
        write(fds[1],str1,sizeof(str1));
        sleep(2);
        read(fds[0],buf,BUF_SIZE);
        cout<<"Child proc output : "<<buf<<endl;
    }else
    {
        read(fds[0],buf,BUF_SIZE);
        cout<<"Parent proc output : "<<buf<<endl;
        write(fds[1],str2,sizeof(str2));
        sleep(3);
    }
    

    return 0;
}
