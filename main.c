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

		//PIT_stop(PIT_0);


			}	//end while(1)

	return 0;
}

