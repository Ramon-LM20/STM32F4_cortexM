#include "stm32f401xe.h"



int config(void);

int init = 0;

int main(void)
{

	init = config();

	while(config)
	{
		/*
		  ODR : Output Data Register
		  this register is used to drive voltage to the pin. (in this case is toggleling the PIN A 5)

		  GPIOA->ODR ^=(1U<<5); // using the output data register (ODR) to toggle PIN A5
		  for(int i=0;i<100000;i++){}
		*/


		/*
		 IDR : Input Data Register
		 this register is used for store the logical state of a pin configured as input

		 Read the state of the pushbutton and writing the output to the led
		 pressed -> led_on
		 released -> led_off

		 note: in this board the push button is active low / no debounce implemented
		*/
		if(GPIOC->IDR & (1U<<13))
		{
		/*
		  BSRR : Bit Set/Reset Register
		  this is a 32 bits register where the lowest 16 bits are used for setting and the highest 16 bits are used for reseting;
		*/
		GPIOA->BSRR |= (1U<<21);
		}
		else
		{
		GPIOA->BSRR |= (1U<<5);
		}
	}

	return 0;
}

int config()
{

	/* 1. Enables clock access to GPIOA and GPIOC */
	RCC->AHB1ENR |= (1U<<0); //PORT A
	RCC->AHB1ENR |= (1U<<2); //PORT C

	/* 2. Set PA5 as output */
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	/* 3. Set PC13 as input*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	return 1;
}
