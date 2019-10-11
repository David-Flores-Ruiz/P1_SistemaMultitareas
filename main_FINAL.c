/*
 * @file:			P1_DAC.c
 * @comany:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */


#include "MK64F12.h"
#include "GPIO.h"
#include "NVIC.h"
#include "PIT.h"
#include "RGB.h"
#include "Teclado.h"
#include "FSMcontrol.h"
#include "bits.h"
#include "motor.h"
#include "generador.h"


int main(void) {
	RGB_init();
	SW_init();
	TECLADO_init();
	PIT_init();
	DAC0_clock_gating( );
	DAC0_config( );

	/** Callbacks for GPIO */
	GPIO_callback_init(GPIO_B, Teclado_set_irq_flagSW);	//** flag teclado */


	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	//NVIC_set_basepri_threshold(PRIORITY_10);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_10);	// sw2
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_10);	// sw3
	NVIC_enable_interrupt_and_priotity(PORTB_IRQ,PRIORITY_10);	// teclado
	NVIC_global_enable_interrupts;

	uint8_t state_keyPress = 0;

    while(1) {
		state_keyPress = Teclado_get_irq_status_flagSW();
		if (state_keyPress) {
			FSM_control();
			Teclado_clear_irq_flagSW();	// Se apaga bandera de Software
		}

		FSM_motor();

		FSM_generador();

	}	//end while(1)


    return 0 ;
}
