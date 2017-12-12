/*
 * usart_helpers.c
 *
 * Created: 11/4/2017 12:26:45 PM
 *  Author: Teodor
 */

#include <usart/usart_helpers.h>

void usart_init(USART_t *usart) {
	is_listening = 0;
	_receive_buffer_tail = 0;
	_receive_buffer_head = 0;
	_buffer_overflow = 0;
}

void usart_listen(USART_t *usart) {
	is_listening = 1;
	_buffer_overflow = 0;
	_receive_buffer_head = _receive_buffer_tail = 0;
	usart_set_rx_interrupt_level(usart, USART_INT_LVL_LO);
}

void usart_stop_listening(USART_t *usart) {
	is_listening = 0;
	usart_set_rx_interrupt_level(usart, USART_INT_LVL_OFF);
}

void usart_send(USART_t *usart, const char * command) {
	while (*command) {
		uint8_t c = (uint8_t) *command;
		usart_putchar(usart, c);
		command++;
	}
}

void usart_recv(USART_t *usart) {
	usart_set_rx_interrupt_level(usart, USART_INT_LVL_OFF);
	uint8_t next = (_receive_buffer_tail + 1) % _SS_MAX_RX_BUFF;
	if (next != _receive_buffer_head)
	{
		// save new data in buffer: tail points to where byte goes
		_receive_buffer[_receive_buffer_tail] = usart_getchar(usart); // save new byte
		_receive_buffer_tail = next;
	}
	else
	{
		_buffer_overflow = 1;
	}
	usart_set_rx_interrupt_level(usart, USART_INT_LVL_LO);
}

uint8_t usart_read(USART_t *usart) {
	if (is_listening == 0) return -1;
	if (_receive_buffer_head == _receive_buffer_tail) return -1;
	uint8_t c = _receive_buffer[_receive_buffer_head]; // grab next byte
	_receive_buffer_head = (_receive_buffer_head + 1) % _SS_MAX_RX_BUFF;
	usart_putchar(USART_DEBUG_SERIAL, c);
	return c;
}

uint8_t usart_available(USART_t *usart) {
	if (is_listening == 0) return -1;
	return (_receive_buffer_tail + _SS_MAX_RX_BUFF - _receive_buffer_head) % _SS_MAX_RX_BUFF;
}

uint8_t check_response(const char * expect) {
	uint8_t resp[_SS_MAX_RX_BUFF];
	uint8_t i = 0;
	while (usart_available(USART_SERIAL) > 0) {
		resp[i] = usart_read(USART_SERIAL);
	}
	
	if (strcmp((char *) (&resp), expect)) {
		return 1;
	}
	
	return 0;
};
