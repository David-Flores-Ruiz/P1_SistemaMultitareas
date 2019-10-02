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
	TECLADO_init();
	/*
	 * 1 2 3 A
	 * 4 5 6 B
	 * 7 8 9 C
	 * * 0 # D
	 */
	uint32_t PTC_4 = 0;	// Data Available
	uint32_t pasword_correcto_o_falso = 0;
	while (1) {
		write_pasword();//Se llena un arreglo de 4 digitos pasword_user VARIABLE GLOBAL?
		pasword_correcto_o_falso=compara_pasword(GENERADOR_SENAL);//Retorna un 1 en caso de contraseña correcta

		if(pasword_correcto_o_falso==1){
			encender_LED(GREEN_ON);
		}else{
			encender_LED(RED_ON);
		}
	}	//end while(1)

	return 0;
}

