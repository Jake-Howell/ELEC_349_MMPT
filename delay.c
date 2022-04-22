#include "main.h"
#include "stm32f407xx.h"                  // Device header

volatile unsigned int sysTickCounter;

void SysTick_Init(void) 
{
while (SysTick_Config(SystemCoreClock/1000) != 0) {} // One SysTick interrupt now equals 1us
	NVIC_SetPriority(SysTick_IRQn,2);
}//This method needs to be called in the SysTick_Handler


//void TimeTick_Decrement(void) 
//{
//if (sysTickCounter != 0x00) {sysTickCounter--;}
//}

void delay_nus(unsigned int n) //delay of  n microseconds
{
sysTickCounter = n;
while (sysTickCounter != 0) {}
}

void delay_1ms(void) //delay of 1 ms
{
sysTickCounter = 1000;
while (sysTickCounter != 0) {}
}

int delay_nms(unsigned int n) //delay of n milliseconds
{
	sysTickCounter=n;
	while(sysTickCounter>0);
	return 1;
}

void SysTick_Handler(void) 
{
if(sysTickCounter>0) sysTickCounter--;
}

