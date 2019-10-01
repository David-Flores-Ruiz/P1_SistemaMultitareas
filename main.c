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
	RGB_init();
	TECLADO_init();

	uint32_t PTC_4  = 0;	// Data Available
	uint32_t PTD_0  = 0;	//	--- LSB
	uint32_t PTD_1  = 0;	//			---	Bits de "ABCD"
	uint32_t PTD_2  = 0;	//			--- salida del codificador 74c922
	uint32_t PTD_3  = 0;	//  --- MSB
	uint32_t total_input = 0;	// "DCBA" puede tener valores de 0 - 15
	uint32_t tecla_presionada = 0;

	/*
	 * 1 2 3 A
	 * 4 5 6 B
	 * 7 8 9 C
	 * * 0 # D
	 */

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
				encender_LED(RED_ON);
				break;
			case 1:
				tecla_presionada='2';
				break;
			case 2:
				tecla_presionada='3';
				break;
			case 3:
				tecla_presionada='A';
				break;
			case 4:
				tecla_presionada='4';
				break;
			case 5:
				tecla_presionada='5';
				break;
			case 6:
				tecla_presionada='6';
				break;
			case 7:
				tecla_presionada='B';
				break;
			case 8:
				tecla_presionada='7';
				break;
			case 9:
				tecla_presionada='8';
				break;
			case 10:
				tecla_presionada='9';
				break;
			case 11:
				tecla_presionada='C';
				break;
			case 12:
				tecla_presionada='*';
				break;
			case 13:
				tecla_presionada='#';
				break;
			case 14:
				tecla_presionada='D';
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
		}//end if
	}//end while(1)


    return 0 ;
}
