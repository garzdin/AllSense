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
#include <util/atomic.h>

#define CR '\r'
#define NL '\n'

#define FIFO_BUFFER_LEGNTH (uint8_t) 128

union buffer_element {
	uint8_t byte;
	uint16_t halfword;
	uint32_t word;
};

fifo_desc_t fifo_desc_rx;
union buffer_element fifo_buffer_rx[FIFO_BUFFER_LEGNTH];

uint8_t usart_init(USART_t *usart);
void usart_send(USART_t *usart, const char *command);
void usart_recv(USART_t *usart);
uint8_t check_response(const char * expect);

#endif /* USART_HELPERS_H_ */