/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <stdio.h>
#include <port_map.h>
#include <usart/usart_driver.h>
#include <string.h>

char buf[128];

int main (void)
{	
	// Initialize board
	board_init();
	sysclk_init();
			
	// Enable IO service
	ioport_init();
	
	// Set TEST_LEDT1 as output
	ioport_set_pin_dir(TEST_LED1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(TEST_LED2, IOPORT_DIR_OUTPUT);
	
	// Enable GPS on MC 60
	ioport_set_pin_dir(GSM_POWER_EN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(GSM_POWER_KEY, IOPORT_DIR_OUTPUT);
	
	// Enable power and turn on MC 60
	ioport_set_value(GSM_POWER_EN, true);
	ioport_set_value(GSM_POWER_KEY, true);
		
	// Set USART pin direction
	ioport_set_pin_dir(C_RXD0, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(C_TXD0, IOPORT_DIR_OUTPUT);

#ifdef DEBUG
	// Set debugger pin dir
	ioport_set_pin_dir(E_RXD0, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(E_TXD0, IOPORT_DIR_OUTPUT);
#endif // DEBUG
	
#ifdef DEBUG
	// Debugger options
	static usart_rs232_options_t USART_SERIAL_DEBUG_OPTIONS = {
		.baudrate = USART_DEBUG_SERIAL_BAUDRATE,
		.charlength = USART_DEBUG_SERIAL_CHAR_LENGTH,
		.paritytype = USART_DEBUG_SERIAL_PARITY,
		.stopbits = USART_DEBUG_SERIAL_STOP_BIT
	};
#endif // DEBUG
	
#ifdef DEBUG
	usart_init_rs232(USART_DEBUG_SERIAL, &USART_SERIAL_DEBUG_OPTIONS);
#endif // DEBUG

	FILE *mc60_tty = tty_init();
	
	// Setup interrupt services
	pmic_init();
	cpu_irq_enable();

	while (true) {
		fprintf(mc60_tty, "%s", "AT\r");
		if(fgets(buf, sizeof buf - 1, mc60_tty) == NULL) {
			break;
		}
		if (strstr(buf, "OK") != NULL) {
			break;
		}
	}
	
	ioport_set_value(TEST_LED1, true);
	
	fprintf(stdout, "AT+CPIN?\r");
	
	while(true) {}
}