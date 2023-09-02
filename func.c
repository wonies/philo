#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void	*thread_routine(void *arg)
{
	pthread_mutex_t *mutex = (pthread_mutex_t *)arg;
	
	pthread_t tid;
	tid = pthread_self();

	int  i = 0;
	printf("\ttid:%lx\n", tid);
	while (i < 10)
	{
		pthread_mutex_lock(mutex);
		printf("\tnew thread:%d\n", i);
		i++;
		pthread_mutex_unlock(mutex);
		sleep(1);
	}
}

int main()
{
	pthread_t thread;
	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread, NULL, thread_routine, &mutex);
	// pthread_detach(thread);
	int i = 0;
	printf("tid:%lx\n", pthread_self());
	while (i < 5)
	{
		printf("main:%d\n", i);
		i++;
		sleep(1);
	}
	pthread_join(thread,NULL);
	pthread_mutex_destroy(&mutex);
}
