/*
 * @file:			generador.h
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#ifndef GENERADOR_H_
#define GENERADOR_H_

#include <stdint.h>
#include "bits.h"

#define MAX 100 	//** Completa la onda */
#define Delay_2ms  0.002	 /** Tiempo de muestreo para generar señales a 5Hz */

void DAC0_clock_gating( );

void DAC0_config( );

void Wait_2ms(); //** Generar señales a 5 Hz */

void DAC_FSM_signals(void);

void DAC_plot(uint16_t elemento);

#endif /* GENERADOR_H_ */
