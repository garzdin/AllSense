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
		uint8_t c = usart_getchar(usart);
		if (c == '\r' || c == '\n') break;
		buffer_append(&response, c);
	}
	
	return response;
}

bool usart_send_and_expect(USART_t * usart, const char * command, const char * expect) {
	buffer_t command_buf = make_command((uint8_t *) command);
	usart_send(usart, &command_buf);
	buffer_t response = usart_receive(usart);
	#ifdef ENVIRONMENT
		#if ENVIRONMENT == DEVELOPMENT
		usart_send(USART_DEBUG_SERIAL, &response);
		#endif // ENVIRONMENT == DEVELOPMENT
	#endif // ENVIRONMENT
	if (check_response(&response, expect)) {
		buffer_free(&command_buf);
		buffer_free(&response);

		return true;
	}

	buffer_free(&command_buf);
	buffer_free(&response);

	return false;
}
