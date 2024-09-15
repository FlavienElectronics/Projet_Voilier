#include "stm32f10x.h"			// Pour la gestion de la carte STM32
#include "application.h"		// Contient les fonctions de haut niveau
#include "driver.h"					// Contient les macros des ports et pins

int main(void)
{
    TIMER_Init();
	
	//Ton commentaire est nul est inutile
	

    // Initialisation de la pin GPIO de la LED (Output push-pull)
    GPIO_PIN_Init(PORT_A, PIN_5, OUTPUT_10MHZ, GENERAL_PURPOSE_OUTPUT_PUSH_PULL);

    // Initialisation du bouton sur le GPIO PC13 (Floating input)
    GPIO_PIN_Init(PORT_C, PIN_13, INPUT, FLOATING_INPUT);

    while (1)
    {
        // Verification de la pression sur le bouton (logique inverse)
        if (GPIO_PIN_Read(PORT_C, PIN_13) == 0)
        {
            // Allumage de la LED
            GPIO_PIN_Set(PORT_A, PIN_5);
        }
        else
        {
            // Extinction de la LED
            GPIO_PIN_Reset(PORT_A, PIN_5);
        }
    }
}
