# STM32_Cubemx_UARTIDLE_CPP
cubemx构建的原始工程，其中包含DMA空闲中断实现的不定长串口内容接收C++库

# 如果不能运行
工程应该可以直接运行，不能运行的直接用cubemx生成一个打开DMA的串口，然后在对stm32f1xx_it.c的串口中断程序中把空闲处理函数加进去
```
注意该函数要添加到stm32f1xx_it.c的串口中断中
void USART1_IRQHandler(void)
{
	UsartReceive_IDLE(&huart1);
  HAL_UART_IRQHandler(&huart1);
}
```
