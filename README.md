# Pthread Tutorial

Pthread 라이브러리 사용을 위한 기본 튜토리얼

1. 컴파일 옵션

```sh
# 컴파일 할 때 뒤에 -pthread 옵션을 붙여주어야 한다.
gcc -o myprog myprog.c -pthread 
```

2. 스레드 생성 및 소멸

스레드를 생성하기 위해서는 pthread_create() 함수를 이용해야 한다.

pthread_create() 함수는 다른 호출들에서 사용될 수 있는 thread identifier를 제공한다.
```C
int	pthread_create(pthread_t *tid, const pthread_attr_t *tattr,
    void*(*start_routine)(void *), void *arg);

//첫번째 인자 : thread identifier
//두번째 인자 : thread attribute (Null Pointer means default setting)
//세번째 인자 : thread가 실행하고자 하는 함수의 포인터
//네번째 인자 : thread로 보내는 데이터
```



You should plan to collect the exit status of all the threads you create by calling pthread_join() on each thread eventually.

프로세스가 종료되어서 스레드가 강제종료되는 상황이 발생하지 않도록 하기 위해서 프로세스가 종료되기 전에 스레드를 종료되게 한다.

pthread_cancel...

Exercise 1.

Write a program that creates 10 threads. Have each thread execute the same function and pass each thread a unique number. Each thread should print ...
five times where 'n' is replaced by the thread's number. Use an array of pthread_t objects to hold the various thread IDs. Be sure the program doesn't terminate until all the threads are complete

```C

// Exercise 1 Solution
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_MAX 3

void * thread_function (void * arg)
{
    int *  incoming = (int *)arg;
    int * cnt = malloc(sizeof(int));
    
    for(;*cnt < 5; (*cnt)++) printf("Hello, World. I'm Thread %d\n", *incoming);

    return NULL;
}

int main (void)
{
    pthread_t thread_id[THREAD_MAX];
    void *    exit_status[THREAD_MAX];
    int value;
    int idx  = 0;
    value = 42;

    for(int idx = 0; idx < THREAD_MAX; idx++)
    {
        pthread_create(&thread_id[idx], NULL, thread_function, idx);
        pthread_join(thread_id[idx], &exit_status[idx]);
    }

    return 0;
}
```

```C
//실행 결과 ex1-1.c
Hello, World This is Thread 1
Hello, World This is Thread 1
Hello, World This is Thread 1
Hello, World This is Thread 2
Hello, World This is Thread 2
Hello, World This is Thread 0
Hello, World This is Thread 0
Hello, World This is Thread 0
Hello, World This is Thread 0
```
```C
// ex1-1-join.c 실행결과
Hello, World This is Thread 0
Hello, World This is Thread 0
Hello, World This is Thread 0
Hello, World This is Thread 0
Hello, World This is Thread 0
Hello, World This is Thread 1
Hello, World This is Thread 1
Hello, World This is Thread 1
Hello, World This is Thread 1
Hello, World This is Thread 1
Hello, World This is Thread 2
Hello, World This is Thread 2
Hello, World This is Thread 2
Hello, World This is Thread 2
Hello, World This is Thread 2
```

3. 스레드로 부터 값을 전달받기

