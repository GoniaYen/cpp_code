#include <iostream>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
using namespace std;
int sum  = 0;
void *thread_summation(void *argv)
{
    int start = ((int *)argv)[0];
    int end = ((int *)argv)[1];
    while (start<=end)
    {
        sum += start;
        start++;
    }
    
    return NULL;
}
int main(int argc, char const *argv[])
{
    pthread_t id_t1,id_t2;
    int range1[]={1,5};
    int range2[]={6,10};
    pthread_create(&id_t1, NULL, thread_summation, (void *)range1);
    pthread_create(&id_t2, NULL, thread_summation, (void *)range2);
    pthread_join(id_t1,NULL);
    pthread_join(id_t2,NULL);
    cout<<"sum : "<<sum<<endl;
    return 0;
}

