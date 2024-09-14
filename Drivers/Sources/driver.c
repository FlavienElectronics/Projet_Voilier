#include "stm32f10x.h"
#include "driver.h"

/*
Initialisation du TIMER de reference
*/
void TIMER_Init(){
    RCC->APB2ENR |= (0x01 << 2) | (0x01 << 4);
}

/*
Assigne un pointeur au GPIO correspondant :
Retourne -1 si le port n'existe pas, sion 0 si le processus a ete effectue avec succes.
*/
int GPIO_Assignment(GPIO_TypeDef ** GPIO, int port){
    switch (port){
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
            return (-1);}
    return (0);
}

/*
Configure le mode du GPIO :
Retourne -1 si le port n'existe pas, sion 0 si le processus a ete effectue avec succes.
*/
int GPIO_SetPinConfig(GPIO_TypeDef *GPIO, int pin, int mode, int configuration)
{
    int mask = ~0;
    int config_value = configuration << 2 | mode;           // [CNF : MODE]

    if (pin < 0 || pin > 15)
        return (-1);

    if (pin > 7)
    {
        mask = (int)(~0) & (int)(~(0xF << 4 * (pin - 8)));
        GPIO->CRH &= (uint32_t)mask;
        config_value <<= ((int)(pin - 8) * 4);              // Shifting to the correct position
        GPIO->CRH |= (uint32_t)config_value;
    }
    else
    {
        mask = (int)(~0) & (int)(~(0xF << 4 * pin));
        GPIO->CRL &= (uint32_t)mask;
        config_value <<= (pin * 4);                         // Shifting to the correct position
        GPIO->CRL |= (uint32_t)config_value;
    }

    return (0);
}

/*
Mise a jour du GPIO en SET (1)
*/
void GPIO_SetPin(GPIO_TypeDef *GPIO, int pin)
{
    GPIO->BSRR = 0x01 << pin;
}

/*
Mise a jour du GPIO en RESET (0)
*/
void GPIO_ResetPin(GPIO_TypeDef *GPIO, int pin)
{
    GPIO->BRR = 0x01 << pin;
}

/*
Lecture de l'etat du GPIO :
Retourne le bit en question (1 ou 0)
*/
int GPIO_ReadPin(GPIO_TypeDef *GPIO, int pin)
{
    return ((GPIO->IDR >> pin) & 0x01);
}
