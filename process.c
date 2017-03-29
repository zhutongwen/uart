
/* fork.c */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define pit_t int

int fork_test(void)
{
	pit_t result;
	
	//int test = 0;
	
	//打印进程号
	/*
	{
	 printf("\n\n\nThe PID of this process is %d\n",getpid());
	 printf("The PPID of this process is %d\n",getppid());
	}
	*/
	
	//调用fork函数
	result = vfork();
	
	//test = 1;
		
	/*通过 result 的值来判断 fork()函数的返回情况，首先进行出错处理*/
	if(result == -1)
	{
		printf("Fork error\n");
	}
	else if (result == 0) /*返回值为 0 代表子进��*/
	{
		printf("The returned value is %d\nIn child process!!\nMy PID is %d\n",result,getpid());
	}
	else /*返回值大��0 代表父进��*/
	{
		printf("The returned value is %d\nIn father process!!\nMy PID is %d\n",result,getpid());
	}
	
//	exit(0);
	while(1);
	return result;
}
