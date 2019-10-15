/*
 * motor.c
 *
 *  Created on: 4 oct 2019
 *      Author: pacas
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "bits.h"
#include "motor.h"
#include "RGB.h"
#include "PIT.h"

const State FSM_Moore[4] =
{
	//led azul  funcion escribir  valor delay   estados sig/act
	{ bit_24, GPIO_set_pin,   DELAY_1, SYSTEM_CLOCK, PIT_0, PIT_delayInteger, { SEC_motor2, SEC_motor1 } }, // 660 1s encendido
	{ bit_24, GPIO_clear_pin, DELAY_1, SYSTEM_CLOCK, PIT_0, PIT_delayInteger, { SEC_motor3, SEC_motor2 } }, // 660 1s apagado
	{ bit_24, GPIO_set_pin,   DELAY_3, SYSTEM_CLOCK, PIT_0, PIT_delayInteger, { SEC_motor4, SEC_motor3 } }, // 1980 3s encendido
	{ bit_24, GPIO_clear_pin, DELAY_1, SYSTEM_CLOCK, PIT_0, PIT_delayInteger, { SEC_motor1, SEC_motor4 } }  // 1980 3s encendido
};

const State FSM_Moore2[2]=
{
	{bit_24 , GPIO_set_pin, DELAY_4,SYSTEM_CLOCK,PIT_0, PIT_delayInteger, {SEC_motor2, SEC_motor1}}, //660 1s encendido
	{bit_24 , GPIO_clear_pin, DELAY_4,SYSTEM_CLOCK,PIT_0, PIT_delayInteger, {SEC_motor1, SEC_motor2}}, //660 1s encendido
};
const State_master FSM_Moore_motor[3]=
{
	{Secuencia1,bit_2,bit_3,GPIO_set_pin,GPIO_clear_pin,{SEC2,SEC1}},
	{Secuencia2,bit_2,bit_3,GPIO_clear_pin,GPIO_set_pin,{SEC3,SEC2}},
	{Secuencia3,bit_2,bit_3,GPIO_clear_pin,GPIO_clear_pin,{SEC1,SEC3}},
};

void Secuencia1(void){
	static uint8_t current_state = SEC_motor1;
	uint32_t output = 0;
	uint32_t SYS_CLOCK = 0;
	uint8_t estado = FALSE;
	uint16_t delay_value = 0;
	uint32_t PIT_Ch = 0;

	output = FSM_Moore[current_state].out;
	FSM_Moore[current_state].fptrPort(GPIO_E, output); //enciende motor
	delay_value = FSM_Moore[current_state].wait; //extrae valor de delay
	SYS_CLOCK = FSM_Moore[current_state].system;
	PIT_Ch = FSM_Moore[current_state].PIT_N;
	FSM_Moore[current_state].fptrDelay(PIT_Ch, SYS_CLOCK, delay_value); //espra 1 seg
	estado = PIT_get_irq_flag_status(PIT_Ch);
	if (estado)
	{
		current_state = FSM_Moore[current_state].next[CERO_N];
		//PIT_clear_irq_flag_status(PIT_Ch);
		PIT_clear_irq_flag_status(PIT_Ch);	// Limpiamos bandera de Software
		PIT_stop(PIT_0);
	}
}

void Secuencia2(void)
{
	static uint8_t current_state = SEC_motor1;
	uint32_t output = 0;
	uint32_t SYS_CLOCK = 0;
	uint8_t estado = FALSE;
	uint16_t delay_value = 0;
	uint32_t PIT_Ch = 0;
	output = FSM_Moore2[current_state].out;
	FSM_Moore2[current_state].fptrPort(GPIO_E, output);	//enciende motor
	delay_value = FSM_Moore2[current_state].wait;	//extrae valor de delay
	SYS_CLOCK = FSM_Moore2[current_state].system;
	PIT_Ch = FSM_Moore2[current_state].PIT_N;
	FSM_Moore2[current_state].fptrDelay(PIT_Ch, SYS_CLOCK, delay_value);//espra 1 seg
	estado = PIT_get_irq_flag_status(PIT_Ch);
	if (estado)
	{
		current_state = FSM_Moore2[current_state].next[CERO_N];
		PIT_clear_irq_flag_status(PIT_Ch);
	}
}
void Secuencia3(void)
{
	GPIO_clear_pin(GPIO_E,bit_24);
}
void Motor_secuencia_master(void)
{
	static uint8_t current_state = SEC3;
	uint8_t output_PTB2 = 0;
	uint8_t output_PTB3 = 0;
	uint32_t status = 0;

	FSM_Moore_motor[current_state].fptrSecuancia();
	output_PTB2 = FSM_Moore_motor[current_state].BIT_LED_AZUL;
	output_PTB3 = FSM_Moore_motor[current_state].BIT_LED_NARANJA;
	FSM_Moore_motor[current_state].fptrSET(GPIO_B, output_PTB2);
	FSM_Moore_motor[current_state].fptrCLEAR(GPIO_B, output_PTB3);
	status = GPIO_get_irq_status(GPIO_C);

	if (status)
	{
		current_state = FSM_Moore_motor[current_state].next[CERO_N];	//en vez de cero puede ser sw;
		GPIO_clear_irq_status(GPIO_C);
	}
}
