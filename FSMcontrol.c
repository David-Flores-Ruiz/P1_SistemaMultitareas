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
#include "PIT.h"

static FSM_flags_t g_FSM_status_flags = {0};	// Banderas de activacion de FSM: MOTOR y GENERADOR
int8_t readArray[4] = { '0', '0', '0', '0' };

void FSM_motor() {
	if (g_FSM_status_flags.flag_FSM_MOTOR == TRUE) {
		Motor_secuencia_master();
	}
	if(g_FSM_status_flags.flag_FSM_MOTOR == FALSE) {
		//Se detiene el motor
	}
}

void FSM_generador() {
	if (g_FSM_status_flags.flag_FSM_GENERADOR == TRUE) {
		DAC_FSM_signals();
	}
	if(g_FSM_status_flags.flag_FSM_GENERADOR == FALSE) {
		// Se detiene la señal
	}
}

void Wait_1_second() {
	uint8_t estado = FALSE;
	PIT_delay(PIT_1, SYSTEM_CLOCK, Delay_Password);	// Corre el PIT

	// FUNCIONA BIEN EN DEBUG
	do {
		estado = PIT_get_irq_flag_status(PIT_1);
	} while (estado == FALSE);

	PIT_clear_irq_flag_status(PIT_1);	// Limpiamos bandera de Software
	PIT_stop(PIT_1);					// Paramos el PIT


/*	// FUNCIONA BIEN EN DEBUG PERO NO CORRIENDO TODO EL TIEMPO "F8 sin breakpoints"

	PIT_delay(PIT_0, SYSTEM_CLOCK, Delay_Password);
	estado = PIT_get_irq_flag_status(PIT_0);

	if (estado) {

		GPIO_clear_pin(GPIO_B, bit_18);
		PIT_clear_irq_flag_status(PIT_0);	// Limpiamos bandera de Software
		PIT_stop(PIT_0);

	}
*/

}

void FSM_control() {
	static State_t current_state = waitCLAVE_MAESTRA; // Estado Inicial del Sistema
	static uint32_t letra = 0;
	uint32_t letra_minus1 = 0;
	boolean_t intento = FALSE;	//** Los intentos inician como fallidos */
	boolean_t intento_A = FALSE;
	boolean_t intento_B = FALSE;
	readArray[letra] = TECLADO_read_KEY(GPIO_D);
	printf("... %c", readArray[letra]);
	letra_minus1 = letra;
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
		if (intento) {
			current_state = waitSELECT_PROCESO;
			printf("\nCLAVE_MAESTRA correcta!");
			GPIO_set_pin(GPIO_B, bit_18); 			/** Power On: GREEN LED */
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
		if (intento == TRUE) {
			g_FSM_status_flags.imparOn_A = !g_FSM_status_flags.imparOn_A;
			printf("\nClave_4567_motor correcto!");

			readArray[0] = 0;
			readArray[1] = 0;
			readArray[2] = 0;
			readArray[3] = 0;

			GPIO_clear_pin(GPIO_B, bit_18);			//** Apaga led verde 	*/	// 1 vez
			//Wait_1_second();							//** Wait 1 seg */
			GPIO_set_pin(GPIO_B, bit_18);			//** Enciende led verde */
			//Wait_1_second();							//** Wait 1 seg */
			GPIO_clear_pin(GPIO_B, bit_18);			//** Apaga led verde	*/	// 2 vez
			//Wait_1_second();							//** Wait 1 seg */
			GPIO_set_pin(GPIO_B, bit_18);			//** Enciende led verde */
		}

		if ( (intento == FALSE) && (letra_minus1 == SIZE_CLAVE-1) ) {
			GPIO_set_pin(GPIO_B, bit_19);			//** Enciende led rojo */ // 1 vez
			//Wait_1_second();							//** Wait 1 seg */
			GPIO_clear_pin(GPIO_B, bit_19);			//** Apaga led rojo    */
			//Wait_1_second();							//** Wait 1 seg */
			GPIO_set_pin(GPIO_B, bit_19);			//** Enciende led rojo */ // 2 vez
			//Wait_1_second();							//** Wait 1 seg  */
			GPIO_clear_pin(GPIO_B, bit_19);			//** Apaga led rojo	   */
		}

		if ( (g_FSM_status_flags.imparOn_A == TRUE) && (intento == TRUE) ) {
			current_state = FSM_MOTOR;
			g_FSM_status_flags.flag_FSM_MOTOR = TRUE;								// new from FSM_MOTOR
			current_state = waitSELECT_PROCESO;										// new from FSM_MOTOR
		}
		if ( (g_FSM_status_flags.imparOn_A == FALSE) && ((intento == TRUE)) ) {
			g_FSM_status_flags.flag_FSM_MOTOR = FALSE;
			current_state = waitSELECT_PROCESO;
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

			readArray[0] = 0;
			readArray[1] = 0;
			readArray[2] = 0;
			readArray[3] = 0;

			GPIO_clear_pin(GPIO_B, bit_18);			//** Apaga led verde 	*/	// 1 vez
			//Wait_1_second();							//** Wait 1 seg */
			GPIO_set_pin(GPIO_B, bit_18);			//** Enciende led verde */
			//Wait_1_second();							//** Wait 1 seg */
			GPIO_clear_pin(GPIO_B, bit_18);			//** Apaga led verde	*/	// 2 vez
			//Wait_1_second();							//** Wait 1 seg */
			GPIO_set_pin(GPIO_B, bit_18);			//** Enciende led verde */
		}

		if ( (intento == FALSE) && (letra_minus1 == SIZE_CLAVE-1) ) {
			GPIO_set_pin(GPIO_B, bit_19);			//** Enciende led rojo */ // 1 vez
			//Wait_1_second();							//** Wait 1 seg */
			GPIO_clear_pin(GPIO_B, bit_19);			//** Apaga led rojo    */
			//Wait_1_second();							//** Wait 1 seg */
			GPIO_set_pin(GPIO_B, bit_19);			//** Enciende led rojo */ // 2 vez
			//Wait_1_second();							//** Wait 1 seg  */
			GPIO_clear_pin(GPIO_B, bit_19);			//** Apaga led rojo	   */
		}

		if( (g_FSM_status_flags.imparOn_B == TRUE) && (intento == TRUE) ){
			current_state = FSM_GENERADOR;
			g_FSM_status_flags.flag_FSM_GENERADOR = TRUE;							// new from FSM_GENERADOR
			current_state = waitSELECT_PROCESO;										// new from FSM_GENERADOR
		}
		if( (g_FSM_status_flags.imparOn_B == FALSE) && (intento == TRUE) ){
			g_FSM_status_flags.flag_FSM_GENERADOR = FALSE;	//STOP GENERADOR
			current_state = waitSELECT_PROCESO;
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
