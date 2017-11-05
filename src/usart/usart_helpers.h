/*
 * usart_helpers.h
 *
 * Created: 11/4/2017 12:27:51 PM
 *  Author: Teodor
 */ 

#ifndef USART_HELPERS_H_
#define USART_HELPERS_H_

void usart_send(USART_t *usart, unsigned char *data);
void usart_receive(USART_t *usart, unsigned char *output, unsigned char size);

#endif /* USART_HELPERS_H_ */