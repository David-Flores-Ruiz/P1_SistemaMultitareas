/*
 * @file:			P1_Sistema_Multitareas.c
 * @comany:			ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#include "MK64F12.h"
#include "PIT.h"
#include "NVIC.h"
#include "GPIO.h"
#include "Bits.h"
#include "RGB.h"
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



		uint32_t PTC_4  = 0;	// Data Available

			int8_t key_press;

			while (1) {

				PTC_4 = GPIO_read_pin(GPIO_C, bit_4);	//	Data available
				if (PTC_4){
					key_press = TECLADO_read_KEY(GPIO_D);// Leemos el teclado matricial
					printf("tecla: %c\n", key_press);
				}
			}//end while(1)






    return 0 ;
}

