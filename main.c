/*
 * @file:			P1_Sistema_Multitareas.c
 * @comany:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include <Teclado.h>
#include "MK64F12.h"
#include "stdio.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#include "RGB.h"
#include "Bits.h"
typedef enum {
	STATE_MOTOR_1 = 1,
	STATE_MOTOR_2 = 2,
	STATE_MOTOR_3 = 3,
}State_motor_n;
/*
 * LED Externo #1 Color Rojo  PTB_2
 * LED Externo #2 Color Verde PTB_3
 *
 * Motor PTE_24
 */
int main(void) {
	/********************************************************************************************/
	/**	Configurar el Clock Gating de los perifericos GPIO a utilizar */
	RGB_init();
	sw_init();
	PIT_init(PIT_0);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PIT_CH2_IRQ, PRIORITY_10);


	while (1) {
		Secuencia1();
		/*uint8_t Sw2 = 0;
		uint8_t contador_sw = 0,total_input = 0;
	static	State_motor_n current_state = 0;
		Sw2 = GPIO_read_pin(GPIO_C, bit_6);//presionado =0
		if(Sw2==0){
			current_state++;
		}
		switch (current_state) {
			case STATE_MOTOR_1:
				GPIO_clear_pin(GPIO_B, bit_2);//Rojo
				GPIO_clear_pin(GPIO_B, bit_3);//verde
				GPIO_set_pin(GPIO_B, bit_2);//Rojo
				GPIO_clear_pin(GPIO_B, bit_3);//verde
				Secuencia1();
				break;
			case STATE_MOTOR_2:
				GPIO_clear_pin(GPIO_B, bit_2);//Rojo
				GPIO_clear_pin(GPIO_B, bit_3);//verde
				GPIO_clear_pin(GPIO_B, bit_2);//verde
				GPIO_set_pin(GPIO_B, bit_3);//Rojo
				Secuencia2();
				break;
			case STATE_MOTOR_3:
				GPIO_clear_pin(GPIO_B, bit_2);//Rojo
				GPIO_clear_pin(GPIO_B, bit_3);//verde
				Secuencia3();
				break;
		}*/





			}	//end while(1)

	return 0;
}

