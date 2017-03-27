#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include"uart.h"


#define FALSE (-1)
//#define STDIN_FILENO 0

int fd;//: File descriptor for the port

int main(void)
{
	int counter = 0;
//	int port_state = 0;
	char buffer[1000];
	
	//½ø³ÌºÅ
	{
		printf("The PID of this process in %d\n",getpid());
		printf("The PPID of this process in %d\n",getppid());
	}
	
	
	printf("\nhello world !\n\n");

	fd = open_port("/dev/ttyUSB0");
//	printf("port_state:%d\n",port_state);
//	printf("port_state:%d\n\n",port_state);
	
	if(uart_set(fd,115200,0,8,'N',1) == -1)
    {
        fprintf(stderr,"uart set failed!\n");
        exit(EXIT_FAILURE);
    }
	else
	{
		printf("uart_set ok!\n\n");
	}
	while(1)
	{
		int i=0;
//		counter++;
//		printf("begin read..........\n");
//		printf("counter:%d\n",counter);
//		printf("begin read..........");
		counter = read(fd,buffer,1000);
		printf("counter:%d\n",counter);
		
		for(i=0; i<counter; i++)
		{
//			printf("%x ",buffer[i]);
		}	
		for(i=0; i<counter; i++)
		{
			printf("%c ",buffer[i]);
		}	
		
		printf("\n\n\n");
		
		usleep(1000000);
	}

	return 0;
}


