#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define THREAD_MAX 20
#define COUNT 100

pthread_mutex_t mutex;
pthread_cond_t cond;

int data = 32768;
/*
void * thread_function (void * arg)
{
	int * incoming = (int *)arg;
	int * cnt = malloc(sizeof(int));
	* cnt = 0;
	for(; *cnt < 5; (*cnt)++) printf("Hello, World This is Thread %d\n", *incoming);
	
	free(cnt);
	return NULL;
}
*/

void * increase (void * arg)
{
	while(1)
	{
		//sleep(1);	
		pthread_mutex_lock(&mutex);
		data++;
		if(data >= 40000)
		{
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

void * print (void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(data >= 40000)
		{
			pthread_mutex_unlock(&mutex);
			break;
		}
		pthread_cond_wait(&cond, &mutex);
		printf("Current Data : %d\n", data );		
		pthread_mutex_unlock(&mutex);
	}
	return NULL;	
}

int main (void)
{
	pthread_t thread1, thread2;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	pthread_create(&thread1, NULL, increase, NULL);
	pthread_create(&thread2, NULL, print, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Last Data : %d\n",data);	
	return 0;
}
