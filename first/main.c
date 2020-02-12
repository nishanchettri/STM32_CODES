#include "stm32f10x.h"

int main()
{
	RCC ->APB2ENR |= (1<<4); //ENABLING PORT C , GPIO IN AHB>APB2
	GPIOC->CRH |= (1<<20)|(1<<21) ; // GPIO C13 MAX SPEED 50 MHZ
  GPIOC->CRH &= ~((1<<22)|(1<<23));//GPIO C13 AS OUTPUT
	
	while(1)
	{
		
      GPIOC->BSRR = GPIO_BSRR_BS13; 
		  for(int i=0;i<500000;i++);
		  GPIOC->BSRR = GPIO_BSRR_BR13; 
		  for(int i=0;i<500000;i++);
	}
}

	