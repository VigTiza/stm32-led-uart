# Control de LED y reporte UART con STM32F103RB

Proyecto académico para la tarjeta **NUCLEO-F103RB**, desarrollado en lenguaje C con STM32 HAL. Su objetivo es controlar un LED mediante una máquina de estados, utilizar TIM2 como base de tiempo y reportar el estado del sistema por UART.

El desarrollo se organiza entre seis integrantes mediante issues, ramas, commits, pull requests, revisiones y merges en GitHub.

**Repositorio:** [VigTiza/stm32-led-uart](https://github.com/VigTiza/stm32-led-uart)

## Estado del proyecto

Proyecto en desarrollo. La base generada con CubeMX y los issues del equipo ya fueron creados. La incorporación de módulos, integración y validación física se registrarán mediante los pull requests y las evidencias correspondientes.

Las tablas de configuración y funcionamiento siguientes describen la implementación prevista. Los resultados reales de ejecución deben registrarse en `docs/PRUEBAS.md`.

## Objetivo

Implementar una aplicación modular que permita:

- Encender y apagar el LED integrado de la tarjeta.
- Hacerlo parpadear a una frecuencia determinada.
- Generar una base de tiempo mediante interrupciones de TIM2.
- Mostrar el modo actual y el estado del LED mediante UART.
- Documentar la participación de cada integrante en el desarrollo y la revisión del código.

## Funcionamiento previsto

El sistema repetirá automáticamente la siguiente secuencia:

| Modo | Duración | Comportamiento |
| --- | --- | --- |
| APAGADO | 2 segundos | LED apagado |
| ENCENDIDO | 2 segundos | LED encendido fijo |
| PARPADEO | 4 segundos | 250 ms encendido y 250 ms apagado |

Un ciclo completo de parpadeo dura 500 ms, equivalente a **2 Hz**. La secuencia de modos se repite aproximadamente cada 8 segundos.

La UART enviará un reporte al iniciar, al cambiar de modo y cada segundo. Ejemplo del formato esperado:

```text
t=0 ms | modo=APAGADO | LED=OFF
t=2000 ms | modo=ENCENDIDO | LED=ON
t=4000 ms | modo=PARPADEO 2Hz | LED=ON
```

Estos mensajes son ejemplos de formato, no resultados medidos. Durante el parpadeo, un reporte cada segundo puede coincidir con la misma fase del LED; su frecuencia se comprueba observando la salida o midiéndola.

## Hardware y herramientas

| Elemento | Uso |
| --- | --- |
| NUCLEO-F103RB, STM32F103RBT6 | Ejecución del firmware |
| LED integrado LD2, PA5 | Salida visual |
| ST-LINK integrado | Programación, depuración y puerto COM virtual |
| Cable USB de datos | Conexión con la computadora |
| STM32CubeMX y STM32CubeF1 | Configuración y generación de la base del proyecto |
| STM32CubeIDE | Compilación y programación de la tarjeta |
| Visual Studio Code y Git | Edición y control de versiones |
| GitHub | Colaboración y evidencias del desarrollo |
| Terminal serial | Visualización de los mensajes UART |

La propuesta utiliza el LED integrado y la conexión UART con el ST-LINK de la Nucleo con sus puentes de fábrica. No requiere un LED externo para demostrar el funcionamiento.

## Configuración de referencia en CubeMX

Verificar que los valores del archivo `Github_Project.ioc` correspondan a esta configuración antes de ejecutar el firmware:

| Parámetro | Configuración prevista |
| --- | --- |
| Depuración | Serial Wire, mediante SWD |
| Fuente del PLL | HSI de 8 MHz dividido entre 2 |
| Multiplicador PLL | ×16 |
| SYSCLK / HCLK | 64 MHz |
| APB1 | Divisor /2; PCLK1 de 32 MHz |
| Reloj de TIM2 | 64 MHz |
| PA5 | GPIO Output Push Pull, sin pull-up/pull-down, nivel inicial bajo |
| TIM2 | Internal Clock, conteo ascendente |
| Prescaler de TIM2 | 6399 |
| Auto-reload de TIM2, ARR | 9 |
| Interrupción | TIM2 global interrupt habilitada en NVIC |
| USART2 | Asynchronous; PA2 TX y PA3 RX |
| Comunicación serial | 115200 baudios, 8 bits, sin paridad, 1 bit de parada |
| Control de flujo | Ninguno |

Con un reloj de TIM2 de 64 MHz:

```text
Frecuencia de interrupción = 64 000 000 / ((6399 + 1) × (9 + 1))
                          = 1000 Hz

Periodo de interrupción = 1 ms
```

El contador de milisegundos de la aplicación se actualiza desde TIM2. SysTick se conserva como base de tiempo de HAL. Si se modifica el reloj de TIM2, deben recalcularse PSC y ARR.

## Organización del código

| Ruta | Responsabilidad |
| --- | --- |
| `Github_Project.ioc` | Configuración de CubeMX |
| `Core/Inc/led.h` y `Core/Src/led.c` | Encender, apagar, alternar y consultar el LED |
| `Core/Inc/tiempo.h` y `Core/Src/tiempo.c` | Iniciar TIM2 y contar milisegundos |
| `Core/Inc/control.h` y `Core/Src/control.c` | Administrar los modos y solicitar reportes |
| `Core/Inc/uart_estado.h` y `Core/Src/uart_estado.c` | Construir y transmitir los mensajes UART |
| `Core/Inc/parpadeo.h` y `Core/Src/parpadeo.c` | Alternar el LED cada 250 ms sin esperas bloqueantes |
| `Core/Src/main.c` | Inicializar periféricos y módulos; ejecutar el ciclo principal |
| `Core/Src/stm32f1xx_it.c` | Manejadores de interrupción generados |
| `Drivers/` | Bibliotecas HAL y CMSIS |
| `docs/PRUEBAS.md` | Registro de las pruebas reales y sus evidencias |
| `docs/TUTORIAL_EQUIPO.md` | Guía de implementación y colaboración, cuando se incorpore |

La tabla incluye los archivos previstos para la versión integrada; algunos pueden estar pendientes de incorporación en `main` mientras se desarrollan sus respectivas ramas.

`main.c` inicializa el hardware y arranca los módulos. El callback de TIM2 únicamente incrementa el contador. La lógica de estados, el parpadeo y los reportes UART se ejecutan desde el ciclo principal. `HAL_TIM_PeriodElapsedCallback` debe tener una sola definición en el proyecto.

## Integrantes y responsabilidades

Completar los nombres y usuarios con los integrantes reales del equipo. Los enlaces a tickets y PR se consultan en GitHub.

| Integrante | Nombre y usuario de GitHub | Aportación | Rama |
| --- | --- | --- | --- |
| 1 | Por completar | Módulo LED | `feature/led` |
| 2 | Por completar | Módulo de tiempo con TIM2 | `feature/tiempo` |
| 3 | Por completar | Control de modos | `feature/control` |
| 4 | Por completar | Reporte UART | `feature/uart` |
| 5 | Por completar | Integración en main y pruebas | `feature/integracion` |
| 6 | Por completar | Módulo de parpadeo | `feature/parpadeo` |

## Compilación y ejecución

1. Clonar el repositorio:

   ```bash
   git clone https://github.com/VigTiza/stm32-led-uart.git
   cd stm32-led-uart
   ```

2. Utilizar la versión integrada de `main` o una rama que incluya las dependencias necesarias.
3. Abrir el proyecto en STM32CubeIDE. Si hace falta, importarlo mediante **File > Import > General > Existing Projects into Workspace**, seleccionando la raíz del repositorio.
4. Comprobar que los módulos `.c` estén incluidos en la compilación y que sus cabeceras estén en `Core/Inc`. Actualizar el explorador con **Refresh** si se añadieron archivos fuera del IDE.
5. Ejecutar **Build Project** y resolver los errores antes de programar.
6. Conectar el USB al ST-LINK de la Nucleo.
7. Programar y ejecutar mediante **Run As > STM32 C/C++ Application**, o usar Debug y después Resume.
8. Identificar el **STLink Virtual COM Port** en la computadora.
9. Abrir ese puerto en la terminal serial con **115200, 8N1 y sin control de flujo**.
10. Pulsar RESET con la terminal abierta y observar al menos dos secuencias completas.

Si se regenera el proyecto desde CubeMX, conservar las zonas `USER CODE` y revisar los cambios antes de hacer commit.

## Flujo de colaboración

Cada integrante trabaja desde su propia cuenta de GitHub y sigue este proceso:

1. Crear y asignarse un issue con su funcionalidad y criterios de aceptación.
2. Crear su rama de trabajo a partir de una base actualizada.
3. Incorporar sus archivos y verificar el código.
4. Hacer commits con mensajes que describan cambios reales y publicar la rama.
5. Abrir un pull request hacia `main` y vincular el issue correspondiente.
6. Solicitar una revisión formal a otro integrante.
7. Atender las observaciones y registrar las comprobaciones realizadas.
8. Integrar mediante merge después de la revisión.

Orden recomendado de integración: **LED → tiempo → UART → parpadeo → control → integración en main**. Las ramas pendientes deben recibir los cambios de `main` para disponer de sus dependencias.

Para conservar los commits individuales en el historial de `main`, utilizar un merge commit cuando esa opción esté habilitada.

## Pruebas y evidencias

Las pruebas físicas permanecen pendientes hasta que se documenten sus resultados reales.

| Prueba | Resultado esperado | Registro |
| --- | --- | --- |
| Inicio | LED apagado y reporte APAGADO | `docs/PRUEBAS.md` |
| Encendido fijo | LED encendido durante aproximadamente 2 s | `docs/PRUEBAS.md` |
| Parpadeo | Un ciclo completo cada aproximadamente 500 ms | `docs/PRUEBAS.md` |
| UART | Mensajes legibles y coherentes con el modo | `docs/PRUEBAS.md` |
| Repetición | Retorno al modo apagado y nueva secuencia | `docs/PRUEBAS.md` |
| Reproducibilidad | Otro integrante compila y ejecuta la revisión integrada | `docs/PRUEBAS.md` |

Registrar la fecha, el responsable, el commit probado, el resultado observado y la evidencia correspondiente. Las pruebas simuladas del código de referencia no sustituyen la compilación ARM del proyecto ni la comprobación física.

El reloj interno tiene tolerancia y la transmisión UART bloqueante introduce un retardo breve. Si no se mide con un instrumento, reportar la frecuencia del LED como aproximada.

### Evidencia de GitHub

- [Issues y responsables](https://github.com/VigTiza/stm32-led-uart/issues).
- Ramas de trabajo de los integrantes, disponibles desde el selector del repositorio.
- [Commits de main](https://github.com/VigTiza/stm32-led-uart/commits/main).
- [Pull requests y revisiones](https://github.com/VigTiza/stm32-led-uart/pulls), incluidos los PR cerrados e integrados.
- Merges y vínculos entre issues y pull requests.

Para mostrar el historial desde la terminal:

```bash
git fetch --all
git log --graph --oneline --decorate --all
git log origin/main --format="%h | %an | %ad | %s" --date=short
```

La entrega debe permitir identificar la aportación de cada integrante y demostrar el sistema funcionando en la tarjeta.
