/*
 * motor.c
 *
 *  Created on: 4 oct 2019
 *      Author: pacas
 */
#include "MK64F12.h"
#include <GPIO.h>
#include <bits.h>
#include "motor.h"
#include "RGB.h"
#include "PIT.h"
/*typedef struct
{
	uint32_t out;
//void GPIO_set_pin(gpio_port_name_t port_name, uint8_t pin)
	void(*fptrPort)( gpio_port_name_t , bit_t dato );//set and clear
	uint16_t wait;
//PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock,My_float_pit_t delay)
	uint16_t system;
	void (*fptrDelay)(PIT_timer_t ,My_float_pit_t ,My_float_pit_t);//pit delay
	uint8_t next[4];
}State;*/
const State FSM_Moore[4]=
		{
				//led azul  funcion escribir  valor delay   estados sig/act
				{bit_24 , GPIO_set_pin, DELAY_1,SYSTEM_CLOCK,PIT_0, PIT_delay, {SEC_motor2, SEC_motor1}}, //660 1s encendido
				{bit_24 , GPIO_clear_pin, DELAY_1,SYSTEM_CLOCK,PIT_0, PIT_delay, {SEC_motor3, SEC_motor2}}, // 660 1s apagado
				{bit_24 , GPIO_set_pin, DELAY_3,SYSTEM_CLOCK,PIT_0, PIT_delay, {SEC_motor4, SEC_motor3}}, // 1980 3s encendido
				{bit_24 , GPIO_clear_pin, DELAY_1,SYSTEM_CLOCK,PIT_0, PIT_delay, {SEC_motor1, SEC_motor4}} // 1980 3s encendido
		};
const State FSM_Moore2[2]=
		{
				{bit_24 , GPIO_set_pin, DELAY_4,SYSTEM_CLOCK,PIT_0, PIT_delay, {SEC_motor2, SEC_motor1}}, //660 1s encendido
				{bit_24 , GPIO_clear_pin, DELAY_4,SYSTEM_CLOCK,PIT_0, PIT_delay, {SEC_motor1, SEC_motor2}}, //660 1s encendido
		};



void Secuencia1(void){
	static uint8_t  current_state = SEC_motor1;
			uint32_t output = 0;
			uint32_t SYS_CLOCK = 0;
			uint8_t estado=FALSE;
			uint16_t delay_value = 0;
			uint32_t PIT_Ch = 0;

			output = FSM_Moore[current_state].out;
					FSM_Moore[current_state].fptrPort(GPIO_E,output);//enciende motor
			delay_value = FSM_Moore[current_state].wait;//extrae valor de delay
			SYS_CLOCK = FSM_Moore[current_state].system;
			PIT_Ch = FSM_Moore[current_state].PIT_N;
			FSM_Moore[current_state].fptrDelay(PIT_Ch,SYS_CLOCK,delay_value);//espra 1 seg
			estado=	PIT_get_irq_flag_status(PIT_Ch);
			if(estado){
				current_state = FSM_Moore[current_state].next[0];
				PIT_clear_irq_flag_status(PIT_Ch);	// Limpiamos bandera de Hardware
				PIT_stop(PIT_0);
			}
	}

void Secuencia2(void){
	static uint8_t  current_state = SEC_motor1;
				uint32_t output = 0;
				uint32_t SYS_CLOCK = 0;
				uint8_t estado=FALSE;
				uint16_t delay_value = 0;
				uint32_t PIT_Ch = 0;
				output = FSM_Moore2[current_state].out;
				FSM_Moore2[current_state].fptrPort(GPIO_E,output);//enciende motor
				delay_value = FSM_Moore2[current_state].wait;//extrae valor de delay
				SYS_CLOCK = FSM_Moore2[current_state].system;
				PIT_Ch = FSM_Moore2[current_state].PIT_N;
				FSM_Moore2[current_state].fptrDelay(PIT_Ch,SYS_CLOCK,delay_value);//espra 1 seg
				estado=	PIT_get_irq_flag_status(PIT_Ch);
				if(estado){
					current_state = FSM_Moore2[current_state].next[0];
					PIT_clear_irq_flag_status(PIT_Ch);
				}
}
void Secuencia3(void){
	GPIO_clear_pin(GPIO_D,bit_0);
}
void Estado_master(void){

}




