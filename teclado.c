/*
 * @file:			Teclado.c
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "MK64F12.h"
#include "GPIO.h"
#include "RGB.h"
#include <stdio.h>	// Hay que quitarla después!
#include "Teclado.h"
#include "bits.h"

typedef enum {
	UNO,	DOS,	TRES,	 A,
	CUATRO,	CINCO,	SEIS, 	 B,
	SIETE,	OCHO, 	NUEVE,	 C,
	STAR,	CERO,	CAT,	 D,
} Key_name_t;

static int8_t array_claveMAESTRA[4] = { '1', '2', '3', '4' };
static int8_t array_processA[1] = {'A'};
static int8_t array_proccesB[1] = {'B'};
static int8_t array_clave_MOTOR[4]   = { '4', '5', '6', '7' };
static int8_t array_clave_WAVEGEN[4] = { '7', '8', '9', '0' };

static uint8_t g_flag_press_teclado = FALSE;

void Teclado_set_irq_flagSW(void)
{
	g_flag_press_teclado = TRUE;	//** Prende bandera de interrupcion por Software */
}

void Teclado_clear_irq_flagSW(void)
{
	g_flag_press_teclado = FALSE;	//** Apaga bandera de interrupcion por Software  */
}

uint8_t Teclado_get_irq_status_flagSW(void)
{
	uint8_t status = 0;
	status = g_flag_press_teclado;
	return (status);
}

boolean_t TECLADO_comparaClaves(Password_t contrasena, int8_t arrayTeclado[], uint8_t word_width)
{
	uint32_t letra = 0;
	uint32_t letter_success = 0;

	switch (contrasena)
	{
		case CLAVE_MAESTRA:
			for (letra = 0; letra < word_width; letra++) {
				if (array_claveMAESTRA[letra] == arrayTeclado[letra]) {
					letter_success++;
				}
			}

			if (letter_success == word_width) {
				return (TRUE);	// Contrasena Clave Maestra es correcta!
			}
			else {
				return (FALSE);
			}

			break;	// end case CLAVE_MAESTRA

	case PROCESO_A:
		for (letra = 0; letra <= word_width; letra++) {
			if (array_processA[letra] == arrayTeclado[letra]) {
				letter_success++;
			}
		}

		if (letter_success == word_width) {
			return (TRUE);	// Seleccion de Proceso A es correcto!
		}
		else {
			return (FALSE);
		}

		break;	// end case PROCESO_A

	case PROCESO_B:
		for (letra = 0; letra <= word_width; letra++) {
			if (array_proccesB[letra] == arrayTeclado[letra]) {
				letter_success++;
			}
		}

		if (letter_success == word_width) {
			return (TRUE);	// Seleccion de Proceso B es correcto!
		}
		else {
			return (FALSE);
		}

		break;	// end case PROCESO_B

	case CLAVE_MOTOR:
		for (letra = 0; letra <= word_width; letra++) {
			if (array_clave_MOTOR[letra] == arrayTeclado[letra]) {
				letter_success++;
			}
		}

		if (letter_success == word_width) {
			return (TRUE);	// Contrasena Clave Motor es correcta!
		}
		else {
			return (FALSE);
		}

		break;	// end case CLAVE_MOTOR

	case CLAVE_GENERADOR:
		for (letra = 0; letra <= word_width; letra++) {
			if (array_clave_WAVEGEN[letra] == arrayTeclado[letra]) {
				letter_success++;
			}
		}

		if (letter_success == word_width) {
			return (TRUE);	// Contrasena Clave Generador es correcta!
		}
		else {
			return (FALSE);
		}

		break;	// end case CLAVE_GENERADOR
	}	//end case
}

void TECLADO_init()
{
	/**	Configurar el Clock Gating de los perifericos GPIO a utilizar */
	GPIO_clock_gating( GPIO_D);	// Leer teclado Matricial
	GPIO_clock_gating( GPIO_C); // Interrupción DataAvailable (Keyboard)
	/********************************************************************/
	gpio_pin_control_register_t input_config = GPIO_MUX1;		// 100 de GPIO
	gpio_pin_control_register_t pinINT_config = GPIO_MUX1 | INTR_RISING_EDGE;	// Teclado

	/********************************************************************************************/
		/** INPUT: Configurar como GPIO + como entrada */
		GPIO_pin_control_register( GPIO_D, bit_0,  &input_config );  // PTD	  - pin  0  = GPIO
		GPIO_pin_control_register( GPIO_D, bit_1,  &input_config );  // PTD	  - pin  1  = GPIO
		GPIO_pin_control_register( GPIO_D, bit_2,  &input_config );  // PTD	  - pin  2  = GPIO
		GPIO_pin_control_register( GPIO_D, bit_3,  &input_config );  // PTD	  - pin  3  = GPIO
		GPIO_pin_control_register( GPIO_B, bit_20, &pinINT_config ); // Activa con Posedge

		GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_0);			// input para "A" LSB
		GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_1);			// input para "B"
		GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_2);			// input para "C"
		GPIO_data_direction_pin(GPIO_D,GPIO_INPUT, bit_3);			// input para "D" MSB
		GPIO_data_direction_pin(GPIO_B,GPIO_INPUT, bit_20);			// input para DataAvailable (Interrupcion)
	/********************************************************************************************/
}


int8_t TECLADO_read_KEY(gpio_port_name_t port_name)
{
	uint32_t PTD_0 = 0;	//	--- LSB
	uint32_t PTD_1 = 0;	//			---	Bits de "ABCD"
	uint32_t PTD_2 = 0;	//			--- salida del codificador 74c922
	uint32_t PTD_3 = 0;	//  --- MSB
	uint32_t total_input = 0;	// "DCBA" puede tener valores de 0 - 15
	int8_t tecla_presionada = NADA;// Valor de 0 - 15 según la tecla

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

