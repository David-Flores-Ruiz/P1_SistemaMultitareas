/*
 * @file:			FSMcontrol.c
 * @company:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "MK64F12.h"
#include "FSMcontrol.h"
#include "motor.h"
#include "generador.h"
#include "bits.h"
#include "Teclado.h"
#include <stdio.h>

static FSM_flags_t g_FSM_status_flags = {0};	// Banderas de activacion de FSM: MOTOR y GENERADOR
int8_t readArray[4] = { '0', '0', '0', '0' };

void FSM_motor() {
	if (g_FSM_status_flags.flag_FSM_MOTOR == TRUE) {
		Motor_secuencia_master();
	}
}

void FSM_generador() {
	if (g_FSM_status_flags.flag_FSM_GENERADOR == TRUE) {
		DAC_FSM_signals();
	}
}

void FSM_control() {
	static State_t current_state = waitCLAVE_MAESTRA; // Estado Inicial del Sistema
	static uint32_t letra = 0;
	boolean_t intento = FALSE;	//** Los intentos inician como fallidos */
	boolean_t intento_A = FALSE;
	boolean_t intento_B = FALSE;
	readArray[letra] = TECLADO_read_KEY(GPIO_D);
	printf("... %c",TECLADO_read_KEY(GPIO_D));
	letra++;

	if(letra == SIZE_CLAVE){
		letra = 0;
	}

	if(letra == SIZE_PROCESS && current_state==waitSELECT_PROCESO){
		letra = 0;
	}

	switch (current_state) {
	case waitCLAVE_MAESTRA:
		intento = TECLADO_comparaClaves(CLAVE_MAESTRA, readArray, SIZE_CLAVE);
		if (intento){
			current_state = waitSELECT_PROCESO;
			printf("\nCLAVE_MAESTRA correcta!");
		}
		break; // end case waitCLAVE_MAESTRA

	case waitSELECT_PROCESO:
		intento_A = TECLADO_comparaClaves(PROCESO_A, readArray, SIZE_PROCESS);
		if (intento_A){
			current_state = waitCLAVE_MOTOR;
			printf("\nSelect_A_motor correcto!");
		}

		intento_B = TECLADO_comparaClaves(PROCESO_B, readArray, SIZE_PROCESS);
		if (intento_B){
			current_state = waitCLAVE_GENERADOR;
			printf("\nSelect_B_generador correcta!");
		}
		break; // end case waitSELECT_PROCESO

	case waitCLAVE_MOTOR:
		intento = TECLADO_comparaClaves(CLAVE_MOTOR, readArray, SIZE_CLAVE);
		if (intento){
			g_FSM_status_flags.imparOn_A = !g_FSM_status_flags.imparOn_A;
			printf("\nClave_4567_motor correcto!");
		}
		if ( (g_FSM_status_flags.imparOn_A == TRUE) && (intento == TRUE) ) {
			current_state = FSM_MOTOR;
			g_FSM_status_flags.flag_FSM_MOTOR = TRUE;								// new from FSM_MOTOR
			current_state = waitSELECT_PROCESO;										// new from FSM_MOTOR
		}
		if ( (g_FSM_status_flags.imparOn_A == FALSE) && ((intento == TRUE)) ) {
			current_state = stop_MOTOR;
		}
		break; // end case waitCLAVE_MOTOR

	case FSM_MOTOR:
		g_FSM_status_flags.flag_FSM_MOTOR = TRUE;	// Activa FSM Motor
		current_state = waitSELECT_PROCESO;
		break;// end case FSM_MOTOR

	case stop_MOTOR:
		g_FSM_status_flags.flag_FSM_MOTOR = FALSE;	// Desactivacion de FSM Motor
		current_state = waitSELECT_PROCESO;
		break;// end case stop_MOTOR

	case waitCLAVE_GENERADOR:
		intento = TECLADO_comparaClaves(CLAVE_GENERADOR, readArray, SIZE_CLAVE);
		if(intento){
			g_FSM_status_flags.imparOn_B = !g_FSM_status_flags.imparOn_B;
			printf("\nClave_7890_generador correcto!");
		}
		if( (g_FSM_status_flags.imparOn_B == TRUE) && (intento == TRUE) ){
			current_state = FSM_GENERADOR;
			g_FSM_status_flags.flag_FSM_GENERADOR = TRUE;							// new from FSM_GENERADOR
			current_state = waitSELECT_PROCESO;										// new from FSM_GENERADOR
		}
		if( (g_FSM_status_flags.imparOn_B == FALSE) && (intento == TRUE) ){
			current_state = stop_GENERADOR;
		}
		break; // end case waitCLAVE_GENERADOR

	case FSM_GENERADOR:
		g_FSM_status_flags.flag_FSM_GENERADOR = TRUE;	// Activa FSM Generador
		current_state = waitSELECT_PROCESO;
		break;// end case FSM_GENERADOR

	case stop_GENERADOR:
		g_FSM_status_flags.flag_FSM_GENERADOR = FALSE;	// Desactivacion de FSM Generador
		current_state = waitSELECT_PROCESO;
		break;// end case stop_MOTOR

	default:
		break;
	} //end switch(current state)
} //end FSM_control
