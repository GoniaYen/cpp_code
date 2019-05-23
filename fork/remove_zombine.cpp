#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
using namespace std;

void read_childproc(int sig)
{
    int statues;
    pid_t id = waitpid(-1, &statues, 0);
    if (WIFEXITED(statues))
    {
        cout << "Remove proc id:" << id << endl;
        cout << "Child send :" << WEXITSTATUS(statues) << endl;
    }
}

int main(int argc, char **argv)
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    pid = fork();

    if (pid == 0)
    {
        puts("Hi i am child process");
        sleep(10);
        return 12;
    }
    else
    {
        cout << " Child proc id: " << pid << endl;
        pid = fork();

        if (pid == 0)
        {
            puts("Hi i am child process");
            sleep(10);
            exit(24);
        }
        else
        {
            int i;
            cout << " Child proc id: " << pid << endl;
            for (int i = 0; i < 5; i++)
            {
                puts("wait...");
                sleep(5);
            }
        }
    }

    return 0;
}