#include "stm32f10x.h"

// GPIO Ports
#define PORT_A 0x0A
#define PORT_B 0x0B
#define PORT_C 0x0C
#define PORT_D 0x0D
#define PORT_E 0x0E

// GPIO Pin
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

// GPIO Pin Modes
#define INPUT 0x00
#define OUTPUT_10MHZ 0x01
#define OUTPUT_2MHZ 0x02
#define OUTPUT_50MHZ 0x03

// GPIO INPUT Configuration
#define ANALOG_MODE 0x00
#define FLOATING_INPUT 0x01
#define INPUT_PULL_UP_PULL_DOWN 0x02

// GPIO OUTPUT Configuration
#define GENERAL_PURPOSE_OUTPUT_PUSH_PULL 0x00
#define GENERAL_PURPOSE_OUTPUT_OPEN_DRAIN 0x01
#define ALTERNATE_FUNCTION_OUTPUT_PUSH_PULL 0x02
#define ALTERNATE_FUNCTION_OUTPUT_OPEN_DRAIN 0x03

// Function declarations
int GPIO_Assignment(GPIO_TypeDef ** GPIO, int port);
int GPIO_SetPinConfig(GPIO_TypeDef *GPIO, int pin, int mode, int configuration);
void GPIO_SetPin(GPIO_TypeDef *GPIO, int pin);
void GPIO_ResetPin(GPIO_TypeDef *GPIO, int pin);
int GPIO_ReadPin(GPIO_TypeDef *GPIO, int pin);
void TIMER_Init(void);
