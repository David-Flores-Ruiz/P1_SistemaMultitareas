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
int main(void) {


	gpio_pin_control_register_t led_config = GPIO_MUX1;						// 100 de GPIO
	gpio_pin_control_register_t keyboard_config = GPIO_MUX1;				// 100 de GPIO
	GPIO_clock_gating( GPIO_B);	// led azul y rojo
	GPIO_clock_gating( GPIO_E);	// led verde
	GPIO_clock_gating( GPIO_D);	// Leer teclado Matricial

	GPIO_pin_control_register( GPIO_D, bit_0,  &keyboard_config );  // PTD	  - pin  0 GPIO
	GPIO_pin_control_register( GPIO_D, bit_1,  &keyboard_config );  //
	GPIO_pin_control_register( GPIO_D, bit_2,  &keyboard_config );  //
	GPIO_pin_control_register( GPIO_D, bit_3,  &keyboard_config );  //

	GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_0);							// input
	GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_1);							//
	GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_2);							//
	GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_3);							//


	GPIO_pin_control_register( GPIO_B, bit_21, &led_config);  // ledBlue  - pin 21 GPIO
	GPIO_pin_control_register( GPIO_B, bit_22, &led_config);  // ledRed   - pin 22 GPIO
	GPIO_pin_control_register( GPIO_E, bit_26, &led_config);  // ledGreen - pin 26 GPIO

	GPIO_set_pin( GPIO_B, bit_22);	// OFF - 1 RED
	GPIO_set_pin( GPIO_E, bit_26);	// OFF - 1 GREEN
	GPIO_set_pin( GPIO_B, bit_21);	// OFF - 1 BLUE

	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_22); // OUTPUT - 1 RED
	GPIO_data_direction_pin(GPIO_E, GPIO_OUTPUT, bit_26); // OUTPUT - 1 GREEN
	GPIO_data_direction_pin(GPIO_B, GPIO_OUTPUT, bit_21); // OUTPUT - 1 BLUE

	uint32_t PT0  = 0;	// Secuencia: Verde-Amarillo-Rojo-Morado-Azul...Verde
	uint32_t PT1  = 0;	//
	uint32_t PT2  = 0;	//
	uint32_t PT3  = 0;	//

	uint32_t total_input = 0;

	while (1) {

		PT0 = GPIO_read_pin(GPIO_D, bit_0);
		PT1 = GPIO_read_pin(GPIO_D, bit_1);
		PT2 = GPIO_read_pin(GPIO_D, bit_2);
		PT3 = GPIO_read_pin(GPIO_D, bit_3);

		total_input = PT0 | PT1 | PT2 | PT3;

		switch (total_input)
		{
			case 8:
				encender_LED(RED_ON);		// next en secuencia ascendente
				break;
			case 7:
				encender_LED(BLUE_ON);		// next en secuencia descendente
				break;
			default:
				encender_LED(RED_ON);
				encender_LED(BLUE_ON);// secuencia INVÁLIDA no cambia el next
				encender_LED(GREEN_ON);
				break;
		}




	}








    return 0 ;
}
