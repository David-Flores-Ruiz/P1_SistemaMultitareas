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

int8_t pasword_user[4];
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
uint8_t compara_pasword(proceso accion){
	uint32_t contador = 0;
	uint32_t comprobacion = 0;
	uint8_t pasword_inicializacion[4] = {'1','2','3','4'};
	uint8_t pasword_control_motor[4] = {'4','5','6','7'};
	uint8_t pasword_generador_senal[4] = {'7','8','9','0'};
	switch(accion){
	case CLAVE_MAESTRA:
		for (contador=0;contador<=4;contador++){
			if(pasword_inicializacion[contador]==pasword_user[contador]){
				comprobacion++;
			}
		}
		if(comprobacion==4){
			return(TRUE);
		}else{
			return(FALSE);
		 	 }
		break;
	case CONTROL_MOTOR:

		for (contador=0;contador<=4;contador++){
			if(pasword_control_motor[contador]==pasword_user[contador]){
				comprobacion++;
			}
		}
		if(comprobacion==4){
			return(TRUE);
		}else{
			return(FALSE);
			}
		break;
	case GENERADOR_SENAL:
		for (contador=0;contador<=4;contador++){
			if(pasword_generador_senal[contador]==pasword_user[contador]){
				comprobacion++;
			}
		}
		if(comprobacion==4){
			return(TRUE);
		}else{
			return(FALSE);
			}
		break;
	}//end case
}
void write_pasword(void){
	uint32_t contador = 0;
	uint32_t PTC_4 = 0;	// Data Available
	for(contador=0;contador<=3;contador++){
	PTC_4 = GPIO_read_pin(GPIO_C, bit_4);	//	Data available
	if (PTC_4) {
		pasword_user[contador] = TECLADO_read_KEY(GPIO_D);
		printf("tecla: %c\n", pasword_user[contador]);
		}else{
			contador--;
		}
	};


}




