#include <iostream>
#include <unistd.h>
using namespace std;

int gval = 10;

int main(int argc, char **argv)
{
    pid_t pid;
    int lval = 20;
    gval ++ ;
    lval += 5;

    pid = fork();

    if (pid == 0)
    {
        gval += 2;
        lval += 2;
    }
    else
    {
        gval -= 2;
        lval -= 2;
    }
     if (pid == 0)
    {
        cout<<"child proc : gval = "<<gval<<" lval = "<<lval<<endl;
    }
    else
    {
         cout<<"parent proc : gval = "<<gval<<" lval = "<<lval<<endl;
    }
    return 0;
}