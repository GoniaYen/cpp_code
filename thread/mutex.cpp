#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;
#define NUM_THREAD 100
pthread_mutex_t mutex;
long long sum = 0;
void *thread_ins(void *argv);
void *thread_des(void *argv);
int main(int argc, char const *argv[])
{
    pthread_t id[NUM_THREAD];

    cout << "Sizeof long long :" << sizeof(sum)<<endl;
    pthread_mutex_init(&mutex,NULL);
    for (int i = 0; i < NUM_THREAD; i++)
    {
        if (i % 2)
        {
            pthread_create(&(id[i]), NULL, thread_ins, NULL);
        }
        else
        {
            pthread_create(&(id[i]), NULL, thread_des, NULL);
        }
    }
    for (int i = 0; i < NUM_THREAD; i++)
    {
        pthread_join(id[i], NULL);
    }

    cout << "sum : " << sum << endl;
    pthread_mutex_destroy(&mutex);
    return 0;
}

void *thread_ins(void *argv)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 50000000; i++)
    {
        sum += 1;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void *thread_des(void *argv)
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 50000000; i++)
    {
        sum -= 1;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}