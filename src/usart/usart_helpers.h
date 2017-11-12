/*
 * usart_helpers.h
 *
 * Created: 11/4/2017 12:27:51 PM
 *  Author: Teodor
 */ 

#ifndef USART_HELPERS_H_
#define USART_HELPERS_H_

#include <buffer/buffer.h>
#include <command/command.h>

void usart_send(USART_t *usart, buffer_t *buffer);
buffer_t usart_receive(USART_t *usart);
bool usart_send_and_expect(USART_t * usart, const char * command, const char * expect);

#endif /* USART_HELPERS_H_ */