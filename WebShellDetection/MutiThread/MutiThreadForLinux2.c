#include <stdio.h>
#include <pthread.h>

//gcc MutiThreadForLinux.c -lpthread -o demo2

int tick=1000;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
struct timespec delay;

void thread(char *arg){
	while(1){
		pthread_mutex_lock(&mutex);
		if(tick>0){
			//sleep(1);
			//pthread_delay_np(&delay);
			printf("%s...sale%d\n",arg,tick--);
		}
		pthread_mutex_unlock(&mutex);
	}
}

int main(){
	pthread_t id1,id2,id3,id4;
	int ret1,ret2,ret3,ret4;
	
	delay.tv_sec=0;
	delay.tv_nsec=10000;//1000 nanoseconds = 1 ms
	 
	
	ret1=pthread_create(&id1,NULL,(void *) thread,"Thread1");
	if(ret1!=0){
		printf("creat pthread error!\n");
		exit(1);
	}
	ret2=pthread_create(&id2,NULL,(void *) thread,"Thread2");
    if(ret2!=0){
        printf("creat pthread error!\n");
        exit(1);
    }
	ret3=pthread_create(&id3,NULL,(void *) thread,"Thread3");
    if(ret3!=0){
        printf("creat pthread error!\n");
        exit(1);
    }
	ret4=pthread_create(&id4,NULL,(void *) thread,"Thread4");
    if(ret4!=0){
        printf("creat pthread error!\n");
        exit(1);
    }
		
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	pthread_join(id3,NULL);
	pthread_join(id4,NULL);

	pthread_mutex_destroy(&mutex);
	
	return 0;
}
