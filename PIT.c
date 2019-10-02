/*
 * PIT.c
 *
 *  Created on: 16 sep 2019
 *      Author: Lanix
 */

#include "MK64F12.h"
#include "PIT.h"
#include "Bits.h"

static void (*PIT_0_callback)(void) = 0;	// Inicializamos apuntadores a función
static void (*PIT_1_callback)(void) = 0;
static void (*PIT_2_callback)(void) = 0;
static void (*PIT_3_callback)(void) = 0;

static PIT_interrupt_flags_t g_intrPIT_status_flag = {0};

void PIT_callback_init(PIT_timer_t pit_timer, void (*handler)(void)) {
	if (PIT_0 == pit_timer) {
		PIT_0_callback = handler;
	}
	if (PIT_1 == pit_timer) {
		PIT_1_callback = handler;
	}
	if (PIT_2 == pit_timer) {
		PIT_2_callback = handler;
	}
	if (PIT_3 == pit_timer) {
		PIT_3_callback = handler;
	}
}

void PIT0_IRQHandler(void)			// ESTE ES MI VECTOR DE INTERRUPCIÓN
{
	if (PIT_0_callback) {	// Si ya se inicializó el apuntador a función
		PIT_0_callback( );	// con el Handler del CallBack... LLAMADA A FUNCIÓN: PIT_delay();
	}

	PIT_clear_interrupt(PIT_0);				// Apago interrupción por HW
}


//void PIT0_IRQHandler(void)							// ESTE ES MI VECTOR DE INTERRUPCIÓN
//{
//	g_intrPIT_status_flag.flag_PIT_channel_0 = TRUE;// Enciendo bandera por Software
//	PIT_clear_interrupt(PIT_0);				// Apago interrupción por HW
//}


void PIT_clock_gating(void)
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;	// Set bit 23 - enable module PIT
}

void PIT_enable(void)
{
	PIT->MCR &= ~(0x02);	//PIT_MCR_MDIS_MASK;		// bit 1 - MDIS enable PIT section
}

void FRZ_enable(void)
{
	PIT->MCR |= PIT_MCR_FRZ_MASK;		// bit 0 - FRZ enable Mode Debug
}

void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock,My_float_pit_t delay)
{

	My_float_pit_t clock_PIT;		/*! This variable hold the PIT clock	  	*/
	My_float_pit_t period_PIT;		/*! This variable hold the PIT period	  	*/
	uint32_t cycles_number;			/*! This variable is the cycles to spend	*/

	clock_PIT = system_clock / 2;
	period_PIT = (My_float_pit_t)(1 / clock_PIT);

	cycles_number = (int)(delay / period_PIT);
	PIT->CHANNEL[pit_timer].LDVAL = cycles_number - 1; /** Load of number of cycles */
	PIT->CHANNEL[pit_timer].TCTRL |= PIT_TCTRL_TIE_MASK;// set TIE - enable interrupts Timer
	PIT->CHANNEL[pit_timer].TCTRL |= PIT_TCTRL_TEN_MASK;// set TEN - start Timer
}

uint8_t PIT_get_irq_flag_status(PIT_timer_t pit_timer)	// SOFTWARE FLAG
{
	uint8_t status = 0;

	status = g_intrPIT_status_flag.flag_PIT_channel_0;		// Esta es Software
	return (status);
}

void PIT_clear_irq_flag_status(PIT_timer_t pit_timer)	// SOFTWARE FLAG
{

	g_intrPIT_status_flag.flag_PIT_channel_0 = FALSE;		// Apagamos la bandera de HW

}

void PIT_clear_interrupt(PIT_timer_t pit_timer)	// HARDWARE FLAG
{
	PIT->CHANNEL[pit_timer].TFLG = TRUE;	// Borramos bandera de Hardware
}
