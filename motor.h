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

typedef struct
{
	uint32_t out;
//void GPIO_set_pin(gpio_port_name_t port_name, uint8_t pin)
	void(*fptrPort)( gpio_port_name_t , bit_t dato );//set and clear
	uint32_t wait;
//PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock,My_float_pit_t delay)
	uint32_t system;
	uint32_t PIT_N;
	void (*fptrDelay)(PIT_timer_t ,My_float_pit_t ,My_float_pit_t);//pit delay
	uint8_t next[2];
}State;


void Secuencia1(void);
void Secuencia2(void);
void Secuencia3(void);


#endif /* MOTOR_H_ */
