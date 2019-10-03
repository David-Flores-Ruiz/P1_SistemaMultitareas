/*
 * @file:			Interrupts.c
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "MK64F12.h"
#include "Interrupts.h"
#include "NVIC.h"
#include "GPIO.h"
#include "bits.h"

void INTERRUPTS_init (){	// 	¿Cuáles pines de interrupciones vamos a usar?

	/********************************************************************************************/
	/**Config specific pin for interrupt*/
	gpio_pin_control_register_t pinINT_config = GPIO_MUX1 | INTR_RISING_EDGE;	// Teclado
	GPIO_pin_control_register( GPIO_C, bit_4,  &pinINT_config );	// Activa con Posedge


	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_set_basepri_threshold(PRIORITY_10);
 	/**Enables and sets a particular interrupt and its priority*/	// Setup pin + threshold
//	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_7);		// Int_SW3
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_7);		// Int_SW2 y Teclado
//	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_5);	// PIT_Channel0

	NVIC_global_enable_interrupts;
	/********************************************************************************************/

}