```C
#define DEFAULT_VALUE 200
void * thread_function (void * arg)
{
    int code = DEFAULT_VALUE;
    return (void *)code;
}

// 이러한 방법은 integer가 pointer로 변환되고 나서 다시 integer로 변해도 데이터 손실이 발생하지 않는 환경에서만 가능하다.

// 조금 더 개선해보면 다음과 같은 형태로 나타낼 수도 있다. 

void * thread_function (void * arg)
{
    char buffer[64];
    return buffer;
}

// 이러한 방식의 전달은 type에 따라 달라지지 않는다. 이러한 지역변수 선언을 통해 전달하면 thread function이 종료됨에 따라서 사라지게 되기 때문에 정의되지 않은 주소를 반환하게 된다.

void * thread_function (void * arg)
{
    static char buffer[64];
    return buffer;
}

// 따라서 사라지지 않게 static으로 선언하면 스레드가 종료된 다음에도 계속해서 값을 유지할 수 있다. 
// 하지만 이러한 방식의 해결은 Multi-threaded 환경에서는 부적절해지는데 여러 스레드가 이 static 변수에 동시에 접근하게 되면 race condition이 발생하게 되고 이는 전역변수가 겪는 문제와 동일하다.


void * thread_function (void * arg)
{
    char * buffer = (char *)malloc(sizeof(char));

    return buffer;
}

// 이번에는 동적 할당을 이용해 선언되었다.
// 이러한 방식의 할당은 서로 다른 thread에서 실행되더라도 각각의 stack 메모리에 할당되기 때문에 모두 다른 메모리에 저장된다. 따라서 static 변수로 선언했을 때의 문제를 해결할 수 있다. 
```
Exercise 1.

Write a program that computes the square roots of the integers from 0 to 99 in a separate thread and returns an array of doubles containing the results. In the meantime the main thread should display a short message to the user and then display the results of the computation when they are ready.

```bash
gcc -o ex2 ex2-1.c -pthread -lm
```
```C

//ex2-1.c 실행 결과
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // malloc()
#include <math.h>   // sqrt()

#define MAX 100

void * thread_function(void * arg)
void * root_calculate(void * arg)

void * thread_function (void * arg)
{
    int * coming = (int *)arg;
    pthread_t   thread_id[MAX];
    void *      exit_status[MAX];
    double * sqrt_arr = malloc(sizeof(double) * MAX);
    int cnt = 0;
    for (cnt = 0; cnt < MAX ; cnt++)
    {
        pthread_create(&thread_id[cnt], NULL, thread_function, &cnt);
        pthread_join(thread_id[cnt], &exit_status[cnt]);
        printf("Thread Function : %.4lf\n", *(double *)exit_status[cnt]);
        sqrt_arr[cnt] = *(double *)exit_status[cnt];
    }
    return (void *)sqrt_arr;
}
// 1부터 100까지의 sqrt 값을 전달하는 스레드
void * root calculate(void * arg)
{
    int * incoming = (int *)arg;
    double * rt = (double *)malloc(sizeof(double));
    * rt = sqrt((double) * incoming);
    printf("Root Calculate : %.4lf\n", *rt);
    return (void *)rt;
}
// the thread that calculate the root value

int main (void)
{
    pthread_t thread_id;
    void * exit_status;
    int value;

    int idx = 0;

    pthread_create(&thread_id, NULL, thread_function, &value);
    pthread_join(thread_id, *exit_status);
    for(idx = 0; idx < MAX; idx++)
    {
        printf("Sqrt Value : %.4lf\n", *((double *)exit_status + idx));
    }
    return 0;
}
```
Exercise 2.

Imagine that the computations done by the program above were much more time consuming merely calculating a few square roots. Imagine also that displaying the "short message" was also fairly time consuming. For example, perhaps the message needed to be fetched from a network server as HTML and then rendered. Would you expect the multithreaded program to perform better than a single threaded program that, for example, did the calculations and then fetched the message? Explain.



3. Thread Synchronization

- Mutex

When writing multi-threaded programs it is frequently necessary to enforce mutually exclusive access to __a shared data object__.

How to use :

1) Declare an object of type pthread_mutex_t

2) Initialize the object by calling pthread_mutex_init()

3) Call pthread_mutexe_lock() to gain exclusive access to the shared data object.

4) Call pthread_mutex_unlock() to release the execlusive access and allow another thread to use the shared data object

5) Get rid of the object by calling pthread_mutex_destroy()

It is important to understand that if a thread attempts to lock the mutex while some other thread has it locked, the second thread is blocked until the first releases the mutex with pthread_mutex_unlock()


