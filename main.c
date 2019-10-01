/*
 * @file:			P1_Sistema_Multitareas.c
 * @comany:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "MK64F12.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#include "Bits.h"
#include "RGB.h"
#include "Teclado.h"

int main(void) {

/********************************************************************************************/
	/**	Configurar el Clock Gating de los perifericos GPIO a utilizar */
	GPIO_clock_gating( GPIO_B);	// led azul y rojo
	GPIO_clock_gating( GPIO_E);	// led verde
	GPIO_clock_gating( GPIO_D);	// Leer teclado Matricial
	GPIO_clock_gating( GPIO_C); // Interrupción DataAvailable (Keyboard)
/********************************************************************************************/

	gpio_pin_control_register_t input_config = GPIO_MUX1;						// 100 de GPIO
	gpio_pin_control_register_t led_config   = GPIO_MUX1;						// 100 de GPIO

/********************************************************************************************/
	/** INPUT: Configurar como GPIO + como entrada */
	GPIO_pin_control_register( GPIO_D, bit_0,  &input_config );  // PTD	  - pin  0  = GPIO
	GPIO_pin_control_register( GPIO_D, bit_1,  &input_config );  // PTD	  - pin  1  = GPIO
	GPIO_pin_control_register( GPIO_D, bit_2,  &input_config );  // PTD	  - pin  2  = GPIO
	GPIO_pin_control_register( GPIO_D, bit_3,  &input_config );  // PTD	  - pin  3  = GPIO
	GPIO_pin_control_register( GPIO_C, bit_4,  &input_config );   // PTC	  - pin 4  = GPIO

	GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_0);			// input para "A" LSB
	GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_1);			// input para "B"
	GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_2);			// input para "C"
	GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_3);			// input para "D" MSB
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, bit_4);			 // input para DataAvailable (Interrupcion)
/********************************************************************************************/

/********************************************************************************************/
	/** OUTPUT: Configurar como LED RGB (GPIO) + safe value + como output */
	GPIO_pin_control_register( GPIO_B, bit_21, &led_config);  // ledBlue  - pin 21 GPIO
	GPIO_pin_control_register( GPIO_B, bit_22, &led_config);  // ledRed   - pin 22 GPIO
	GPIO_pin_control_register( GPIO_E, bit_26, &led_config);  // ledGreen - pin 26 GPIO

	GPIO_set_pin( GPIO_B, bit_22);	// OFF - 1 RED
	GPIO_set_pin( GPIO_E, bit_26);	// OFF - 1 GREEN
	GPIO_set_pin( GPIO_B, bit_21);	// OFF - 1 BLUE

	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_22); // OUTPUT - 1 RED
	GPIO_data_direction_pin(GPIO_E, GPIO_OUTPUT, bit_26); // OUTPUT - 1 GREEN
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_21); // OUTPUT - 1 BLUE
/********************************************************************************************/

	uint32_t PTC_4  = 0;	// Data Available

	int8_t key_press;

	while (1) {

		PTC_4 = GPIO_read_pin(GPIO_C, bit_4);	//	Data available
		if (PTC_4){
			key_press = TECLADO_read_KEY(GPIO_D);// Leemos el teclado matricial
			printf("tecla: %c\n", key_press);
		}


	}//end while(1)

    return 0 ;
}
