#include "led.h"
#include "main.h"

/* LED integrado LD2 de la NUCLEO-F103RB: PA5, activo en alto. */

void LED_Iniciar(void)
{
    LED_Apagar();
}

void LED_Encender(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}

void LED_Apagar(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}

void LED_Alternar(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

uint8_t LED_EstaEncendido(void)
{
    return (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_SET)
           ? 1U
           : 0U;
}