```C
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // malloc()
#include <math.h>   // sqrt()
#include <unistd.h>
#define MAX 100

pthread_mutex_t lock;
int shdata = 32768 // Shared Data can be given more complicated form.
void * thread_fn (void * arg)
{
    int idx;

    for(idx = 0; idx < MAX; idx++)
    {
        pthread_mutex_lock(&lock);
        // Critical Section Access
        pthread_mutex_unlock(&lock);
    }
}
int main (void)
{
    pthread_t thread_id;
    void * exit_status;
    int value;

    int idx = 0;

    pthread_create(&thread_id, NULL, thread_fn, &value);
    //pthread_join(thread_id, &exit_status);
    for(idx = 0; idx < 10; idx++)
    {
        // mutex 없이 접근하면 예상했던 결과값과 다른 값이 출력된다.
        printf("Shared Data : %d\n", shdata);
        //따라서 모든 Critical Section에 접근할 때 mutex 처리가 필요하다.


    }
    return 0;
}

```

- No thread should attempt to lock or unlock a mutex that has not been initialized.
- 모든 스레드는 초기화되지 않은 mutex를 lock 또는 unlock하려고 시도하면 안된다.

- The thread that locks a mutex must be the thread that unlocks it.
- mutex를 잠그는 스레드가 mutex를 풀어야 한다.

- No thread should have the mutex locked when you destroy the mutex.
- 모든 스레드는 mutex를 destroy 하려 할 때 mutex를 잠그고 있으면 안된다.

- Any mutex that is intialized should eventually destroyed, but only after any thread that uses it has either terminated or is no longer interesting in using it.
- 초기화 된 mutex는 결국 destroy되어야한다.

`mutex attribute` : 뮤텍스 속성, pthread_mutex_init()을 통해서 설정될 수 있다.
```C
pthread_mutex_init(pthread_mutex_t mutex, pthread_attr_mutex_t * mutex_attribute);
```

Exercise 1.

Enter the program in Lisiting 2 and try it out. Does it behave the way you expected? 
Try different values for the maximum loop index in the thread function and different sleep times in the main function. 
Try removing the call to __sleep()__ entirely. 
Try the program on different machines. Can you explain what is happening?

>> 예상한대로 Shared Data가 증가되서 나타난다. sleep(1) 함수를 없애도 공유자원에는 하나의 스레드만 접근해서 값이 의도치 않게 변경되는 경우는 발생하지 않는다.

Excercise 2.

Suppose you are building a C++ string class that you intend to use in a multi-threaded program. You are worried about your string objects possibly getting corrupted if they are updated by more than one thread at a time. You consider adding a mutex as a member of each string and locking that mutex whenever any string method is called. Discuss the implications.

>> string 클래스에 mutex를 private 멤버 변수로 추가하고 method 내부에서 string 값을 변경할 때 mutex_lock 과 mutex_unlock을 해놓는다.

- Condition Variables

하나의 스레드에서 다른 스레드로 이벤트 발생을 시키고 싶다면 Condition Variable을 써야한다. 

하나의 스레드가 특정 조건을 기다리고 있을 때 thread_cond_wait()을 통해 대기하고 조건을 충족했을 때 pthread_cond_signal()을 통해 호출한다.

```C
// Condition Variable 관련 함수들

int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
int pthread_cond_wait(pthread_cond_t* cond, pthread_mutex_t* mutex );
int pthread_cond_signal(pthread_cond_t* cond);

```

```C
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

int data=0;

void *increase(void *arg){
        while(1){
                pthread_mutex_lock(&mutex);
                pthread_cond_signal(&cond);
                data++;
                pthread_mutex_unlock(&mutex);
                sleep(1);
        }
}

void *printData(void *arg){
        while(1){
                pthread_mutex_lock(&mutex);
                pthread_cond_wait(&cond,&mutex);
                printf("data :%d\n",data);
                pthread_mutex_unlock(&mutex);
        }
}
int main()
{
    pthread_t thread1,thread2;

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
    pthread_create(&thread1, NULL, increase,NULL);
    pthread_create(&thread2, NULL, printData,NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
```

Exercise 1.

