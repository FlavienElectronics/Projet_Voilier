#include "stm32f10x.h"
#include <stdint.h>

#define PORT_A 0x0A
#define PORT_B 0x0B
#define PORT_C 0x0C
#define PORT_D 0x0D
#define PORT_E 0x0E

#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_14 14
#define PIN_15 15

// Mode GPIO
#define INPUT 0x00
#define OUTPUT_10MHZ 0x01
#define OUTPUT_2MHZ 0x02
#define OUTPUT_50MHZ 0x03

// Configuration INPUT GPIO 
#define ANALOG_MODE 0x00
#define FLOATING_INPUT 0x01
#define INPUT_PULL_UP_PULL_DOWN 0x02

// Configuration OUTPUT GPIO 
#define GENERAL_PURPOSE_OUTPUT_PUSH_PULL 0x00
#define GENERAL_PURPOSE_OUTPUT_OPEN_DRAIN 0x01
#define ALTERNATE_FUNCTION_OUTPUT_PUSH_PULL 0x02
#define ALTERNATE_FUNCTION_OUTPUT_OPEN_DRAIN 0x03

/*
Assign a GPIO pointer to it corresponding port
Return -1 if the port doesn't exist 
Return 0 if the process worked
*/
int GPIO_port_Assignment(GPIO_TypeDef ** GPIO,int port)
{
	switch (port)
	{
		case PORT_A:
			*GPIO = GPIOA;
			break;
		case PORT_B:
			*GPIO = GPIOB;
			break;
		case PORT_C:
			*GPIO = GPIOC;
			break;
		case PORT_D:
			*GPIO = GPIOD;
			break;
		case PORT_E:
			*GPIO = GPIOE;
			break;
		default: 
			return (-1);
	}
	return (0);
}

/*
Setup a pin on a port to a desired configuration
Return -1 if the port or the pin doesn't exist
Return 0 if the process worked
Configuration = CNF
*/
int GPIO_PIN_Setup(int port,int pin,int mode, int configuration)
{
	GPIO_TypeDef * GPIO = 0;
	GPIO_port_Assignment(&GPIO,port);
	
	int mask =(~0);
	int config_value =  configuration << 2 | mode; 	// [CNF : MODE] CNF == 2 bits / MODE == 2 bits
	
	if (pin < 0 || pin > 15) 												// Impossible
		return (-1);
	if (pin > 7) 																		// CRL = [0-7] / CRH = [8-15]
	{
		mask = (int)(~0) & (int)(~(0xF << 4*(pin-8)));
		GPIO->CRH &= (uint32_t) mask;
		int DEBUG = ((pin-8)*4);
		config_value <<= ((int)(pin-8)*4); 								// Shifting to the good position
		GPIO->CRH |= (uint32_t) config_value;
	}
	else
	{
		mask = (int)(~0) & (int)(~(0xF << 4*pin));
		GPIO->CRL &= (uint32_t) mask;
		config_value <<= (pin*4); 										// Shifting to the good position
		GPIO->CRL |= (uint32_t) config_value;
	}
	return (0);
}

/*
Return 1 if the bit on the port is on logical high level or 0 if it is on logical low level
Return -1 if the port doesn't exist 
*/
int GPIO_PIN_Read(int port,int pin)
{
	GPIO_TypeDef * GPIO = 0;
	if (GPIO_port_Assignment(&GPIO,port))
		return (-1);
	return ((GPIO->IDR >> pin) & 0x01);							// ODR = Output Data Register
}

/*
Set one bit on a port on logical high level
Return -1 if the port doesn't exist 
*/
int GPIO_PIN_Set(int port,int pin)
{
	GPIO_TypeDef * GPIO = 0;
	if (GPIO_port_Assignment(&GPIO,port))
		return (-1);
	GPIO->BSRR = 0x01 << pin;
	return (0);
}

/*
Set one bit on a port on logical low level
Return -1 if the port doesn't exist 
*/
int GPIO_PIN_Reset(int port,int pin)
{
	GPIO_TypeDef * GPIO = 0;
	if (GPIO_port_Assignment(&GPIO,port))
		return (-1);
	GPIO->BRR = 0x01 << pin;
	return (0);
}

int main ( void )
{
	// Je suis dans ma branche
	// Je vais merge dans le main
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ; // Clock starting (Output Enable)
	
	GPIOA->CRL &= (uint32_t)~(0xF<<4) ;
	GPIOA->CRL |= (0x2<<4) ;
	
	//Led = PA5			 -> Output push-pull
	//Button = PC13	 -> Floating input
	GPIO_PIN_Setup(PORT_A,PIN_5,OUTPUT_10MHZ,GENERAL_PURPOSE_OUTPUT_PUSH_PULL);	// LED
	GPIO_PIN_Setup(PORT_C,PIN_13,INPUT,FLOATING_INPUT); 												// Button
	
	while (1)
	{
		if (GPIO_PIN_Read(PORT_C,PIN_13)==0) 	// Button pressed
			GPIO_PIN_Set(PORT_A,PIN_5);					// LED ON
		else
			GPIO_PIN_Reset(PORT_A,PIN_5);				// LED OFF
	}
}
