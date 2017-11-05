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

#define ENVIRONMENT DEVELOPMENT

#include <asf.h>
#include <string.h>
#include <port_map.h>
#include <usart/usart_helpers.h>
#include <buffer/buffer.h>

volatile buffer_t response_buf;
volatile bool command_ready = false;
volatile bool powered_on = false;

int main (void)
{
	uint8_t init_command[] = "AT\r";
	
	// Initialize response buffer
	buffer_init(&response_buf);
	
	// Initialize board
	board_init();
	sysclk_init();
		
	// Disable interrupts
	if(pmic_level_is_enabled(PMIC_LVL_LOW)) pmic_disable_level(PMIC_LVL_LOW);
	if(pmic_level_is_enabled(PMIC_LVL_MEDIUM)) pmic_disable_level(PMIC_LVL_MEDIUM);
	if(pmic_level_is_enabled(PMIC_LVL_HIGH)) pmic_disable_level(PMIC_LVL_HIGH);
	
	if (cpu_irq_is_enabled()) cpu_irq_disable();
	
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

#ifdef ENVIRONMENT
	#if ENVIRONMENT == DEVELOPMENT
	// Set debugger pin dir
	ioport_set_pin_dir(E_RXD0, IOPORT_DIR_INPUT);
	ioport_set_pin_dir(E_TXD0, IOPORT_DIR_OUTPUT);
	#endif // ENVIRONMENT == DEVELOPMENT
#endif // ENVIRONMENT
	
	// USART options
	static usart_rs232_options_t USART_SERIAL_OPTIONS = {
		.baudrate = USART_SERIAL_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT
	};
	
#ifdef ENVIRONMENT
	#if ENVIRONMENT == DEVELOPMENT
	// Debugger options
	static usart_rs232_options_t USART_SERIAL_DEBUG_OPTIONS = {
		.baudrate = USART_DEBUG_SERIAL_BAUDRATE,
		.charlength = USART_DEBUG_SERIAL_CHAR_LENGTH,
		.paritytype = USART_DEBUG_SERIAL_PARITY,
		.stopbits = USART_DEBUG_SERIAL_STOP_BIT
	};
	#endif // ENVIRONMENT == DEVELOPMENT
#endif // ENVIRONMENT
	
	// Initialize USART
	usart_init_rs232(USART_SERIAL, &USART_SERIAL_OPTIONS);
#ifdef ENVIRONMENT
	#if ENVIRONMENT == DEVELOPMENT
	usart_init_rs232(USART_DEBUG_SERIAL, &USART_SERIAL_DEBUG_OPTIONS);
	#endif // ENVIRONMENT == DEVELOPMENT
#endif // ENVIRONMENT
	usart_set_rx_interrupt_level(USART_SERIAL, USART_INT_LVL_LO);
	usart_set_tx_interrupt_level(USART_SERIAL, USART_INT_LVL_LO);
		
	// Setup interrupt services
	pmic_init();
	cpu_irq_enable();
	
	while (true) {
		if (powered_on == false) {
			usart_send(USART_SERIAL, init_command);
		}
		if (powered_on == true) {
			ioport_set_value(TEST_LED1, true);
		}
	}
}

ISR(USART_TX_Vect) {
	if (powered_on == false) {
		if (command_ready == true) {
			if (strstr((char*)buffer_get(&response_buf), "OK")) {
				powered_on = true;
			}
			command_ready = false;
		}
	}
}

ISR(USART_RX_Vect) {
	uint8_t c = usart_getchar(USART_SERIAL);
	if (c == '\r' || c == '\n') {
		command_ready = true;
	} else {
		buffer_append(&response_buf, c);
	}
	usart_clear_rx_complete(USART_SERIAL);
#ifdef ENVIRONMENT
	#if ENVIRONMENT == DEVELOPMENT
	usart_put(&USARTE0, c);
	if (c == '\r') {
		usart_put(&USARTE0, '\n');
	}
	#endif // ENVIRONMENT == DEVELOPMENT
#endif // ENVIRONMENT
}