Modify the program in Listing 3 to print message and add delays(or wait for user input) at various places so you can verify that the thread is, in fact, wating for the condition as appropriate. Verify that the thread does not wait if the condition is already true when it is first tested.

Exercise 2.

In the text above, when a condition is signaled the signaling thread releases the mutex before calling pthread_cond_signal(). However, it is also possible swap those operations as shown below.

```C
pthread_mutex_lock(&mutex);
flag = 1;
pthread_cond_signal(&condition);
pthread_mutex_unlock(&mutex);
```

Does this result in the same behavior as before? Are any race conditions introduced by this change? How does this approach impact application performance?

> race condition이 발생하지 않고 동일하게 동작한다. 하지만 성능상에 차이가 발생하는데 lock과 unlock 사이에 signal이 발생하면 호출받은 스레드가 실행되기 전에 공유 메모리의 mutex 소유권을 signal을 호출한 스레드 쪽에서 가지고 있으므로 공유메모리로의 접근이 불가능하다. 따라서 그 때까지 대기를 해야하고 결국엔 성능 저하로 이어진다. 

>따라서 가능한 한 pthread_cond_signal은 unlcok 뒤에 실행해야 한다.

- [관련 링크](https://stackoverflow.com/questions/59087852/what-happens-to-a-thread-calling-pthread-cond-signal)

- Semaphore

Semaphore are essentially glorified integer counters.
They support two primary operations. 

One operation, called _down_ or _wait_ attempts to decrement the counter.
The other operation, called _up_ and _signal_ attempts to increment the counter.

semaphore는 _binary semaphore_ 와 _integer semaphore_ 가 존재한다.

Another difference between a pthread mutex and a semaphore is that, unlike a mutex, a semaphore can be signaled in a different thread than the thread that does the wait operation.

Mutex와 Semaphore의 차이점은 mutex는 호출한 thread에서 lock과 unlock 처리를 해주어야 하지만 semaphore는 lock한 thread와 unlock하는 thread가 다를수 있다.

```C
#include <semaphore.h>

int shraed;
sem_t binary_sem;

void *thread_function(void * arg)
{
    sem_wait(&binary_sem);
    // Shared Memory
    sem_signal(&binary_sem);
}


int main(void)
{
    sem_init(&binary,_sem, 1);

    // thread_create()
    sem_wait(&binary_sem);
    // Use Share Resource
    sem_signal(&binary_sem);

    // thread_join

    sem_destory(&binary_sem);
}
```

Exercise 1.

Using POSIX mutex and condition variables, implement a semaphore abstract type. For example, consider a header file containing the following.

```C
struct semaphore
{

};

void semaphore_init(struct semaphore *s, int initial_count);
void semaphore_destroy(struct semaphore *s);
void semaphore_wait(struct semaphore *s);
void semaphore_signal(struct semaphore *s);
```
Implement the functions declared above. This shows that semaphores are not strictly necessry as part of a low level API.

Exercise 2. 

Some semaphore APIs allow the signal operation to advance the value of a semaphore by more than one. This can be implemented by executing a basic signal operation multiple times in a loop.
However, such an approach is inefficient if the number to be added to the semaphore is large. Extend your solution for the question above so that __semaphore_signal__ takes an additional integer parameter specifying the how much the semaphore value is to be advanced. Try to use an efficient method of handling large advances. 

Make sure your solution works properly and does not suffer from any race conditions even when there are multiple threads waiting on the semaphore.


- Reader / Writer Locks


4. Thread Models


- Boss / Worker Model

Here the idea is to have a single _boss thread_ and several _worker thread_ 

1) Queue up the work to be handled later as soon as a worker is free

2) Create more worker threads

3) Blcok until a worker is free to take the new work.

We can example website or bank situation.

이 모델의 장점은 각 Task가 독립적일 때 제일 효과적이다. 만약 각 Task가 독립적이지 않으면 수행 중인 Worker Thread사이에 통신이 필요하게되고 이는 결국 성능 저하로 이끌어진다.

- Pipeline Model

- Backgroudn Task Model