/* 
Author: Nishan Chettri
Github: nishanchettri
Instagram:nishanchettri
Facebook: nishanchettri0
Email: nishanchettri@gmail.com
*/

/**************************************LIBRARIES*************************************/
                              #include "stm32f10x.h"
															#include "stdlib.h"
															#include "stdint.h"
                              #include "string.h"
                              #include "stdarg.h"
/************************************************************************************/
static void nisprint(char *receivedMessage,...);
#define randomDelay for(int i=0;i<5000000;i++)

int main()
{
	
	//ENABLE CLOCK FOR USART1 AND PORTA
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN ;
	
	//ENABLE OUTPUT MODE FOR PIN A9 @50MHZ IN CRH REGISTER
	GPIOA->CRH |= GPIO_CRH_MODE9 ;
	
	//SET OUTPUT MODE AS ALTERNATE FUNCTION PUSH-PULL
	GPIOA->CRH |= GPIO_CRH_CNF9_1 ;
	GPIOA->CRH &= ~(GPIO_CRH_CNF9_0) ;
	
	// SET BAUDRATE TO 9600
	USART1->BRR= 0x1D4C;
	
	//ENABLE USART1 | TX | RX FROM CONTROL REGISTER 1
	USART1->CR1|= (1<<13)|(1<<3)|(1<<2) ;
  
	while(1)
	{
		if(USART1->SR&USART_SR_RXNE)
		{
		nisprint("my name is nishan\n");
		randomDelay;
		}
		
	}
	
}

//FUNCTION TO CONVERT RECEIVED DATA TO STRING
//FUNCTION TO PRINT DATA TO SERIAL MONITOR
static void nisprint(char *receivedMessage,...)
{
	char buffer[100];
	//make print function like in C
	va_list args;
	va_start(args,receivedMessage);
	vsprintf(buffer,receivedMessage,args);
	
	for(int n=0;n<strlen(buffer);n++)
	{
		USART1->DR=buffer[n];
//WAIT TILL THE TXE FLAG =0 MEANS THE DATA IS TRANSFERRED
		while(!(USART1->SR&(1<<7)));
	}
}