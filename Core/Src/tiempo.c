#include "tiempo.h"

extern TIM_HandleTypeDef htim2;

static volatile uint32_t milisegundos_actuales = 0;

void Tiempo_Iniciar(void)
{
    HAL_TIM_Base_Start_IT(&htim2);
}

uint32_t Tiempo_Millis(void)
{
    return milisegundos_actuales;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        milisegundos_actuales++;
    }
}
