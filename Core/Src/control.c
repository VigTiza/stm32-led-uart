#include "control.h"
#include "led.h"
#include "tiempo.h"
#include "parpadeo.h"
#include "uart_estado.h"

typedef enum { APAGADO, ENCENDIDO, PARPADEO } Modo;
static Modo modo;
static uint32_t inicio_modo;
static uint32_t ultimo_reporte;

static void Reportar(uint32_t ahora)
{
    const char *nombre = modo == APAGADO ? "APAGADO" :
                         modo == ENCENDIDO ? "ENCENDIDO" : "PARPADEO 2Hz";

    if (UART_Reportar(nombre, LED_EstaEncendido(), ahora) != HAL_OK) {
        Error_Handler();
    }
    ultimo_reporte = ahora;
}

static void CambiarModo(Modo nuevo, uint32_t ahora)
{
    Parpadeo_Detener();
    modo = nuevo;
    inicio_modo = ahora;

    if (modo == APAGADO) {
        LED_Apagar();
    } else if (modo == ENCENDIDO) {
        LED_Encender();
    } else {
        Parpadeo_Iniciar();
    }

    Reportar(ahora);
}

void Control_Iniciar(void)
{
    LED_Iniciar();
    CambiarModo(APAGADO, Tiempo_Millis());
}

void Control_Actualizar(void)
{
    uint32_t ahora = Tiempo_Millis();
    uint32_t duracion = modo == PARPADEO ? 4000U : 2000U;

    if ((uint32_t)(ahora - inicio_modo) >= duracion) {
        Modo siguiente = modo == APAGADO ? ENCENDIDO :
                         modo == ENCENDIDO ? PARPADEO : APAGADO;
        CambiarModo(siguiente, ahora);
    }

    Parpadeo_Actualizar();

    if ((uint32_t)(ahora - ultimo_reporte) >= 1000U) {
        Reportar(ahora);
    }
}
