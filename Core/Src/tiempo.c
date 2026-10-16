#include "tiempo.h"
#include "main.h"

/* Definido por CubeMX, en main.c o tim.c segun su configuracion. */
extern TIM_HandleTypeDef htim2;
static volatile uint32_t milisegundos = 0;

void Tiempo_Iniciar(void)
{
    milisegundos = 0;
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);

    if (HAL_TIM_Base_Start_IT(&htim2) != HAL_OK) {
        Error_Handler();
    }
}

uint32_t Tiempo_Millis(void)
{
    return milisegundos;
}

/* Una sola definicion de este callback en todo el proyecto. */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2) {
        ++milisegundos;
    }
}
