/*
 * @file:			Teclado.c
 * @company:		ITESO
 * @Engineer Team:	D.F.R. / R.G.P.
 */

#ifndef TECLADO_H_
#define TECLADO_H_



#include "MK64F12.h"
#include "stdint.h"
#include "GPIO.h"
typedef enum {
	CLAVE_MAESTRA,
	CONTROL_MOTOR,
	GENERADOR_SENAL,
} proceso;
/*	Keyboard:
	 *	 	1  2  3  A
	 *	 	4  5  6  B
	 * 	 	7  8  9  C
	 * 	 	*  0  #  D
*/


/************************************************************************************/
/*!
 	 \brief:	 Leer la salida del encoder 74c922 del teclado matricial

 	 \param[in]  El GPIO D
 	 \return 	 char
 */

int8_t TECLADO_read_KEY(gpio_port_name_t port_name);
/************************************************************************************/

void TECLADO_init(void);
uint8_t compara_pasword(proceso accion);
void write_pasword(void);



#endif /* TECLADO_H_ */
