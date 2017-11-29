/*
 * usart_helpers.h
 *
 * Created: 11/4/2017 12:27:51 PM
 *  Author: Teodor
 */ 

#ifndef USART_HELPERS_H_
#define USART_HELPERS_H_

#include <asf.h>
#include <string.h>
#include <buffer/buffer.h>

#define CR '\r'
#define NL '\n'

#define DEFAULT_RX_BUFFER_SIZE 8

typedef enum {
	RESPONSE_OK,
	RESPONSE_FAIL,
} response_code_enum_t;

volatile buffer_t rx_buffer;
volatile uint8_t response_ready;

void usart_send(USART_t *usart, const char * expect);
void handle_rx_interrupt(USART_t * usart);
response_code_enum_t check_response(volatile buffer_t *buffer, const char * expect);

#endif /* USART_HELPERS_H_ */