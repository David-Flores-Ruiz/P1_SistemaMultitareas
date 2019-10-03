/*
 * @file:			P1_Sistema_Multitareas.c
 * @comany:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "MK64F12.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#include "RGB.h"
#include "Interrupts.h"
#include "WaveGenerator.h"
#include "Motor.h"
#include <stdio.h>	// DEBUG teclado matricial
#include <teclado.h>

#include "Bits.h"



int main(void) {

	/********************************************************************************************/
	/**	Configurar el Clock Gating de los perifericos GPIO a utilizar */
	RGB_init();
	TECLADO_init();
	INTERRUPTS_init();

	/** Callbacks for GPIO */
	GPIO_callback_init(GPIO_A, secuencia_sw3);	// Función motor 	 - SW3
	GPIO_callback_init(GPIO_C, secuencia_sw2);	// Función generador - SW2
	GPIO_callback_init(GPIO_C, press_teclado);	// Se presionó una tecla

	int8_t key_press;

	while (1) {


		key_press = TECLADO_read_KEY(GPIO_D);// Leemos el teclado matricial
		printf("tecla: %c\n", key_press);


	}	//end while(1)

	return 0;
}

