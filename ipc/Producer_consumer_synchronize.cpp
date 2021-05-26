#include<bits/stdc++.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<queue>
#include<stdlib.h>
#include<unistd.h>
using namespace std;
//Name : md Saiful
//Id :2019-2-60-040
sem_t empty1;
sem_t full1;
sem_t empty2;
sem_t full2;
sem_t empty3;
sem_t full3;
sem_t empty4;
sem_t full4;
int cnt_sister = 0;
int cnt_father = 0;
int cnt_brother = 0;
int cnt_mother = 0;
int omlete=0;
void init_semaphore()
{
	sem_init(&empty1,0,1);
	sem_init(&full1,0,0);
	sem_init(&empty2,0,8);
	sem_init(&full2,0,0);
	sem_init(&empty3,0,1);
	sem_init(&full3,0,0);
	sem_init(&empty4,0,1);
	sem_init(&full4,0,0);
}

void * onion(void * arg)
{
    sem_wait(&empty1);
    printf("Onion Provide\n");
    sem_post(&full2);
    sem_post(&full2);
}
void * chili(void * arg)
{
        sem_wait(&full2);
        printf("Chili provide\n");
        cnt_brother++;
        if(cnt_brother==2){
            sem_post(&full3);
        }
        else if(cnt_brother==4){
        sem_post(&full3);
        omlete++;
        printf("Omlete ready %d\n",omlete);
        sem_post(&full2);
        sem_post(&full2);
        }
        else if(cnt_brother==6){
            omlete++;
            printf("Omlete ready %d\n",omlete);
        sem_post(&full2);
        sem_post(&full2);
        }
        else if(cnt_brother==8){
        omlete++;
        printf("Omlete ready %d\n",omlete);
        }



}
void * egg(void * arg)
{
    sem_wait(&full3);
    printf("Egg provide\n");
    cnt_father++;
    if(cnt_father==1){
        sem_post(&full4);
    }
}
void * salt(void * arg)
{
    sem_wait(&full4);
    printf("Salt provide\n");
    omlete++;
    printf("Omlete ready %d\n",omlete);
    sem_post(&empty1);

}

int main(void)
{

	printf("\t\t\t\tName: Md Saiful\n");
	printf("\t\t\t\tID: 2019-2-60-040\n");
	pthread_t thread1[2];
	pthread_t thread2[8];
	pthread_t thread3[2];
	pthread_t thread4;
    init_semaphore();
    for(int i = 0; i < 2; i++){
	   pthread_create(&thread1[i], NULL, onion, NULL);
    }
    for(int i = 0; i < 8; i++){
	   pthread_create(&thread2[i], NULL, chili, NULL);
    }
	for (int i = 0; i < 2; i++){
        pthread_create(&thread3[i], NULL, egg, NULL);
	}
    pthread_create(&thread4,NULL,salt,NULL);

	while(1);
	return 0;
}
