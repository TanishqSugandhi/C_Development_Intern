// producer_consumer.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUF_SIZE 5
int buffer[BUF_SIZE];
int count = 0, in = 0, out = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t can_produce = PTHREAD_COND_INITIALIZER;
pthread_cond_t can_consume = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int id = *(int*)arg;
    for (int i=0;i<10;i++) {
        usleep((rand()%100 + 50)*1000);
        pthread_mutex_lock(&m);
        while (count == BUF_SIZE) pthread_cond_wait(&can_produce, &m);
        buffer[in] = i + id*100;
        in = (in+1)%BUF_SIZE;
        count++;
        printf("[P%d] produced %d (count=%d)\n", id, buffer[(in-1+BUF_SIZE)%BUF_SIZE], count);
        pthread_cond_signal(&can_consume);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void *consumer(void *arg) {
    int id = *(int*)arg;
    for (int i=0;i<10;i++) {
        usleep((rand()%150 + 50)*1000);
        pthread_mutex_lock(&m);
        while (count == 0) pthread_cond_wait(&can_consume, &m);
        int val = buffer[out];
        out = (out+1)%BUF_SIZE;
        count--;
        printf("    [C%d] consumed %d (count=%d)\n", id, val, count);
        pthread_cond_signal(&can_produce);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() {
    srand((unsigned)time(NULL));
    pthread_t p1,p2,c1,c2;
    int id1=1,id2=2;
    pthread_create(&p1,NULL,producer,&id1);
    pthread_create(&p2,NULL,producer,&id2);
    pthread_create(&c1,NULL,consumer,&id1);
    pthread_create(&c2,NULL,consumer,&id2);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(c1,NULL);
    pthread_join(c2,NULL);
    printf("All done.\n");
    return 0;
}
