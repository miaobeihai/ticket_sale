 ///
 /// @file    pthread_cond.c
 /// @author  miaobeihai(452686191@qq.com)
 /// @date    2017-02-08 10:30:17
 ///
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t mutex;
pthread_cond_t cond;
void* thread (void* p)
{
	printf("pthread create sucess\n");
	pthread_mutex_lock(&mutex);
	int ret;
	ret=pthread_cond_wait(&cond,&mutex);
	if(ret!=0)
	{
    	printf("cond ret %d\n",ret);
		return (void*)-1;
	}
	pthread_mutex_unlock(&mutex);
	printf("cond_wait create sucess\n");
	return NULL;
}
int main()
{
	pthread_t pthid;
	pthread_mutex_init(&mutex,NULL);
	int ret;
	ret=pthread_cond_init(&cond,NULL);
	if(ret!=0)
	{
		printf("cond init ret %d\n",ret);
		return -1;
	}
	pthread_create(&pthid,NULL,thread,NULL);
	sleep(1);
    ret=pthread_cond_signal(&cond);
	if(ret!=0)
	{
		printf("cond signal ret %d\n",ret);
		return -1;
	}
	pthread_join(pthid,NULL);
	return 0;
}
	
