#include "MyUart.h"
#include "usart.h"
#include "string.h"



MyUart *Uart1;

MyUart::MyUart(UART_HandleTypeDef* inituart){
//MyUart_Library::MyUart_Library(){
	this->uart = inituart;
	HAL_UART_Receive_DMA(this->uart, usartDMA_rxBuf, RECEIVELEN);
  __HAL_UART_ENABLE_IT(this->uart, UART_IT_IDLE); //使能空闲中断
	this->rx_len = 0;
	memset(this->usartDMA_rxBuf,0,RECEIVELEN);
	this->dmaSend_flag = 0;
	this->receive_flag = 0;
}

//DMA发送函数
void MyUart::SendData_DMA(uint8_t *pdata, uint16_t Length)
{
		//HAL_GPIO_WritePin(RT_485_GPIO_Port,RT_485_Pin,GPIO_PIN_SET);
    while(this->dmaSend_flag == USART_DMA_SENDING);
    this->dmaSend_flag = USART_DMA_SENDING;
    HAL_UART_Transmit_DMA(uart, pdata, Length);
}


//下面要根据具体的对象名来修改

void MyUart_Init(MyUart ** uart,UART_HandleTypeDef* inituart){
	*uart = new MyUart(inituart);
	//uart = new MyUart();
}
//DMA发送回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    __HAL_DMA_DISABLE(huart->hdmatx);
    if(huart == &huart1){
        Uart1->dmaSend_flag = USART_DMA_SENDOVER;
		}
		/*
		if(huart == &huart2){
        Usart2Type.dmaSend_flag = USART_DMA_SENDOVER;
		}
		if(huart == &huart3){
			//HAL_GPIO_WritePin(RT_485_GPIO_Port,RT_485_Pin,GPIO_PIN_RESET);//进入接收态
			Usart3Type.dmaSend_flag = USART_DMA_SENDOVER;
		}
		*/
}

//串口接收空闲中断
/*
注意该函数要添加到stm32f1xx_it.c的串口中断中
void USART1_IRQHandler(void)
{
	UsartReceive_IDLE(&huart1);
  HAL_UART_IRQHandler(&huart1);
}

*/
void UsartReceive_IDLE(UART_HandleTypeDef *huart)
{
    uint32_t temp;

    if((__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET))
    {
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        HAL_UART_DMAStop(huart);
        temp = huart->hdmarx->Instance->CNDTR;
        if(huart==&huart1) {
            Uart1->rx_len =  RECEIVELEN - temp;
            Uart1->receive_flag=1;
            HAL_UART_Receive_DMA(&huart1,Uart1->usartDMA_rxBuf,RECEIVELEN);
					//下面添加该串口的内容解析函数
					Uart1->SendData_DMA(Uart1->usartDMA_rxBuf,Uart1->rx_len);
					Uart1->rx_len = 0;
        }
				/*
        else if(huart==&huart2) {
            Usart2Type.rx_len =  RECEIVELEN - temp;
            Usart2Type.receive_flag=1;
            HAL_UART_Receive_DMA(&huart2,Usart2Type.usartDMA_rxBuf,RECEIVELEN);
				//下面添加该串口的内容解析函数
        }
        else if(huart==&huart3) {
            Usart3Type.rx_len =  RECEIVELEN - temp;
            Usart3Type.receive_flag=1;
            HAL_UART_Receive_DMA(&huart3,Usart3Type.usartDMA_rxBuf,RECEIVELEN);
				//下面添加该串口的内容解析函数
        }
				*/
    }
}
