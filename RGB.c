/*
 * RGB.c
 *
 *  Created on: 10 sep 2019
 *      Author: Ricardo Pacas
 */

#include "MK64F12.h"
#include "RGB.h"
#include <GPIO.h>
#include "bits.h"

#define ASCENDENTE_SW2  (0x02u) // Orden1 de FSM
#define DESCENDENTE_SW3 (0x01u)	// Orden2 de FSM

typedef enum {
	GREEN,		// 0
	BLUE,		// 1
	PURPLE,		// 2
	RED,		// 3
	YELLOW,		// 4
}State_name_t;

void fx (void){
	static State_name_t current_state = GREEN;	// Estado Inicial de la FSM
	static uint32_t arriba_sw2  = 0;	// Secuencia: Verde-Amarillo-Rojo-Morado-Azul...Verde
	static uint32_t abajo_sw3   = 0;	// Secuencia: Verde-Azul-Morado-Rojo-Amarillo...Verde
	static uint32_t total_input = 0;

	for ( ; ; ) {
		arriba_sw2 = GPIO_read_pin(GPIO_C, bit_6);	// lee el sw2
		abajo_sw3   = GPIO_read_pin( GPIO_A, bit_4);	// lee el sw3
		arriba_sw2  = arriba_sw2 >> 6;		// mandar el bit al LSB
		abajo_sw3   = abajo_sw3  >> 3;		// mandar el bit al penúltimo
		total_input = arriba_sw2 | abajo_sw3;

		switch (current_state)
		{
			case GREEN:
				apagar_LED(RGB_OFF);
				encender_LED(GREEN_ON);			// ENCIENDE LED GREEN EN k-64

				switch (total_input)
				{
					case ASCENDENTE_SW2:
						current_state = YELLOW;		// next en secuencia ascendente
						break;
					case DESCENDENTE_SW3:
						current_state = BLUE;		// next en secuencia descendente
						break;
					default:
						current_state = GREEN;		// secuencia INVÁLIDA no cambia el next
					break;
				}
				break;// end case GREEN

			case BLUE:
				apagar_LED(RGB_OFF);
				encender_LED(BLUE_ON);			// ENCIENDE LED BLUE EN k-64

				switch (total_input)
				{
					case ASCENDENTE_SW2:
						current_state = GREEN;		// next en secuencia ascendente
						break;
					case DESCENDENTE_SW3:
						current_state = PURPLE;		// next en secuencia descendente
						break;
					default:
						current_state = BLUE;		// secuencia INVÁLIDA no cambia el next
					break;
				}
				break;// end case BLUE

			case PURPLE:
				apagar_LED(RGB_OFF);
				encender_LED(PURPLE_ON);			// ENCIENDE LED PURPLE EN k-64

				switch (total_input)
				{
					case ASCENDENTE_SW2:
						current_state = BLUE;		// next en secuencia ascendente
						break;
					case DESCENDENTE_SW3:
						current_state = RED;		// next en secuencia descendente
						break;
					default:
						current_state = PURPLE;		// secuencia INVÁLIDA no cambia el next
					break;
				}
				break;// end case PURPLE

			case RED:
				apagar_LED(RGB_OFF);
				encender_LED(RED_ON);			// ENCIENDE LED RED EN k-64

				switch (total_input)
				{
					case ASCENDENTE_SW2:
						current_state = PURPLE;		// next en secuencia ascendente
						break;
					case DESCENDENTE_SW3:
						current_state = YELLOW;		// next en secuencia descendente
						break;
					default:
						current_state = RED;		// secuencia INVÁLIDA no cambia el next
					break;
				}
				break;// end case RED

			case YELLOW:
				apagar_LED(RGB_OFF);
				encender_LED(YELLOW_ON);			// ENCIENDE LED YELLOW EN k-64

				switch (total_input)
				{
					case ASCENDENTE_SW2:
						current_state = RED;		// next en secuencia ascendente
						break;
					case DESCENDENTE_SW3:
						current_state = GREEN;		// next en secuencia descendente
						break;
					default:
						current_state = YELLOW;		// secuencia INVÁLIDA no cambia el next
					break;
				}
				break;// end case YELLOW
			default:
				apagar_LED(RGB_OFF);		// DEFAULT...
				current_state = GREEN;		// NOS REGRESA AL ESTADO INICIAL
				break;
		}//end switch(current state)

		break;//para return ISR vector

	}//end for(;;)
}


