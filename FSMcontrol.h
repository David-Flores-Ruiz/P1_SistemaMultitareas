/*
 * @file:			FSMcontrol.h
 * @company:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#ifndef FSMCONTROL_H_
#define FSMCONTROL_H_

#include "MK64F12.h"

typedef enum {
	waitCLAVE_MAESTRA,
	waitSELECT_PROCESO,
	waitCLAVE_MOTOR,
	FSM_MOTOR,	 	//** Activa a la FSM de Motor para ejecutar secuencias */
	stop_MOTOR,
	waitCLAVE_GENERADOR,
	FSM_GENERADOR,	//**  Activa a la FSM de Generador para generar ondas  */
	stop_GENERADOR,
} State_t;

typedef enum {
	CLAVE_MAESTRA, PROCESO_A, PROCESO_B, CLAVE_MOTOR, CLAVE_GENERADOR,
} Password_t;

//** Para saltar al código de la máquina de estado */
//** Si es la segunda vez o número par que ingresa contrasena es porque quiere detener el proceso */
typedef struct {
	uint8_t flag_FSM_MOTOR :1;
	uint8_t imparOn_A :1;
	uint8_t flag_FSM_GENERADOR :1;
	uint8_t imparOn_B :1;
} FSM_flags_t;

void FSM_control();	//** Máquina de estados general */

void FSM_motor();

void FSM_generador();

#endif /* FSMCONTROL_H_ */
