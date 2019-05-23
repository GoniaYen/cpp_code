#include <iostream>
#include <unistd.h>


#define BUF_SIZE 30

using namespace std;

int main(int argc,char **argv)
{

    int fds1[2],fds2[2];
    char buf[BUF_SIZE];
    char str1[] = "who are you?";
    char str2[] = "thanks your message!";
    pid_t pid;

    pipe(fds1);pipe(fds2);
    pid = fork();

    if(pid == 0){
        write(fds1[1],str1,sizeof(str1));
        read(fds2[0],buf,BUF_SIZE);
        cout<<"Child proc output : "<<buf<<endl;
    }else
    {
        read(fds1[0],buf,BUF_SIZE);
        cout<<"Parent proc output : "<<buf<<endl;
        write(fds2[1],str2,sizeof(str2));
        sleep(3);
    }
    

    return 0;
}
