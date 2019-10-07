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
#include "motor.h"
typedef enum {
	SEC1 = 0,
	SEC2 = 1,
	SEC3 = 2,
}State_motor_n;
/*
 * LED Externo #1 Color Rojo  PTB_2
 * LED Externo #2 Color Verde PTB_3
 *
 * Motor PTE_24
 */
int main(void) {
	/********************************************************************************************/
	/**	Configurar el Clock Gating de los perifericos GPIO a utilizar */
	uint8_t state_port_C = 0;
	uint8_t state_port_A = 0;
	RGB_init();
	sw_init();
	PIT_init(PIT_0);
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PIT_CH2_IRQ, PRIORITY_10);

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
		/*NVIC_set_basepri_threshold(PRIORITY_10);*/
		/**Enables and sets a particular interrupt and its priority*/
		NVIC_enable_interrupt_and_priotity(PORTC_IRQ,PRIORITY_4);
		/**Enables and sets a particular interrupt and its priority*/
		//NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_5);
		NVIC_global_enable_interrupts;
		typedef struct
		{

			void(*fptrSecuancia)(void);//out

			//uint32_t gpio;
			//void (*fptrget_status)(gpio_port_name_t  );//pit delay
			uint8_t next[2];
		}State_master;
		const State_master FSM_Moore_motor[3]=
				{
						{Secuencia1,{SEC2,SEC1}},
						{Secuencia2,{SEC3,SEC2}},
						{Secuencia3,{SEC1,SEC3}},
				};
	while (1) {
		static uint8_t  current_state = SEC3;

				uint32_t status = 0;
			FSM_Moore_motor[current_state].fptrSecuancia();
			status=GPIO_get_irq_status(GPIO_C);
			if(status){
			current_state = FSM_Moore_motor[current_state].next[0];//en vez de cero puede ser sw;
			GPIO_clear_irq_status(GPIO_C);
			}

		/*static uint8_t status = 0;

		status=GPIO_get_irq_status(GPIO_C);

		GPIO_clear_irq_status(GPIO_C);*/
		/*switch (contador) {
			case STATE_MOTOR_1:
				GPIO_clear_pin(GPIO_B, bit_2);//Rojo
				GPIO_clear_pin(GPIO_B, bit_3);//verde
				GPIO_set_pin(GPIO_B, bit_2);//Rojo
				GPIO_clear_pin(GPIO_B, bit_3);//verde
				Secuencia1();
				PIT_clear_irq_flag_status(GPIO_C);
				break;
			case STATE_MOTOR_2:
				GPIO_clear_pin(GPIO_B, bit_2);//Rojo
				GPIO_clear_pin(GPIO_B, bit_3);//verde
				GPIO_clear_pin(GPIO_B, bit_2);//verde
				GPIO_set_pin(GPIO_B, bit_3);//Rojo
				Secuencia2();
				PIT_clear_irq_flag_status(GPIO_C);
				break;
			case STATE_MOTOR_3:
				GPIO_clear_pin(GPIO_B, bit_2);//Rojo
				GPIO_clear_pin(GPIO_B, bit_3);//verde
				Secuencia3();
				PIT_clear_irq_flag_status(GPIO_C);
				break;
		}*/






			}	//end while(1)

	return 0;
}

