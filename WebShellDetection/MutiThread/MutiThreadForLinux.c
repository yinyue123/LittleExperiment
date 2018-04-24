#include <stdio.h>
#include <pthread.h>

//gcc MutiThreadForLinux.c -lpthread -o demo

void thread(){
	int i;
	for( i=0; i<60; i++) 
		printf("demo run---%d\n",i);
}

int main(){
	pthread_t id;
	int i,ret;
	ret=pthread_create(&id,NULL,(void *) thread,NULL);
	if(ret!=0){
		printf("creat pthread error!\n");
		exit(1);
	}
	for( i=0; i<60; i++)
	  printf("hello world--%d\n",i);
	pthread_join(id,NULL);//等待第一个进程结束
	return 0;
}
