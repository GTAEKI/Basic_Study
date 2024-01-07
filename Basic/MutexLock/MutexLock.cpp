#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

// mutex라는 이름의 자물쇠 초기화
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int shared = 0;

void *foo(void * arg)
{
    pthread_mutex_lock(&mutex); // 자물쇠 잠그기
    for (int i = 0; i < 10000; ++i) {
        shared += 1;
    }
    pthread_mutex_unlock(&mutex); // 자물쇠 풀기
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, foo, NULL);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("final result is %d\n", shared);

    return 0;
}