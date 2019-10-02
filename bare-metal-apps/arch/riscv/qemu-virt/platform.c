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

#define NUM_GUEST_INTERRUPTS 10

typedef void interrupt_handler_t();

static interrupt_handler_t * interrupt_handlers[NUM_GUEST_INTERRUPTS] = {[0 ... NUM_GUEST_INTERRUPTS-1] = NULL};


/**
 * @brief Interrupt registration. 
 *   	Register interruts rotines. The valid interrupt numbers are
 *   	in the guest_interrupts.h file. 
 */
uint32_t interrupt_register(interrupt_handler_t *handler, uint32_t interrupt){
		
	return 0;
}

/**
 * @brief General exception routine.
 *   All interrupts or exceptions invoke this routine. Call the 
 *   function handler corresponding to the RIPL field.
 */
void _irq_handler(uint32_t status, uint32_t cause){

	
}


/**
 * @brief Processor configuration. Called early during the initilization. 
 * 
 */
void init_proc(){

}



/**
 * @brief Determines if a time period was consumed.
 * @param old_time Initial time.
 * @param ms_delay Time period.
 * @return 0 if the period was not consumed, 1 otherwise.
 */
uint32_t wait_time(uint32_t old_time, uint32_t ms_delay){
	
	return 0;
}



