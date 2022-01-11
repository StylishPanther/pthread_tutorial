#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define THREAD_MAX 20
#define COUNT 100

pthread_mutex_t lock;
int shdata = 32768;
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

void * thread_fn (void * arg)
{
	int idx;

	for(idx = 0 ; idx < COUNT ; idx++)
	{
		pthread_mutex_lock(&lock);
		printf("Thread Data : %d\n", shdata);	
		++shdata;
		pthread_mutex_unlock(&lock);
	}

	return NULL;
}
int main (void)
{
	pthread_t	thread_id;
	void *		exit_status;
	int			value;

	int idx = 0;
	int cnt = 0;
	value = 42;
	pthread_mutex_init(&lock, NULL);
	pthread_create(&thread_id, NULL, thread_fn, &idx);	
	
	for(idx = 0; idx < 10; idx++)
	{
		//sleep(1);
		pthread_mutex_lock(&lock);
		printf("!!!!!!!!!!!Shared Data : %d!!!!!!!\n", shdata);	
		pthread_mutex_unlock(&lock);
	}

	pthread_join(thread_id, &exit_status);
	for(idx = 0; idx < THREAD_MAX; idx++)
	{
		//pthread_create(&thread_id[idx], NULL, thread_function, &idx);	
		//pthread_join(thread_id[idx], &exit_status[idx]);
	}
	//for(cnt = 0 ; cnt < 50; cnt++)	printf("Main Process Executing\n");
	return 0;
}
