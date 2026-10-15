#include "uart_estado.h"
#include <stdio.h>

/* Definido por CubeMX, en main.c o usart.c. */
extern UART_HandleTypeDef huart2;

HAL_StatusTypeDef UART_Reportar(const char *modo, uint8_t led, uint32_t tiempo_ms)
{
    char mensaje[112];
    int longitud = snprintf(mensaje, sizeof(mensaje),
        "t=%lu ms | modo=%s | LED=%s\r\n",
        (unsigned long)tiempo_ms, modo, led ? "ON" : "OFF");

    if (longitud < 0 || (unsigned int)longitud >= sizeof(mensaje)) {
        return HAL_ERROR;
    }

    return HAL_UART_Transmit(&huart2, (uint8_t *)mensaje,
                             (uint16_t)longitud, 100);
