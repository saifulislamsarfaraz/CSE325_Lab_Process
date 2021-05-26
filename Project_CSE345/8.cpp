#include<bits/stdc++.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<queue>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
//Group ID: 8
//Name : Md Saiful
//Id : 2019-2-60-040
//Name :Jekrul Islam Shajib
//ID : 2019-2-60-046
sem_t empty1;
sem_t full1;
sem_t empty2;
sem_t full2;
sem_t empty3;
sem_t full3;
sem_t empty4;
sem_t full4;
sem_t coord;
sem_t cust_ready;
sem_t finished;
sem_t leave_chair;
sem_t payment;
sem_t receipt;
pthread_mutex_t lock1;
pthread_mutex_t lock2;
pthread_mutex_t lock3;
pthread_mutex_t lock4;
pthread_mutex_t lock5;
pthread_mutex_t lock6;
pthread_mutex_t lock7;
pthread_mutex_t lock8;
pthread_mutex_t lock9;

queue<int> chair;
queue<int> sofa;
queue<int> q3;
queue<int> q4;

void init_semaphore()
{

	sem_init(&empty1,0,20);
	sem_init(&full1,0,0);
	pthread_mutex_init(&lock1,0);
	sem_init(&empty2,0,4);
	sem_init(&full2,0,0);
	pthread_mutex_init(&lock2,0);
	sem_init(&empty3,0,3);
	sem_init(&full3,0,0);
	pthread_mutex_init(&lock3,0);
	sem_init(&empty4,0,1);
	sem_init(&full4,0,0);
	pthread_mutex_init(&lock4,0);
	sem_init(&cust_ready,0,0);
	sem_init(&finished,0,0);
	sem_init(&leave_chair,0,0);
	sem_init(&payment,0,0);
	sem_init(&receipt,0,0);
}


void * customer(void * arg)
{
    sem_wait(&empty1);
    pthread_mutex_lock(&lock1);
    printf("customer enter room\n");
    sem_wait(&empty2);
    pthread_mutex_lock(&lock2);
    printf("customer seat sofa\n");
    sem_wait(&empty3);
    pthread_mutex_lock(&lock3);
    printf("get up from sofa\n");
    pthread_mutex_unlock(&lock3);
    sem_post(&empty3);
    printf("seat in barber chair\n");
    pthread_mutex_unlock(&lock4);
    sleep(1);
    sem_post(&cust_ready);
    pthread_mutex_lock(&lock5);
    sem_wait(&finished);
    printf("leave barber chair\n");
    pthread_mutex_unlock(&lock6);
    sem_post(&leave_chair);
    printf("make payment\n");
    pthread_mutex_unlock(&lock7);
    sem_post(&payment);
    sem_wait(&receipt);
    pthread_mutex_lock(&lock8);
    printf("exit from shop\n");
    pthread_mutex_unlock(&lock1);
    sem_post(&empty1);




}



void * barber(void * arg)
{

	while(true){
            sem_wait(&cust_ready);
            pthread_mutex_lock(&lock4);
           // pthread_mutex_lock(&lock9);
            printf("cut hair\n");
           // pthread_mutex_unlock(&lock9);
            pthread_mutex_unlock(&lock5);
            sem_post(&finished);
            sem_wait(&leave_chair);
            pthread_mutex_lock(&lock6);
            pthread_mutex_unlock(&lock2);
            sem_post(&empty2);
	}
}



void * cashier(void * arg)
{
    printf("I am Cashier\n");
	while(true)
	{
        sem_wait(&payment);
        pthread_mutex_lock(&lock7);

       // pthread_mutex_lock(&lock9);
        printf("accept Payments");
       // pthread_mutex_lock(&lock9);
        pthread_mutex_unlock(&lock8);
        sem_post(&receipt);

	}

}


int main(void)
{

	printf("\t\t\t\tName: Md Saiful\n");
	printf("\t\t\t\tID: 2019-2-60-040\n");
	pthread_t thread1[10];
	pthread_t thread2[3];
	pthread_t thread3;
    int x[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    init_semaphore();



	for (int i = 0; i < 20; i++){
        pthread_create(&thread1[i], NULL, customer, NULL);
	}
    for(int i = 0; i < 3; i++){
	   pthread_create(&thread2[i], NULL, barber, NULL);
    }
    pthread_create(&thread3,NULL,cashier,NULL);




	while(1);
	return 0;
}
