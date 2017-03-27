#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<assert.h>
#include<termios.h>
#include<string.h>
#include<sys/time.h>
#include<sys/types.h>
#include<errno.h>

#define FALSE (-1)


/******************************************************************
*brief:		open uart port
*intput:	port: file name (include path)(ttyS0,ttyS1,ttyS2)/dev/ttyUSB0			
*ruturn:	file descriptor
*
*******************************************************************/
int open_port(char *port)
{
	int fd;
	fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
	//	fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
	if (fd == -1)
	{
		/*
		 * Could not open the port.
		 */
		perror("open_port: Unable to open /dev/ttyUSB0\n");
		return FALSE;
	}
	else
	{
		printf("open USB0 OK!\n");
	}
	/*清除串口非阻塞标*/
	if(fcntl(fd,F_SETFL,0) < 0)
	{
		fprintf(stderr,"fcntl failed!\n");
		return -1;
	}
	else
	{
		printf("清除串口非阻塞标��OK!\n");
	}
	printf("fd = %d!\n\n\n\n",fd);
	return fd;
}

/******************************************************************
*brief:		uart set
*intput:	fd: file descriptor;
			baude: (should be 9600 or 115200)
			c_flow: flow control(should be 0 ,1 or 2)
			bits: 
*ruturn:	
*
*******************************************************************/
int uart_set(int fd,int baude,int c_flow,int bits,char parity,int stop)
{
	struct termios options;
	/*获取终端属*/
	if(tcgetattr(fd,&options) < 0)
	{        
		perror("tcgetattr error");
		return -1;
	}
	/*设置输入输出波特率，两者保持一致*/
	switch(baude)
	{
		case 9600:
			cfsetispeed(&options,B9600);
			cfsetospeed(&options,B9600);
			break;
		case 115200:
			cfsetispeed(&options,B115200);
			cfsetospeed(&options,B115200);
			break;
		default:
			fprintf(stderr,"Unkown baude!\n");
			return -1;
	}
	/*设置控制模式*/
	options.c_cflag |= CLOCAL;//保证程序不占用串��
	options.c_cflag |= CREAD;//保证程序可以从串口中读取数据
	/*设置数据流控��*/
	switch(c_flow)
	{
		case 0://不进行流控制
			options.c_cflag &= ~CRTSCTS;
			break;
		case 1://进行硬件流控��
			options.c_cflag |= CRTSCTS;
			break;
		case 2://进行软件流控��
			options.c_cflag |= IXON|IXOFF|IXANY;
			break;
		default:
			fprintf(stderr,"Unkown c_flow!\n");
			return -1;
	}

	/*设置数据��*/
	switch(bits)
	{
		case 5:
			options.c_cflag &= ~CSIZE;//屏蔽其它标志��
			options.c_cflag |= CS5;
			break;
		case 6:
			options.c_cflag &= ~CSIZE;//屏蔽其它标志��
			options.c_cflag |= CS6;
			break;
		case 7:
			options.c_cflag &= ~CSIZE;//屏蔽其它标志��
			options.c_cflag |= CS7;
			break;
		case 8:
			options.c_cflag &= ~CSIZE;//屏蔽其它标志��
			options.c_cflag |= CS8;
			break;
		default:
			fprintf(stderr,"Unkown bits!\n");
			return -1;
	}

	/*设置校验��*/
	switch(parity)
	{
		/*无奇偶校验位*/
		case 'n':
		case 'N':
		options.c_cflag &= ~PARENB;//PARENB：产生奇偶位，执行奇偶校��
		options.c_cflag &= ~INPCK;//INPCK：使奇偶校验起作��
		break;
		/*设为空格,即停止位����*/
		case 's':
		case 'S':
			options.c_cflag &= ~PARENB;//PARENB：产生奇偶位，执行奇偶校��
			options.c_cflag &= ~CSTOPB;//CSTOPB：使用两位停止位
			break;
		/*设置奇校��*/
		case 'o':
		case 'O':
			options.c_cflag |= PARENB;//PARENB：产生奇偶位，执行奇偶校��
			options.c_cflag |= PARODD;//PARODD：若设置则为奇校��否则为偶校验
			options.c_cflag |= INPCK;//INPCK：使奇偶校验起作��
			options.c_cflag |= ISTRIP;//ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8��
			break;
		/*设置偶校��*/
		case 'e':
		case 'E':
			options.c_cflag |= PARENB;//PARENB：产生奇偶位，执行奇偶校��
			options.c_cflag &= ~PARODD;//PARODD：若设置则为奇校��否则为偶校验
			options.c_cflag |= INPCK;//INPCK：使奇偶校验起作��
			options.c_cflag |= ISTRIP;//ISTRIP：若设置则有效输入数字被剥离7个字节，否则保留全部8��
			break;
		default:
			fprintf(stderr,"Unkown parity!\n");
			return -1;
	}

	/*设置停止��*/
	switch(stop)
	{
		case 1:
			options.c_cflag &= ~CSTOPB;//CSTOPB：使用两位停止位
			break;
		case 2:
			options.c_cflag |= CSTOPB;//CSTOPB：使用两位停止位
			break;
		default:
			fprintf(stderr,"Unkown stop!\n");
			return -1;
	}

	/*设置输出模式为原始输��*/
	options.c_oflag &= ~OPOST;//OPOST：若设置则按定义的输出处理，否则所有c_oflag失效
	/*设置本地模式为原始模��*/
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	/*
	 *ICANON：允许规范模式进行输入处��
	 *ECHO：允许输入字符的本地回显
	 *ECHOE：在接收EPASE时执行Backspace,Space,Backspace组合
	 *ISIG：允许信��
	 */

	/*设置等待时间和最小接受字��*/
	options.c_cc[VTIME] = 0;//可以在select中设��
	options.c_cc[VMIN] = 1;//最少读取一个字��

	/*如果发生数据溢出，只接受数据，但是不进行读操��*/
	tcflush(fd,TCIFLUSH);

	/*激活配��*/
	if(tcsetattr(fd,TCSANOW,&options) < 0)
	{
		perror("tcsetattr failed");
		return -1;
	}
	return 0;
}

