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

/**
 * @file timer.c
 * 
 * @section DESCRIPTION
 * 
 * Timer interrupt subsystem. This timer is used for VCPU scheduling and  
 * virtual timer interrupt injection on Guests. 
 * 
 * Every guest receive timer interrupt each 1ms. This will be replaced soon with 
 * a configurable guest timer. 
 */

#include <globals.h>
#include <hal.h>
#include <qemu_virt.h>
#include <guest_interrupts.h>
#include <scheduler.h>
#include <interrupts.h>
#include <libc.h>

#define SYSTEM_TICK_INTERVAL (SYSTEM_TICK_US * MICROSECOND)
#define QUEST_TICK_INTERVAL (GUEST_QUANTUM_MS * MILISECOND)


/**
 * @brief Configures the COMPARE register to the next interrupt. 
 * 
 * @param interval Time interval to the next interrupt in CPU ticks (CPU_FREQ/2)
 */
void calc_next_timer_interrupt(uint32_t interval){
	return;
}

/**
 * @brief Time interrupt handler.
 * 
 * Perfoms VCPUs scheduling and virtual timer interrupt injection on guests. 
 */
static void timer_interrupt_handler(){
	static uint32_t past = 0;
	uint32_t now, diff_time;
	
	calc_next_timer_interrupt(SYSTEM_TICK_INTERVAL);
	
	run_scheduler();
	
	/* FIXME: configure next timer interrupt. */	
    
}

/**
 * @brief Configures the CP0 timer.
 * 
 * This function will never return to the calling code. It waits for the
 * first timer interrupt.
 */
void start_timer(){
	    
	/* Wait for a timer interrupt */
	while(1){};
}

