/*
 * @file:			P1_Sistema_Multitareas.c
 * @comany:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "MK64F12.h"
#include <stdio.h>
#include "Teclado.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#include "RGB.h"
#include "Bits.h"

int main(void) {

	/********************************************************************************************/
	/**	Configurar el Clock Gating de los perifericos GPIO a utilizar */
	RGB_init();
	TECLADO_init();

	/** Callbacks for GPIO */
//	GPIO_callback_init(GPIO_A, RGB_red_on_off);
//	GPIO_callback_init(GPIO_B, RGB_blue_on_off);
//  Tercer callback

	/********************************************************************************************/
	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_set_basepri_threshold(PRIORITY_10);
 	/**Enables and sets a particular interrupt and its priority*/	// Setup pin + threshold
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_7);		// Int_SW3
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_7);		// Int_SW2 y Teclado
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_5);	// PIT_Channel0

	NVIC_global_enable_interrupts;
	/********************************************************************************************/


	while (1) {



	}	//end while(1)

	return 0;
}

