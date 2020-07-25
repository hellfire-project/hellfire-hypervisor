/*
Copyright (c) 2016, prpl Foundation

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

/* Simple UART and Blink Bare-metal application sample using virtualized IO. */

#include <arch.h>
#include <libc.h>
#include <hypercalls.h>
#include <guest_interrupts.h>
#include <platform.h>
#include <io.h>

volatile int32_t t2 = 0;



#define NEXECUTION 100000

void measure_get_guestID(){
	uint32_t ini, end, i;

	ini = get_performed_inst();

	for(i=0;i<NEXECUTION;i++){
		get_guestid();
	}

	end = get_performed_inst();

	printf("\nNumber of Instructions for get_guestid() %d", end - ini);

}

void measure_mdelay(){
	uint32_t ini, end, i;

	ini = get_performed_inst();

	for(i=0;i<NEXECUTION;i++){
		mdelay(0);
	}

	end = get_performed_inst();

	printf("\nNumber of Instructions for mdelay() %d", end - ini);

}

int main() {
	di();	


	measure_get_guestID();

	measure_mdelay();
  
  	while(1){}

	return 0;
}

