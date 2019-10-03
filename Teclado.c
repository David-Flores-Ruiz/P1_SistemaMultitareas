/*
 * @file:			Teclado.c
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include <Teclado.h>
#include "MK64F12.h"
#include "GPIO.h"
#include "RGB.h"
#include "bits.h"

typedef enum {
	UNO,	DOS,	TRES,	 A,
	CUATRO,	CINCO,	SEIS, 	 B,
	SIETE,	OCHO, 	NUEVE,	 C,
	STAR,	CERO,	CAT,	 D,
} Key_name_t;


int8_t TECLADO_read_KEY(gpio_port_name_t port_name)
{
	uint32_t PTD_0 = 0;	//	--- LSB
	uint32_t PTD_1 = 0;	//			---	Bits de "ABCD"
	uint32_t PTD_2 = 0;	//			--- salida del codificador 74c922
	uint32_t PTD_3 = 0;	//  --- MSB
	uint32_t total_input = 0;	// "DCBA" puede tener valores de 0 - 15
	int8_t tecla_presionada = 0;// Valor de 0 - 15 según la tecla
	PTD_0 = GPIO_read_pin(port_name, bit_0);	//	"A"
	PTD_1 = GPIO_read_pin(port_name, bit_1); 	//	"B"
	PTD_2 = GPIO_read_pin(port_name, bit_2); 	//	"C"
	PTD_3 = GPIO_read_pin(port_name, bit_3); 	//	"D"

	total_input = PTD_0 | PTD_1 | PTD_2 | PTD_3; 	// "DCBA"

	switch (total_input)
	{
		case UNO:
			tecla_presionada = '1';
			break;
		case DOS:
			tecla_presionada = '2';
			break;
		case TRES:
			tecla_presionada = '3';
			break;
		case A:
			tecla_presionada = 'A';
			break;
		case CUATRO:
			tecla_presionada = '4';
			break;
		case CINCO:
			tecla_presionada = '5';
			break;
		case SEIS:
			tecla_presionada = '6';
			break;
		case B:
			tecla_presionada = 'B';
			break;
		case SIETE:
			tecla_presionada = '7';
			break;
		case OCHO:
			tecla_presionada = '8';
			break;
		case NUEVE:
			tecla_presionada = '9';
			break;
		case C:
			tecla_presionada = 'C';
			break;
		case STAR:
			tecla_presionada = '*';
			break;
		case CERO:
			tecla_presionada = '0';
			break;
		case CAT:
			tecla_presionada = '#';
			break;
		case D:
			tecla_presionada = 'D';
			break;
		default:
			encender_LED(RED_ON);
			delay(2000);
			encender_LED(BLUE_ON);	// ON - LED WHITE
			delay(2000);
			encender_LED(GREEN_ON);
			delay(2000);
			apagar_LED(RGB_OFF);	// OFF
			break;
		}//end switch (total_input)
	return(tecla_presionada);
}




