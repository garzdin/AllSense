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

#define CR '\r'
#define NL '\n'

#define _SS_MAX_RX_BUFF 64
uint8_t _receive_buffer[_SS_MAX_RX_BUFF];
uint8_t is_listening;
volatile uint8_t _receive_buffer_tail;
volatile uint8_t _receive_buffer_head;
volatile uint8_t _buffer_overflow;

void usart_init(USART_t *usart);
void usart_listen(USART_t *usart);
void usart_stop_listening(USART_t *usart);
void usart_send(USART_t *usart, const char * command);
void usart_recv(USART_t *usart);
uint8_t usart_read(USART_t *usart);
uint8_t usart_available(USART_t *usart);
uint8_t check_response(const char * expect);

#endif /* USART_HELPERS_H_ */