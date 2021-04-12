#include<bits/stdc++.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<queue>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
//Name : md saiful
//Id :2019-2-60-040
sem_t empty1;
sem_t full1;
sem_t empty2;
sem_t full2;
sem_t empty3;
sem_t full3;
pthread_mutex_t lock1;
pthread_mutex_t lock2;
pthread_mutex_t lock3;

#define cus 10
#define chefSz 3

queue<int> q1;
queue<int> q2;
queue<int> q3;
int cnt = 0;
void * chef(void * arg);
void * masterChef(void * arg);
void * waiter(void * arg);
void init_semaphore1()
{
	sem_init(&empty1,0,5);
	sem_init(&full1,0,0);
	pthread_mutex_init(&lock1,0);
}
void init_semaphore2()
{
	sem_init(&empty2,0,3);
	sem_init(&full2,0,0);
	pthread_mutex_init(&lock2,0);
}
void init_semaphore3()
{
	sem_init(&empty3,0,1);
	sem_init(&full3,0,0);
	pthread_mutex_init(&lock3,0);
}

void * customer(void * arg)
{
    int* customer_id = (int*)arg;
	printf("I am Customer %d\n",(int*)arg);


		sem_wait(&empty1);//buffer 0
		pthread_mutex_lock(&lock1);//consume
		sleep(1);
		cnt++;
		q1.push(cnt);
		printf("customer %d has placed his order\n",customer_id);
        pthread_mutex_unlock(&lock1);
        sem_post(&full1);



}
//buff1
void * chef(void * arg)
{

    printf("I am chef%c\n",(char*)arg);
	int i;
	char* chef_id = (char*)arg;
	while(true){

        sem_wait(&full1);
		pthread_mutex_lock(&lock1);
		sleep(1);
		int item = q1.front();
		q1.pop();
		printf("Chef%c has prepared order %d\n", chef_id,item);
        pthread_mutex_unlock(&lock1);
        sem_post(&empty1);


		sem_wait(&empty2);
        pthread_mutex_lock(&lock2);
        sleep(1);
        q2.push(item);
		printf("Chef%c has sent order %d to masterChef\n", chef_id,item);
        pthread_mutex_unlock(&lock2);
        sem_post(&full2);




	}
}
//buff2
void * masterChef(void * arg)
{
    printf("I am MasterChef\n");
	while(true)
	{
        sem_wait(&full2);
        pthread_mutex_lock(&lock2);
		sleep(1);
		int item = q2.front();
		q2.pop();
        printf("masterChef has checked order %d\n",item);
        pthread_mutex_unlock(&lock2);
        sem_post(&empty2);






		sem_wait(&empty3);
        pthread_mutex_lock(&lock3);
        sleep(1);
        q3.push(item);
        printf("masterChef has called waiter to collect order %d\n",item);
        pthread_mutex_unlock(&lock3);
        sem_post(&full3);



	}

}
//buff3
void * waiter(void * arg)
{
    printf("I am waiter\n");
    while(true)
	{
        sem_wait(&full3);
        pthread_mutex_lock(&lock3);


		sleep(1);
		int item = q3.front();
		q3.pop();
		printf("waiter has delivered order %d\n",item);
        pthread_mutex_unlock(&lock3);


        sem_post(&empty3);
	}
	return NULL;
}

int main(void)
{

	printf("\t\t\t\tName: Md Saiful\n");
	printf("\t\t\t\tID: 2019-2-60-040\n");
	pthread_t thread1[10];
	pthread_t thread2[3];
	pthread_t thread3;
	pthread_t thread4;
    int x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    char a[3] = {'A','B','C'};
    init_semaphore1();
    init_semaphore2();
    init_semaphore3();


	for (int i = 0; i < 10; i++){
        pthread_create(&thread1[i], NULL, customer, (void*) *(x+i));
	}
    for(int i = 0; i < 3; i++){
	   pthread_create(&thread2[i], NULL, chef, (void*) *(a+i));
    }
    pthread_create(&thread4,NULL,waiter,NULL);
    pthread_create(&thread3,NULL,masterChef,NULL);



	while(1);
	return 0;
}
