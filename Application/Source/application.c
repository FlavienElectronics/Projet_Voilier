#include "driver.h"
#include "application.h"

/*
Initialise le pin du GPIO
*/
int GPIO_PIN_Init(int port, int pin, int mode, int config)
{
    GPIO_TypeDef *GPIO = 0;
    if (GPIO_Assignment(&GPIO, port) == -1)
        return (-1);

    return GPIO_SetPinConfig(GPIO, pin, mode, config);
}

/*
Mise a jour du GPIO en SET (1)
*/
int GPIO_PIN_Set(int port, int pin)
{
    GPIO_TypeDef *GPIO = 0;
    if (GPIO_Assignment(&GPIO, port) == -1)
        return (-1);
    
    GPIO_SetPin(GPIO, pin);
    return 0;
}

/*
Mise a jour du GPIO en RESET (0)
*/
int GPIO_PIN_Reset(int port, int pin)
{
    GPIO_TypeDef *GPIO = 0;
    if (GPIO_Assignment(&GPIO, port) == -1)
        return (-1);
    
    GPIO_ResetPin(GPIO, pin);
    return 0;
}

/*
Lecture de l'etat du GPIO
*/
int GPIO_PIN_Read(int port, int pin)
{
    GPIO_TypeDef *GPIO = 0;
    if (GPIO_Assignment(&GPIO, port) == -1)
        return (-1);

    return GPIO_ReadPin(GPIO, pin);
}
