#ifndef LED_H
#define LED_H

#include <stdint.h>

void LED_Iniciar(void);
void LED_Encender(void);
void LED_Apagar(void);
void LED_Alternar(void);
uint8_t LED_EstaEncendido(void);

#endif /* LED_H */
