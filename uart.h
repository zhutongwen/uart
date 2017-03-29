
#ifndef UART_DEF
#define UART_DEF

int open_port(char *port);
int uart_set(int fd,int baude,int c_flow,int bits,char parity,int stop);
void uart_test(void);

#endif
