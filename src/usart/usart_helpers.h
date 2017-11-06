/*
 * usart_helpers.h
 *
 * Created: 11/4/2017 12:27:51 PM
 *  Author: Teodor
 */ 

#ifndef USART_HELPERS_H_
#define USART_HELPERS_H_

#include <buffer/buffer.h>

void usart_send(USART_t *usart, buffer_t *buffer);
buffer_t usart_receive(USART_t *usart);

#endif /* USART_HELPERS_H_ */