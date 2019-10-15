/*
 * motor.h
 *
 *  Created on: 4 oct 2019
 *      Author: pacas
 */

#ifndef MOTOR_H_
#define MOTOR_H_

/** Estas definiciones son usadas para los estados en funcion secuencia 1 y secuencia 2 */
#define SEC_motor1  0
/** Estas definiciones son usadas para los estados en funcion secuencia 1 y secuencia 2 */
#define SEC_motor2  1
/** Estas definiciones son usadas para los estados en funcion secuencia 1 y secuencia 2 */
#define SEC_motor3  2
/** Estas definiciones son usadas para los estados en funcion secuencia 1 y secuencia 2 */
#define SEC_motor4  3
/** Esta definicion es el reloj usado por la k64 */
#define SYSTEM_CLOCK (21000000U)
/** Esta definicion es el tiempo que durara, dependiendo el caso encendido o apagado */
#define DELAY_1 (2)
#define DELAY_3 (6)
#define DELAY_4 (8)

/*Estas definiciones son usadas para cambiar de entre secuencias usadas por Motor_secuencia_master  */
typedef enum {
	SEC1 = 0,
	SEC2 = 1,
	SEC3 = 2,
}State_motor_n;
/*!Esta estructura es utilizada para generar las secuencias
  	Bit de salida
  	Funcion GPIO_set_pin o GPIO_clear_pin
  	Tiempo de espera
  	CLK
  	PIT utilizado
  	Funcion PIT_delay
  	estado{siguiente,actual}
 * */
typedef struct{
	uint32_t out;
	void(*fptrPort)( gpio_port_name_t , bit_t ); //set and clear
	uint32_t wait;
	uint32_t system;
	uint32_t PIT_N;
	void (*fptrDelay)(PIT_timer_t , My_float_pit_t , My_float_pit_t); //pit delay
	uint8_t next[2];
}State;

/*!Esta estructura es utilizada para controlar las secuencias y encender los LEDS
  	Secuencia
  	Numero de bit donde se coloco el LED AZUL Bit_2
  	Numero de bit donde se coloco el LED Naranja Bit_2
  	GPIO_set_pin
  	GPIO_clear_pin
  	estado{siguiente,actual}
 * */
typedef struct {
	void (*fptrSecuancia)(void);
	uint32_t BIT_LED_AZUL;
	uint32_t BIT_LED_NARANJA;
	void (*fptrSET)(gpio_port_name_t, bit_t );
	void (*fptrCLEAR)(gpio_port_name_t, bit_t );
	uint8_t next[2];
} State_master;

/*!
 	 \brief	 Esta Funcion Realiza la Secuencia 1:
 	 	 	 1s ON
 	 	 	 1s OFF
 	 	 	 3s ON
 	 	 	 1s OFF
 	 \param[in]  void.
 	 \return void
 */
void Secuencia1(void);
/*!
 	 \brief	 Esta Funcion Realiza la Secuencia 2:
 	 	 	 4s ON
 	 	 	 4s OFF
 	 \param[in]  void.
 	 \return void
 */
void Secuencia2(void);
/*!
 	 \brief	 Esta Funcion Realiza la Secuencia 3:
 	 	 	 OFF
 	 \param[in]  void.
 	 \return void
 */
void Secuencia3(void);
/*!
 	 \brief	 Esta Funcion Realiza el control de las secuencias anteriores al oprimir  sw2 en el siguiente orden:
 	 	 	 Secuencia 1 -LED AZUL =ON LED NARANJA =OFF.
 	 	 	 Secuencia 2 -LED AZUL =OFF LED NARANJA =ON.
 	 	 	 Secuencia 3 -LED AZUL =OFF LED NARANJA =OFF.
 	 \param[in]  void.
 	 \return void
 */
void Motor_secuencia_master(void);


#endif /* MOTOR_H_ */
