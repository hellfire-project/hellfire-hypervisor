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
#include <pic32mz.h>
#include <mips_cp0.h>
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
	uint32_t count;
	
	count = mfc0(CP0_COUNT, 0);
	count += interval;
	mtc0(CP0_COMPARE, 0, count);
	
	IFSCLR(0) = 1;  
}

/**
 * @brief Time interrupt handler.
 * 
 * Perfoms VCPUs scheduling and virtual timer interrupt injection on guests. 
 */
static void timer_interrupt_handler(){
	uint32_t ini = mfc0(25, 1);
	void * vc = vcpu_in_execution;
	static uint32_t past = 0;
	uint32_t now, diff_time;
	static uint32_t exec_count = 0;
	static uint32_t instruction_count = 0;

	
	calc_next_timer_interrupt(SYSTEM_TICK_INTERVAL);
	
	run_scheduler();
	
	now = mfc0(CP0_COUNT, 0);
	if (now >= past)
		diff_time = now - past;
	else
		diff_time = 0xffffffff - (past - now);

	/* Insert a virtual timer interrupt to the guest each other timer tick. */
	if(diff_time >= QUEST_TICK_INTERVAL){
		setGuestCTL2(getGuestCTL2() | (GUEST_TIMER_INT << GUESTCLT2_GRIPL_SHIFT));
		past = now;
	}

	if(vc != vcpu_in_execution){
		exec_count++;
		instruction_count += mfc0(25, 1) - ini + 5;
		if(exec_count == 100000){
			printf("\ninstruction_count %d", instruction_count);
			exec_count = 0;
			instruction_count = 0;
		}
	}

    
}

/**
 * @brief Configures the CP0 timer.
 * 
 * This function will never return to the calling code. It waits for the
 * first timer interrupt.
 */
void start_timer(){
	uint32_t temp_CP0, offset;
    
	offset = register_interrupt(timer_interrupt_handler);
	OFF(0) = offset;
	INFO("CP0 Timer interrupt registered at 0x%x.", offset);
    
	IPC(0) = 0x1f;
	IFSCLR(0) = 1;
	IECSET(0) = 1;
    
	temp_CP0 = mfc0(CP0_COUNT, 0);
	temp_CP0 += 10000;
	mtc0(CP0_COMPARE, 0, temp_CP0);
	
	INFO("Starting hypervisor execution.\n");

	asm volatile ("ei");    
    
	/* Wait for a timer interrupt */
	while(1){};
}

