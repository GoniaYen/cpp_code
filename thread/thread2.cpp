#include <iostream>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;
void *thread_main(void *argv)
{
    int cnt = *((int *)argv);
    char *msg = (char *)malloc(sizeof(char)*50);
    strcpy(msg,"Hello,i am thread~\n");
    for (int i = 0; i < cnt; i++)

    {
        sleep(1);
        cout << "running thread" << endl;
    }
    return (void*)msg;
}
int main(int argc, char const *argv[])
{
    pthread_t t_id;
    int thread_param = 5;
    void *thr_set;
    if (pthread_create(&t_id, NULL, thread_main, (void *)&thread_param) != 0)
    {
        perror("pthread_create() error");
        return -1;
    }
    if(pthread_join(t_id,&thr_set)!=0){
        perror("pthread_join() error");
        return -1;
    }
  cout<<"thread return message : "<<(char *)thr_set<<endl;
  free(thr_set);

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
