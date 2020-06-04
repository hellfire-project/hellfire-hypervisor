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

#include <arch.h>
#include <types.h>
#include <guest_interrupts.h>
#include <malloc.h>
#include <libc.h>
#include <platform.h>
#include <hypercalls.h>

#define NUM_GUEST_INTERRUPTS 10

typedef void interrupt_handler_t();

static interrupt_handler_t * interrupt_handlers[NUM_GUEST_INTERRUPTS] = {[0 ... NUM_GUEST_INTERRUPTS-1] = NULL};


/**
 * @brief Interrupt registration. 
 *   	Register interruts rotines. The valid interrupt numbers are
 *   	in the guest_interrupts.h file. 
 */
uint32_t interrupt_register(interrupt_handler_t *handler, uint32_t interrupt){
	uint32_t i;
	
	for(i=0; i<NUM_GUEST_INTERRUPTS; i++){
		if(interrupt & (1<<i)){
			if (interrupt_handlers[i] == NULL){
				interrupt_handlers[i] = handler;
				return (uint32_t)handler;
			}
		}
	}
		
	return 0;
}

/**
 * @brief General exception routine.
 *   All interrupts or exceptions invoke this routine. Call the 
 *   function handler corresponding to the RIPL field.
 */
void _irq_handler(uint32_t sstatus, uint32_t sepc){

	if(read_csr(sip)&TIMER_INT){


		if (interrupt_handlers[0]){
			((interrupt_handler_t*)interrupt_handlers[0])();
		}

		write_csr(sie,read_csr(sie) ^ TIMER_INT);

	}
	if(read_csr(sip)&VIRTUAL_INT){

		if (interrupt_handlers[1]){
			((interrupt_handler_t*)interrupt_handlers[1])();
		}

		write_csr(sip,read_csr(sip) ^ VIRTUAL_INT);
	}

			
}


/**
 * @brief Processor configuration. Called early during the initilization. 
 * 
 */
void init_proc(){
	/* Enable float-point instructions */
	write_csr(sstatus, read_csr(sstatus) | (1 << 13));

}



/**
 * @brief Determines if a time period was consumed.
 * @param old_time Initial time.
 * @param ms_delay Time period.
 * @return 0 if the period was not consumed, 1 otherwise.
 */
uint32_t wait_time(uint32_t old_time, uint32_t ms_delay){
	uint32_t diff_time;
	uint32_t now = get_mtimer_value();
    
	if (now >= old_time)
		diff_time = now - old_time;
	else
		diff_time = 0xffffffffffffffff - (old_time - now);

	if(diff_time > (ms_delay * MILISECOND)){
		return 1;
	}
	
	return 0;
}


void mdelay(uint32_t msec){
 	uint32_t now = get_mtimer_value();
    
    while(!wait_time(now, msec));       
  
}


void di(){
	write_csr(sie, read_csr(sie) ^ 2);
}

void ei(){
	write_csr(sie, read_csr(sie) | 2);	
}

void enable_interrupts(){
	ei();
}

