/*
 C o*pyright (c) 2016, prpl Foundation
 
 Permission to use, copy, modify, and/or distribute this software for any purpose with or without 
 fee is hereby granted, provided that the above copyright notice and this permission notice appear 
 in all copies.
 
 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
 INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE 
 FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, 
 ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 
 This code was written by Carlos Moratelli at Embedded System Group (GSE) at PUCRS/Brazil.
 
 */

#include <uart.h>
#include <types.h>
#include <arch.h>

static uint32_t serial_port = UART2;

int32_t serial_select(uint32_t serial_number){
			return -1;
}


void putchar(int32_t value){
	while( !(UART0_LSR&0x40) );
	UART0_RBR = value;   
}

int32_t kbhit(void){
	return 0;
}

uint32_t getchar(void){
	return 0;
}


