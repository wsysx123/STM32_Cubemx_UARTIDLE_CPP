#ifndef _MYUART_
#define _MYUART_
#include "usart.h"
#include <stdint.h>

class MyUart_Library;

#define RECEIVELEN 100
#define USART_DMA_SENDING 1//发送中标志位
#define USART_DMA_SENDOVER 0//发送完成标志位

typedef struct  
{  
	
}USART_RECEIVETYPE;

class MyUart {
	public:
		uint8_t receive_flag:1;//空闲接收标记
		uint8_t dmaSend_flag:1;//发送完成标记
		uint16_t rx_len;//接收长度
		uint8_t usartDMA_rxBuf[RECEIVELEN];//DMA接收缓存
	
		//USART_RECEIVETYPE UsartType;
		MyUart(UART_HandleTypeDef*);
		MyUart();
		void SendData_DMA(uint8_t *pdata, uint16_t Length);
	private:
		UART_HandleTypeDef* uart;		
};

extern MyUart *Uart1;

void MyUart_Init(MyUart ** uart,UART_HandleTypeDef* inituart);


#endif

