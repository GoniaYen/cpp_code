#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;



int main(int argc, char **argv)
{
    int status;
    pid_t pid=fork();;
   
    if (pid == 0)
    {
       return 3;
    }
    else
    {
        cout<<"child PID1 :"<<pid<<endl;
        pid=fork();
        if(pid == 0){
            exit(7);
        }else
        {
             cout<<"child PID2 :"<<pid<<endl;
             wait(&status);
             if(WIFEXITED(status)){
                   cout<<"child send one : :"<<WEXITSTATUS(status)<<endl;
             }
             wait(&status);
             if(WIFEXITED(status)){
                   cout<<"child send two : :"<<WEXITSTATUS(status)<<endl;
             }
             sleep(30);
             
        }
        
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