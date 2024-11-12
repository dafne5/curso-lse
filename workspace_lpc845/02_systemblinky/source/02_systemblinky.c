#include "board.h"

// Pin para el LED azul
#define LED_BLUE	1
#define LED_D1      29

/**
 * @brief Programa principal
 */
int main(void) {

	// Inicializacion
	BOARD_BootClockFRO24M();

    // Estructura de configuracion de salida
    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };

    // Habilito el puerto 1
    GPIO_PortInit(GPIO, 1);

    // Configuro los LEDS como salida
    GPIO_PinInit(GPIO, 1, LED_BLUE, &out_config);
    GPIO_PinInit(GPIO, 0, LED_D1, &out_config);

    // Configuro SysTick para 500 ms
    SysTick_Config(SystemCoreClock * 0.5);


    while(1);
    return 0 ;
}

/**
 * @brief Handler para interrupcion de SysTick
 */
void SysTick_Handler(void) {
	// Variable para contar interrupciones
	static uint16_t i = 0;

	// Incremento contador
	i++;
	// Verifico si el SysTick se disparo 500 veces (medio segundo)
	if(i == 500) {
		// Reinicio el contador
		i = 0;
		// Conmuto el LED
		GPIO_PinWrite(GPIO, 1, LED_BLUE, !GPIO_PinRead(GPIO, 1, LED_BLUE));
	}
}