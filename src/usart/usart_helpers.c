/*
 * usart_helpers.c
 *
 * Created: 11/4/2017 12:26:45 PM
 *  Author: Teodor
 */

#include <asf.h>
#include <usart/usart_helpers.h>
#include <buffer/buffer.h>

void usart_send(USART_t *usart, buffer_t *buffer) {
	uint8_t i = 0;
	while (i < buffer->size) {
		unsigned char c = (unsigned char) buffer_get_one(buffer, i);
		usart_putchar(usart, c);
		i++;
	}
}

buffer_t usart_receive(USART_t *usart) {
	buffer_t response;
	buffer_init(&response);
	while (true) {
		unsigned char c = (unsigned char) usart_getchar(usart);
		if (c == '\0') break;
		buffer_append(&response, c);
	}
	
	return response;
}