uint8_t encender_LED(color_ON color_RGB) {
	switch (color_RGB) {
	case RED_ON:
		GPIO_clear_pin(GPIO_B, bit_22);	// ON - 0 RED
		break;
	case GREEN_ON:
		GPIO_clear_pin(GPIO_E, bit_26);	// ON - 0 GREEN
		break;
	case BLUE_ON:
		GPIO_clear_pin(GPIO_B, bit_21);	// ON - 0 BLUE
		break;
	case PURPLE_ON:
		GPIO_clear_pin(GPIO_B, bit_21);	// ON - 0 	BLUE +
		GPIO_clear_pin(GPIO_B, bit_22);	// ON - 0 	RED		= PURPLE
		break;
	case YELLOW_ON:
		GPIO_clear_pin(GPIO_B, bit_22);	// ON - 0 	RED +
		GPIO_clear_pin(GPIO_E, bit_26);	// ON - 0 	GREEN	= YELLOW
		break;
	default: /**If doesn't exist the option*/
		return (FALSE);
	}
	return (TRUE);
}

uint8_t apagar_LED(color_OFF color_RGB) {
	switch (color_RGB) {
	case RED_OFF:
		GPIO_set_pin( GPIO_B, bit_22);	// OFF - 1 RED
		break;
	case GREEN_OFF:
		GPIO_set_pin( GPIO_E, bit_26);	// OFF - 1 GREEN
		break;
	case BLUE_OFF:
		GPIO_set_pin( GPIO_B, bit_21);	// OFF - 1 BLUE
		break;
	case RGB_OFF:
		GPIO_set_pin( GPIO_B, bit_22);	// OFF - 1 RED	  +
		GPIO_set_pin( GPIO_E, bit_26);	// OFF - 1 GREEN  +
		GPIO_set_pin( GPIO_B, bit_21);	// OFF - 1 BLUE		=	RGB is OFF
		break;
	default: /**If doesn't exist the option*/
		return (FALSE);
	}
	return (TRUE);
}
void RGB_init(void){
	/**	Configurar el Clock Gating de los perifericos GPIO a utilizar */
	GPIO_clock_gating( GPIO_B);	// led azul y rojo
	GPIO_clock_gating( GPIO_E);	// led verde
	gpio_pin_control_register_t led_config   = GPIO_MUX1;	// 100 de GPIO
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

		gpio_pin_control_register_t pin_control_register_bit_d_0 = GPIO_MUX1;
		GPIO_clock_gating(GPIO_E);	 						   // Pin 0 del puerto D
		GPIO_pin_control_register(GPIO_E, bit_24, &pin_control_register_bit_d_0);	// GPIO
		GPIO_pin_control_register(GPIO_B, bit_2, &pin_control_register_bit_d_0);
		GPIO_pin_control_register(GPIO_B, bit_3, &pin_control_register_bit_d_0);

		GPIO_data_direction_pin(GPIO_E,GPIO_OUTPUT, bit_24);
		GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT, bit_2);
		GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT, bit_3);

		GPIO_clear_pin( GPIO_E, bit_24);	// OFF -  Motor
		GPIO_clear_pin( GPIO_B, bit_2);	// OFF -  LED 1 externo Color Rojo
		GPIO_clear_pin( GPIO_B, bit_3);	// OFF -  LED 2 externo Color Verde


}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
void sw_init(void){
	GPIO_clock_gating( GPIO_A);	// sw3
	GPIO_clock_gating( GPIO_C);	// sw2
	gpio_pin_control_register_t sw_config  = GPIO_MUX1 |GPIO_PE | GPIO_PS;	// 103
	GPIO_pin_control_register( GPIO_A, bit_4,  &sw_config );  // sw3	  - pin  4
	GPIO_pin_control_register( GPIO_C, bit_6,  &sw_config );  // sw2	  - pin  6

}
void delay(uint16_t delay) {
	volatile uint16_t j, i;

	for (j = delay; j > 0; j--) {
		for (i = 0; i < 1000; ++i) {
			__asm("nop");
		}

	}
}
