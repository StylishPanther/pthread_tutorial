#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define THREAD_MAX 3
void * thread_function (void * arg)
{
	int * incoming = (int *)arg;
	int * cnt = malloc(sizeof(int));
	* cnt = 0;
	for(; *cnt < 5; (*cnt)++) printf("Hello, World This is Thread %d\n", *incoming);
	
	free(cnt);
	return NULL;
}

int main (void)
{
	pthread_t thread_id[THREAD_MAX];
	void *		exit_status[THREAD_MAX];
	int			value;

	int idx = 0;
	int cnt = 0;
	value = 42;
	
	for(idx = 0; idx < THREAD_MAX; idx++)
	{
		pthread_create(&thread_id[idx], NULL, thread_function, &idx);	
		pthread_join(thread_id[idx], &exit_status[idx]);
	}
	//for(cnt = 0 ; cnt < 50; cnt++)	printf("Main Process Executing\n");
	return 0;
}
