/*
 * @file:			Teclado.h
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */
#ifndef TECLADO_H_
#define TECLADO_H_
#include "MK64F12.h"
#include <stdint.h>
#include "GPIO.h"
#include "bits.h"
#include "FSMcontrol.h"

#define SIZE_CLAVE 4
#define SIZE_PROCESS 1

/*	Keyboard:
	 *	 	1  2  3  A
	 *	 	4  5  6  B
	 * 	 	7  8  9  C
	 * 	 	*  0  #  D
*/

#define NADA -1

void Teclado_set_irq_flagSW(void);	//** Se presiono una tecla */

void Teclado_clear_irq_flagSW(void);

uint8_t Teclado_get_irq_status_flagSW(void);

/************************************************************************************/
/*!
 	 \brief:	 Leer la salida del encoder 74c922 del teclado matricial

 	 \param[in]  El GPIO D
 	 \return 	 char
 */
void TECLADO_init();
/************************************************************************************/



/************************************************************************************/
/*!
 	 \brief:	 Leer la salida del encoder 74c922 del teclado matricial

 	 \param[in]  El GPIO D
 	 \return 	 char
 */
int8_t TECLADO_read_KEY(gpio_port_name_t port_name);
/************************************************************************************/


boolean_t TECLADO_comparaClaves(Password_t contrasena, int8_t arrayTeclado[], uint8_t word_width);

#endif /* TECLADO_H_ */
