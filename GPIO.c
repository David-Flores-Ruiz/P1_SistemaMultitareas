/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	18/02/2019
	\todo
	    Interrupts are not implemented in this API implementation.
 */
#include "MK64F12.h"
#include <GPIO.h>
#include <bits.h>

/*! This variable reads the full port	  */
uint32_t port_readValue;

/*! This variable reads the specific pin  */
uint8_t pin_readValue;


uint8_t GPIO_clock_gating(gpio_port_name_t port_name)	// f(x) #2		done jlpe! + good perform
{
	switch (port_name)/** Selecting the GPIO for clock enabling*/
	{
	case GPIO_A: /** GPIO A is selected*/
		SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
		break;
	case GPIO_B: /** GPIO B is selected*/
		SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
		break;
	case GPIO_C: /** GPIO C is selected*/
		SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
		break;
	case GPIO_D: /** GPIO D is selected*/
		SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
		break;
	case GPIO_E: /** GPIO E is selected*/
		SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
		break;
	default: /**If doesn't exist the option*/
		return (FALSE);
	}		// end switch
	/**Successful configuration*/
	return (TRUE);
}		// end function

														// f(x) #3		done jlpe! + good perform
uint8_t GPIO_pin_control_register(gpio_port_name_t port_name, uint8_t pin,
		const gpio_pin_control_register_t* pin_control_register) {
	switch (port_name) {
	case GPIO_A:/** GPIO A is selected*/
		PORTA->PCR[pin] = *pin_control_register;
		break;
	case GPIO_B:/** GPIO B is selected*/
		PORTB->PCR[pin] = *pin_control_register;
		break;
	case GPIO_C:/** GPIO C is selected*/
		PORTC->PCR[pin] = *pin_control_register;
		break;
	case GPIO_D:/** GPIO D is selected*/
		PORTD->PCR[pin] = *pin_control_register;
		break;
	case GPIO_E: /** GPIO E is selected*/
		PORTE->PCR[pin] = *pin_control_register;
	default:/**If doesn't exist the option*/
		return (FALSE);
		break;
	}
	/**Successful configuration*/
	return (TRUE);
}


