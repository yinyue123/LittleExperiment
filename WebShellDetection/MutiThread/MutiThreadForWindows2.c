#include <stdio.h>
#include <windows.h>

//gcc MutiThreadForLinux2.c

int tick=1000;
CRITICAL_SECTION cs;

DWORD WINAPI thread(LPVOID p){
	char *a=(char *) p;
	while(1){
		EnterCriticalSection(&cs);
		if(tick>0){
			//GetCurrentThreadId()
			printf("%s...sale%d\n",a,tick--);
		}
		LeaveCriticalSection(&cs);
		Sleep(10);
	}
}

int main(){
	HANDLE ret[4];

	InitializeCriticalSection(&cs);
	
	ret[0]=CreateThread(
		NULL,	//线程安全属性
		0,		//堆栈大小
		thread,	//线程函数
		(char *)"Thread1",	
		0,		//线程创建属性
		NULL	//线程ID
	);
	ret[1]=CreateThread(NULL,0,thread,(char *)"Thread2",0,NULL);
	ret[2]=CreateThread(NULL,0,thread,(char *)"Thread3",0,NULL);
	ret[3]=CreateThread(NULL,0,thread,(char *)"Thread4",0,NULL);
		
	WaitForMultipleObjects(4,ret,TRUE,INFINITE);
	
	CloseHandle(ret[0]);
	CloseHandle(ret[1]);
	CloseHandle(ret[2]);
	CloseHandle(ret[3]);

	DeleteCriticalSection(&cs);

	return 0;
}
