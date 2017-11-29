/*
 * usart_helpers.c
 *
 * Created: 11/4/2017 12:26:45 PM
 *  Author: Teodor
 */

#include <usart/usart_helpers.h>

void usart_send(USART_t *usart, const char * command) {
	while (*command) {
		uint8_t c = (uint8_t) *command;
		usart_putchar(usart, c);
		command++;
	}
}

void handle_rx_interrupt(USART_t * usart) {
	uint8_t c = usart_getchar(usart);
	buffer_return_t push = buffer_push(&rx_buffer, c);
	if (push == BUFFER_ERROR) {
		response_ready = 1;
	}
	#ifdef ENVIRONMENT
		#if ENVIRONMENT == DEVELOPMENT
		usart_putchar(USART_DEBUG_SERIAL, c);
		#endif // ENVIRONMENT == DEVELOPMENT
	#endif // ENVIRONMENT
}

response_code_enum_t check_response(volatile buffer_t * buffer, const char * expect) {
	if (strcmp((char *) buffer->data, expect)) {
		buffer_free(buffer);
		return RESPONSE_OK;
	}
	
	buffer_free(buffer);
	return RESPONSE_FAIL;
};
