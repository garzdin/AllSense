/*
 * usart_helpers.c
 *
 * Created: 11/4/2017 12:26:45 PM
 *  Author: Teodor
 */

#include <usart/usart_helpers.h>

uint8_t usart_init(USART_t *usart) {
	return (fifo_init(&fifo_desc_rx, fifo_buffer_rx, FIFO_BUFFER_LEGNTH) == FIFO_OK) ? 1 : 0;
}

void usart_send(USART_t *usart, const char *command) {
	while (*command) {
		uint8_t c = (uint8_t) *command;
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			usart_putchar(usart, c);
			//while(!usart_tx_is_complete(usart));
			//usart_clear_tx_complete(usart);
		}
		command++;
	}
}

void usart_recv(USART_t *usart) {
	if (usart_rx_is_complete(usart)) {
		uint8_t c = usart_getchar(usart);
		if (fifo_push_uint8(&fifo_desc_rx, c) == FIFO_OK) {
			#ifdef ENVIRONMENT
			#if ENVIRONMENT == DEVELOPMENT
			usart_putchar(USART_DEBUG_SERIAL, c);
			while(!usart_tx_is_complete(USART_DEBUG_SERIAL));
			usart_clear_tx_complete(USART_DEBUG_SERIAL);
			#endif
			#endif // ENVIRONMENT
		}
		usart_clear_rx_complete(usart);
	}
}

uint8_t check_response(const char * expect) {
	uint8_t * response[FIFO_BUFFER_LEGNTH];
	uint8_t c = 0, i = 0, cr_first = 0, nl_first = 0, cr_second = 0, nl_second = 0;
	
	int status = FIFO_OK;
	
	do {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			status = fifo_pull_uint8(&fifo_desc_rx, &c);
		}
		if (c == CR && cr_first != 1) cr_first = 1;
		if (c == NL && nl_first != 1) nl_first = 1;
		if (c == CR && cr_first == 1 && cr_second != 1) cr_second = 1;
		if (c == NL && nl_first == 1 && nl_second != 1) nl_second = 1;
		if (cr_first == 1 && nl_first == 1 && cr_second == 1 && nl_second == 1) break;
		*response[i] = c;
	} while(status == FIFO_OK);
	
	if (strstr((char *) response, expect)) {
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
			fifo_flush(&fifo_desc_rx);
		}
		return 1;
	}
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		fifo_flush(&fifo_desc_rx);
	}
	return 0;
};
