/*
 * teclado.h
 *
 *  Created on: 1 oct 2019
 *      Author: pacas
 */

#ifndef TECLADO_H_
#define TECLADO_H_
#include "MK64F12.h"
#include "stdint.h"
#include "GPIO.h"

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


#endif /* TECLADO_H_ */
