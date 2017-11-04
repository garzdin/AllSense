/*
 * usart_helpers.c
 *
 * Created: 11/4/2017 12:26:45 PM
 *  Author: Teodor
 */

#include <asf.h>
#include <usart_helpers.h>

void usart_send(USART_t *usart, unsigned char *data) {
	while (*data) {
		usart_putchar(usart, (unsigned char) *data);
		data++;
	}
}

void usart_receive(USART_t *usart, unsigned char *output, unsigned char size) {
	uint8_t i = 0;
	while (i < size - 1) {
		unsigned char c = (unsigned char) usart_getchar(usart);
		//while(!usart_rx_is_complete(usart));
		usart_clear_rx_complete(usart);
		if (c == '\0') break;
		output[i++] = c;
	}
}
