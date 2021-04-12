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
pthread_mutex_t lock1;
pthread_mutex_t lock2;
#define cus 10
#define chefSz 3

queue<int> q1;
int cnt = 1;
void init_semaphore1()
{
	sem_init(&empty1,0,3);
	sem_init(&full1,0,0);
	pthread_mutex_init(&lock1,0);
}
void * O(void * arg)
{
    int* producer_id = (int*)arg;
	printf("I am Oxizen producer %d\n",(int*)arg);

        sem_wait(&empty1);
		pthread_mutex_lock(&lock1);
		sleep(1);
		q1.push(cnt);
		printf("Oxizen produced %d has placed item %d\n", producer_id, cnt);
		cnt++;
        pthread_mutex_unlock(&lock1);
        sem_post(&full1);
}


void * C(void * arg)
{
        int* customer_id = (int*)arg;
        printf("I am Carbon %d\n",(int*)arg);
        sem_wait(&empty1);
		pthread_mutex_lock(&lock1);
		sleep(1);
		cnt++;
		q1.push(cnt);
		printf("Carbon dioxide produced item %d\n", customer_id);



		pthread_mutex_lock(&lock2);
        printf("Water is Produced\n");
        pthread_mutex_unlock(&lock2);
        sem_post(&full1);
}
//buff1


int main(void)
{

	printf("\t\t\t\tName: Md Saiful\n");
	printf("\t\t\t\tID: 2019-2-60-040\n");
	pthread_t thread1[2];
	pthread_t thread2;
    int x[2] = {1, 2};
    int y[1] = {1};
    init_semaphore1();


	for (int i = 0; i < 2; i++){
        pthread_create(&thread1[i], NULL, O, (void*) *(x+i));
	}
	for (int i = 0; i < 1; i++){
        pthread_create(&thread1[i], NULL, C, (void*) *(y+i));
	}

	while(1);
	return 0;
}
