#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define THREAD_MAX 20
#define MAX 100

void * thread_function (void * arg);
void * root_calculate (void * arg);

void * thread_function (void * arg)
{
	int * incoming = (int *)arg;
	pthread_t thread_id[MAX];
	void *		exit_status[MAX];
	double * sqrt_arr  = malloc(sizeof(double) * MAX);
	int cnt = 0;
	for(cnt = 0; cnt < MAX; cnt++) 
	{
		pthread_create(&thread_id[cnt], NULL, root_calculate, &cnt);
		pthread_join(thread_id[cnt], &exit_status[cnt]);
		printf("Thread Function : %.4lf\n", *(double *)exit_status[cnt]);
		sqrt_arr[cnt] = *(double *)exit_status[cnt];
	}
	
	
	return (void *)sqrt_arr;
}
void* root_calculate (void * arg)
{
	int * incoming = (int *)arg;
	double * rt = malloc(sizeof(double));
	* rt = sqrt((double) *incoming);
	printf("Root Calculate : %.4lf\n", *rt);
	return (void *)rt;
}
int main (void)
{
	pthread_t thread_id;
	void *		exit_status;
	int			value;

	int idx = 0;
	int cnt = 0;
	value = 42;
	
	
	pthread_create(&thread_id, NULL, thread_function, &idx);	
	pthread_join(thread_id, &exit_status);

	
	
	for(cnt = 0 ; cnt < MAX; cnt++)	printf("Sqrt Value : %.4lf\n", *((double *)exit_status + cnt));
	return 0;
}
