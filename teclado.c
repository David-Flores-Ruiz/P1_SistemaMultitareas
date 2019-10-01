/*
 * teclado.c
 *
 *  Created on: 1 oct 2019
 *      Author: pacas
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "bits.h"

void TECLADO_init(void){
	/**	Configurar el Clock Gating de los perifericos GPIO a utilizar */
	GPIO_clock_gating( GPIO_D);	// Leer teclado Matricial
	GPIO_clock_gating( GPIO_C); // Interrupción DataAvailable (Keyboard)
	/********************************************************************/
	gpio_pin_control_register_t input_config = GPIO_MUX1;		// 100 de GPIO
	/********************************************************************************************/
		/** INPUT: Configurar como GPIO + como entrada */
		GPIO_pin_control_register( GPIO_D, bit_0,  &input_config );  // PTD	  - pin  0  = GPIO
		GPIO_pin_control_register( GPIO_D, bit_1,  &input_config );  // PTD	  - pin  1  = GPIO
		GPIO_pin_control_register( GPIO_D, bit_2,  &input_config );  // PTD	  - pin  2  = GPIO
		GPIO_pin_control_register( GPIO_D, bit_3,  &input_config );  // PTD	  - pin  3  = GPIO
		GPIO_pin_control_register( GPIO_C, bit_4,  &input_config );   // PTA	  - pin 0  = GPIO

		GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_0);			// input para "A" LSB
		GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_1);			// input para "B"
		GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_2);			// input para "C"
		GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_3);			// input para "D" MSB
		GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, bit_4);			 // input para DataAvailable (Interrupcion)
	/********************************************************************************************/



}

