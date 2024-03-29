/**
 * \file *********************************************************************
 *
 * \brief USART Serial configuration
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_USART_SERIAL_H_INCLUDED
#define CONF_USART_SERIAL_H_INCLUDED

#define TTY_USART              &USARTC0
#define TTY_BAUDRATE           115200
#define TTY_CHAR_LENGTH        USART_CHSIZE_8BIT_gc
#define TTY_PARITY             USART_PMODE_DISABLED_gc
#define TTY_STOP_BIT           false
#define TTY_INTERRUPT_LEVEL    USART_INT_LVL_LO
#define TTY_RXC_vect           USARTC0_RXC_vect
#define TTY_DRE_vect           USARTC0_DRE_vect

#define USART_DEBUG_SERIAL                    &USARTE0
#define USART_DEBUG_SERIAL_BAUDRATE           115200
#define USART_DEBUG_SERIAL_CHAR_LENGTH        USART_CHSIZE_8BIT_gc
#define USART_DEBUG_SERIAL_PARITY             USART_PMODE_DISABLED_gc
#define USART_DEBUG_SERIAL_STOP_BIT           false
#define USART_DEBUG_RX_Vect                   USARTE0_RXC_vect
#define USART_DEBUG_TX_Vect                   USARTE0_TXC_vect

#endif /* CONF_USART_SERIAL_H_INCLUDED */
