/*
 * usart_driver.c
 *
 * Created: 11/4/2017 12:26:45 PM
 *  Author: Teodor
 */

#include <usart/usart_driver.h>
#include <util/atomic.h>

// the tty i/o stream
FILE tty = FDEV_SETUP_STREAM(tty_put, tty_get, _FDEV_SETUP_RW);

/*
 * initialize the tty subsystem
 */
FILE *tty_init(void)
{
	usart_rs232_options_t tty_cfg = {
		.baudrate = TTY_BAUDRATE,
		.charlength = TTY_CHAR_LENGTH,
		.paritytype = TTY_PARITY,
		.stopbits = TTY_STOP_BIT
	};
	
	// initialize FIFOs
	fifo_init(&tty_rx_fifo, tty_rx_buffer, TTY_RX_FIFO_SIZE);
	fifo_init(&tty_tx_fifo, tty_tx_buffer, TTY_TX_FIFO_SIZE);

	// configure the USART and enable Rx interrupt
	usart_init_rs232(TTY_USART, &tty_cfg);
	usart_set_rx_interrupt_level(TTY_USART, TTY_INTERRUPT_LEVEL);
	usart_set_dre_interrupt_level(TTY_USART, USART_INT_LVL_OFF);

	// connect standard i/o streams to tty
	return &tty;
}

/*
 * stdio compatible get
 */
int tty_get(FILE *f)
{
	int c;
	
	// block while RX FIFO is empty
	while (fifo_is_empty(&tty_rx_fifo));

	// atomically pop char from FIFO
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		c = fifo_pull_uint8_nocheck(&tty_rx_fifo);
	}
			
	// gets() and friends look for newlines, not returns
	if (c == '\r') c = '\n';
	
	return c;
}


/*
 * stdio compatible put
 */
int tty_put(char c, FILE *f)
{
	// block while TX FIFO is full
	while (fifo_is_full(&tty_tx_fifo));

	// atomically push char to FIFO, enable DRE interrupt
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		fifo_push_uint8_nocheck(&tty_tx_fifo, c);
	}
	
	// turn on DRE interrupt to trigger sending of data
	usart_set_dre_interrupt_level(TTY_USART, TTY_INTERRUPT_LEVEL);

	return 0;
}

/*
 *
 */
ISR(TTY_DRE_vect)
{
	if (!fifo_is_empty(&tty_tx_fifo)) {
		usart_put(TTY_USART, fifo_pull_uint8_nocheck(&tty_tx_fifo));
	}
	else {
		usart_set_dre_interrupt_level(TTY_USART, USART_INT_LVL_OFF);
	}
}

/*
 *
 */
ISR(TTY_RXC_vect)
{
	char c;
	
	if (!fifo_is_full(&tty_rx_fifo)) {
		c = usart_get(TTY_USART);
		fifo_push_uint8_nocheck(&tty_rx_fifo, c);
		#ifdef DEBUG
			usart_putchar(USART_DEBUG_SERIAL, (uint8_t) c);
			usart_clear_tx_complete(USART_DEBUG_SERIAL);
		#endif
	}
	else {
		// Rx buffer overrun has occurred
	}
}
