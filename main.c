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
	GPIO_pin_control_register( GPIO_C, bit_4,  &input_config );   // PTA	  - pin 0  = GPIO

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

	uint32_t PTD_0  = 0;	//	--- LSB
	uint32_t PTD_1  = 0;	//			---	Bits de "ABCD"
	uint32_t PTD_2  = 0;	//			--- salida del codificador 74c922
	uint32_t PTD_3  = 0;	//  --- MSB
	uint32_t total_input = 0;	// "DCBA" puede tener valores de 0 - 15


	while (1) {

/********************************************************************************************/
		/** Leer Keyboard: retorna el valor leído del codificador en un nibble de 4 bits */
		PTC_4 = GPIO_read_pin(GPIO_C, bit_4);	// Leemos el Data Available

		if (PTC_4)
		{
			PTD_0 = GPIO_read_pin(GPIO_D, bit_0);	//
			PTD_1 = GPIO_read_pin(GPIO_D, bit_1); // Tecla codificada
			PTD_2 = GPIO_read_pin(GPIO_D, bit_2); // en 4 bits
			PTD_3 = GPIO_read_pin(GPIO_D, bit_3); //
			total_input = PTD_0 | PTD_1 | PTD_2 | PTD_3;
/********************************************************************************************/
			switch (total_input) {
			case 0:
				encender_LED(RED_ON);		// Led RED
				delay(3000);
				break;
			case 1:
				encender_LED(BLUE_ON);		// Led BLUE
				delay(3000);
				break;
			case 2:
				encender_LED(GREEN_ON);		// Led GREEN
				delay(3000);
				break;

			default:
				encender_LED(RED_ON);
				encender_LED(BLUE_ON);	// Led WHITE
				encender_LED(GREEN_ON);
				delay(3000);
				break;
			}		//end switch (total_input)
			apagar_LED(RGB_OFF);		// Test para debug y ver colores
			PTC_4  = 0;
			PTD_0  = 0;
			PTD_1  = 0;
			PTD_2  = 0;
			PTD_3  = 0;
			total_input = 0;
		}
	}//end while(1)


    return 0 ;
}
