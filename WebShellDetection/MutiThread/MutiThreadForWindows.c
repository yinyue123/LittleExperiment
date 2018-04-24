#include <windows.h>
#include <stdio.h>

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	printf("ThreadProc \r\n");
	
	return 0;
}

int main(int argc,char* argv[])
{
	HANDLE hThread=CreateThread(NULL,	//线程安全属性
				0,		//堆栈大小
				ThreadProc,	//线程函数
				NULL,		//参数
				0,		//线程创建属性
				NULL);		//线程ID

	printf("main \r\n");
	WaitForSingleObject(hThread,INFINITE);
	CloseHandle(hThread);
	return 0;
}
