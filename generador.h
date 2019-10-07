/*
 * @file:			generador.h
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#ifndef GENERADOR_H_
#define GENERADOR_H_

#include <stdint.h>
#include "bits.h"

#define MAX 100 //** Completa la onda */

void DAC_FSM_signals(void);

void DAC_plot(uint16_t elemento);

#endif /* GENERADOR_H_ */
