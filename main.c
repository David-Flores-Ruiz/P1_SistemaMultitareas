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
	uint8_t state_port_C = 0;
	uint8_t state_port_A = 0;
	RGB_init();
	sw_init();
	PIT_init(PIT_0);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PIT_CH2_IRQ, PRIORITY_10);

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
		/*NVIC_set_basepri_threshold(PRIORITY_10);*/
		/**Enables and sets a particular interrupt and its priority*/
		NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_5);
		/**Enables and sets a particular interrupt and its priority*/
		NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_4);
		NVIC_global_enable_interrupts;

	while (1) {
		if(GPIO_get_irq_status(GPIO_C)==TRUE){
			GPIO_clear_pin(GPIO_B, bit_2);//Rojo
			GPIO_clear_pin(GPIO_B, bit_3);//verde
			GPIO_set_pin(GPIO_B, bit_2);//Rojo
			GPIO_clear_pin(GPIO_B, bit_3);//verde
			Secuencia1();
				}

		/*uint8_t Sw3 = 0;
		    	Sw3=GPIO_get_irq_status(GPIO_C);
		    	if(TRUE == GPIO_get_irq_status(GPIO_C))
		    	{
					if(state_port_C)
					{
						GPIOB->PDOR |= 0x00200000;/**Blue led off
					}
					else
					{
						GPIOB->PDOR &= ~(0x00200000);/**Blue led on
					}
					state_port_C = !state_port_C;
					GPIO_clear_irq_status(GPIO_C);
		    	}


			if(TRUE == GPIO_get_irq_status(GPIO_A))
			{
				if(state_port_A)
				{
					GPIOB->PDOR |= 0x00400000;/**Read led off
				}
				else
				{
					GPIOB->PDOR &= ~(0x00400000);/**Read led on
				}
				state_port_A = !state_port_A;
				GPIO_clear_irq_status(GPIO_A);
			}*/


	/*	uint8_t Sw2 = 0;
		uint8_t contador_sw = 0,total_input = 0;
	static	State_motor_n current_state = 0;
		if(GPIO_get_irq_status(GPIO_C)==TRUE){
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

