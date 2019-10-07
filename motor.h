/*
 * motor.h
 *
 *  Created on: 4 oct 2019
 *      Author: pacas
 */

#ifndef MOTOR_H_
#define MOTOR_H_


#define SEC_motor1  0
#define SEC_motor2  1
#define SEC_motor3  2
#define SEC_motor4  3
#define SYSTEM_CLOCK (21000000U)
#define DELAY_1 (2)
#define DELAY_3 (6)
#define DELAY_4 (8)


typedef enum {
	SEC1 = 0,
	SEC2 = 1,
	SEC3 = 2,
}State_motor_n;

typedef struct{
	uint32_t out;
	void(*fptrPort)( gpio_port_name_t , bit_t );//set and clear
	uint32_t wait;
	uint32_t system;
	uint32_t PIT_N;
	void (*fptrDelay)(PIT_timer_t ,My_float_pit_t ,My_float_pit_t);//pit delay
	uint8_t next[2];
}State;

typedef struct {
	void (*fptrSecuancia)(void); //out
	uint32_t BIT_LED_AZUL;
	uint32_t BIT_LED_NARANJA;
	void (*fptrSET)(gpio_port_name_t, bit_t ); //set
	void (*fptrCLEAR)(gpio_port_name_t, bit_t ); //set

	//void (*fptrget_status)(gpio_port_name_t  );//pit delay
	uint8_t next[2];
} State_master;

//void Motor_set_irq_flagSW (void);
void Secuencia1(void);
void Secuencia2(void);
void Secuencia3(void);
void Motor_secuencia_master(void);


#endif /* MOTOR_H_ */