void GPIO_data_direction_port(gpio_port_name_t port_name, gpio_port_direction_t direction)		   // f(x) #4	done!
{
	switch (port_name) {
	case GPIO_A:/** GPIO A is selected*/
		GPIOA->PDDR = (direction == 1) ? 0xFFFFFFFF : GPIO_INPUT;
		break;
	case GPIO_B:/** GPIO B is selected*/
		GPIOB->PDDR = (direction == 1) ? 0xFFFFFFFF : GPIO_INPUT;
		break;
	case GPIO_C:/** GPIO C is selected*/
		GPIOC->PDDR = (direction == 1) ? 0xFFFFFFFF : GPIO_INPUT;
		break;
	case GPIO_D:/** GPIO D is selected*/
		GPIOD->PDDR = (direction == 1) ? 0xFFFFFFFF : GPIO_INPUT;
		break;
	case GPIO_E: /** GPIO E is selected*/
		GPIOE->PDDR = (direction == 1) ? 0xFFFFFFFF : GPIO_INPUT;
		break;
	default:/**If doesn't exist the option*/

		break;
	}
}
void GPIO_data_direction_pin (gpio_port_name_t port_name, gpio_port_direction_t state, uint8_t pin)// f(x) #5	done + good perform!
{
	switch (port_name) {
	case GPIO_A:/** GPIO A is selected*/
		GPIOA->PDDR |= (state == 1) ? (1 << pin) : (0 << pin);
		break;
	case GPIO_B:/** GPIO B is selected*/
		GPIOB->PDDR |= (state == 1) ? (1 << pin) : (0 << pin);
		break;
	case GPIO_C:/** GPIO C is selected*/
		GPIOC->PDDR |= (state == 1) ? (1 << pin) : (0 << pin);
		break;
	case GPIO_D:/** GPIO D is selected*/
		GPIOD->PDDR |= (state == 1) ? (1 << pin) : (0 << pin);
		break;
	case GPIO_E: /** GPIO E is selected*/
		GPIOE->PDDR |= (state == 1) ? (1 << pin) : (0 << pin);
	default:/**If doesn't exist the option*/

		break;
	}
}
void GPIO_write_port(gpio_port_name_t portName, uint32_t data);// f(x) #6
uint32_t GPIO_read_port(gpio_port_name_t port_name)			   //(f(x) #7	done!
{
	switch (port_name) {
	case GPIO_A:/** GPIO A is selected*/
		port_readValue = GPIOA->PDIR;		 // Lee completo el GPIOA
		break;
	case GPIO_B:/** GPIO B is selected*/
		port_readValue = GPIOB->PDIR;		 // Lee completo el GPIOB
		break;
	case GPIO_C:/** GPIO C is selected*/
		port_readValue = GPIOC->PDIR;		 // Lee completo el GPIOC
		break;
	case GPIO_D:/** GPIO D is selected*/
		port_readValue = GPIOD->PDIR;		 // Lee completo el GPIOD
		break;
	case GPIO_E: /** GPIO E is selected*/
		port_readValue = GPIOE->PDIR;		 // Lee completo el GPIOE
	default:/**If doesn't exist the option*/

		break;
	}// end switch
	/**Successful configuration*/
	return (port_readValue);
}// end function
void GPIO_set_pin(gpio_port_name_t port_name, uint8_t pin)	   // f(x) #8	done! + good perform
{
	switch (port_name) {
	case GPIO_A:
		GPIOA->PSOR = (1<<pin);
		break;
	case GPIO_B:/** GPIO B is selected*/
		GPIOB->PSOR = (1<<pin);

		break;
	case GPIO_C:/** GPIO C is selected*/
		GPIOC->PSOR = (1<<pin);
		break;
	case GPIO_D:/** GPIO D is selected*/
		GPIOD->PSOR = (1<<pin);
		break;
	case GPIO_E:/** GPIO E is selected*/
		GPIOE->PSOR = (1<<pin);
	default:/**If doesn't exist the option*/

		break;
	}
}
uint8_t GPIO_read_pin(gpio_port_name_t port_name, uint8_t pin) // f(x) #9	done!
{
	switch (port_name) {
		case GPIO_A:/** GPIO A is selected*/
			pin_readValue = GPIOA->PDIR;		 // Lee solo el pin de interés
			break;
		case GPIO_B:/** GPIO B is selected*/
			pin_readValue = GPIOB->PDIR;		 // Lee solo el pin de interés
			break;
		case GPIO_C:/** GPIO C is selected*/
			pin_readValue = GPIOC->PDIR;		 // Lee solo el pin de interés
			break;
		case GPIO_D:/** GPIO D is selected*/
			pin_readValue = GPIOD->PDIR;		 // Lee solo el pin de interés
			break;
		case GPIO_E: /** GPIO E is selected*/
			pin_readValue = GPIOE->PDIR;		 // Lee solo el pin de interés
			break;
		default:/**If doesn't exist the option*/

			break;
		}// end switch
		/**Successful configuration*/
		return (pin_readValue & (1 << pin));	 // Mask for read the especific pin
}// end fuction
void GPIO_clear_pin(gpio_port_name_t port_name, uint8_t pin)   // f(x) #10	done! + good perform
{
	switch (port_name) {
	case GPIO_A:
		GPIOA->PCOR = (1<<pin);
		break;
	case GPIO_B:/* GPIO B is selected*/
		GPIOB->PCOR = (1<<pin);
		break;
	case GPIO_C:/* GPIO C is selected*/
		GPIOC->PCOR = (1<<pin);
		break;
	case GPIO_D:/* GPIO D is selected*/
		GPIOD->PCOR = (1<<pin);
		break;
	case GPIO_E: /* GPIO E is selected*/
		GPIOE->PCOR = (1<<pin); // ON - GREEN pin26.
	default:/*If doesn't exist the option*/

		break;
	}
}
void GPIO_toogle_pin(gpio_port_name_t port_name, uint8_t pin)  // f(x) #11	done!
{
	switch (port_name) {
	case GPIO_A:
		GPIOA->PTOR = (1 << pin);
		break;
	case GPIO_B:/** GPIO B is selected*/
		GPIOB->PTOR = (1 << pin);

		break;
	case GPIO_C:/** GPIO C is selected*/
		GPIOC->PTOR = (1 << pin);
		break;
	case GPIO_D:/** GPIO D is selected*/
		GPIOD->PTOR = (1 << pin);
		break;
	case GPIO_E:/** GPIO E is selected*/
		GPIOE->PTOR = (1 << pin);
	default:/**If doesn't exist the option*/

		break;
	}

}
