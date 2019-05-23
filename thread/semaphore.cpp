#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
using namespace std;


void *read(void *argv);
void *accu(void *argv);

static sem_t sem_one;
static sem_t sem_two;
static int num;
int main(int argc, char const *argv[])
{
    pthread_t id1,id2;
    
    sem_init(&sem_one,0,0);
    sem_init(&sem_two,0,1);

    pthread_create(&id1,NULL,read,NULL);
    pthread_create(&id2,NULL,accu,NULL);
    pthread_join(id1,NULL);
    pthread_join(id2,NULL);

    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    return 0;
}

void *read(void *argv)
{
   
    for (int i = 0; i < 5; i++)
    {
       fputs("inpt num: ",stdout);
       sem_wait(&sem_two);
       cin>>num;
       sem_post(&sem_one);
    }

    return NULL;
}
void *accu(void *argv)
{
   int sum = 0 ;
   for (int i = 0; i < 5; i++)
   {
      sem_wait(&sem_one);
      sum += num;
      sem_post(&sem_two);
   }
   cout<<"reslut : "<<sum<<endl;
   
    return NULL;
}