#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;
void *thread_main(void *argv)
{
    int cnt = *((int *)argv);
    for (int i = 0; i < cnt; i++)

    {
        sleep(1);
        cout << "running thread" << endl;
    }
    return NULL;
}
int main(int argc, char const *argv[])
{
    pthread_t t_id;
    int thread_param = 5;
    if (pthread_create(&t_id, NULL, thread_main, (void *)&thread_param) != 0)
    {
        perror("pthread_create() error");
        return -1;
    }
    sleep(2);
    //sleep(10);
    cout << "end if main" << endl;

    return 0;
}
// void *thread_main(void *argv)
// {
//     int cnt = *((int *)argv);
//     for (int i = 0; i < cnt; i++)

//     {
//        sleep(1);
//        cout<<"running thread"<<endl;
//     }
//     return NULL;

// }
