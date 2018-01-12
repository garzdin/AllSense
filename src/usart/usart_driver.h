/*
 * usart_driver.h
 *
 * Created: 11/4/2017 12:27:51 PM
 *  Author: Teodor
 */ 

#ifndef USART_DRIVER_H_
#define USART_DRIVER_H_

#include <asf.h>
#include <stdio.h>

#define CR '\r'
#define NL '\n'

#define TTY_RX_FIFO_SIZE 128
#define TTY_TX_FIFO_SIZE 128

// FIFO descriptors and buffers
fifo_desc_t tty_rx_fifo;
fifo_desc_t tty_tx_fifo;
uint8_t tty_rx_buffer[TTY_RX_FIFO_SIZE];
uint8_t tty_tx_buffer[TTY_TX_FIFO_SIZE];

// local function prototypes
FILE *tty_init(void);
int tty_get(FILE *);
int tty_put(char, FILE *);

#endif /* USART_DRIVER_H_ */