#include <iostream>
#include <unistd.h>
using namespace std;



int main(int argc, char **argv)
{
    pid_t pid=fork();;
   
    if (pid == 0)
    {
       cout<<"Hi I am child process!"<<endl;
    }
    else
    {
        cout<<"child PID :"<<pid<<endl;
        sleep(30);
    }
     if (pid == 0)
    {
        cout<<"end child process"<<endl;
    }
    else
    {
         cout<<"end parent process"<<endl;
    }
    return 0;
}