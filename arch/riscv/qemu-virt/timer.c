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
#include <proc.h>

#define SYSTEM_TICK_INTERVAL (SYSTEM_TICK_US * MICROSECOND)
#define QUEST_TICK_INTERVAL (GUEST_QUANTUM_MS * MILISECOND)

/**
 * @brief Time interrupt handler.
 * 
 * Perfoms VCPUs scheduling and virtual timer interrupt injection on guests. 
 */
void timer_interrupt_handler(){
	uint32_t static guest_timer = 0;
	vcpu_t *vcpu = vcpu_in_execution;

	guest_timer++;

	if(read_csr(mie)&0x20){
		
		write_csr(mie,read_csr(mie) ^ 0x20);
		write_csr(mip,read_csr(mip) ^ 0x20);
		

	}

	if(guest_timer == 1000){

		guest_timer = 0;
		write_csr(mie,read_csr(mie)|0x20);
		write_csr(mip,read_csr(mip)|0x20);

	}

	MTIMECMP = MTIME + SYSTEM_TICK_INTERVAL;

	run_scheduler();

	/* wait interrupt bit fall to avoid spurious interrupts. */
	/* FIXME: It appears to be not working during debugging.*/
	/*while(read_csr(mip) & MIP_MTIP); */
}

/**
 * @brief Configures the CP0 timer.
 * 
 * This function will never return to the calling code. It waits for the
 * first timer interrupt.
 */
void start_timer(){
	MTIMECMP = MTIME + SYSTEM_TICK_INTERVAL;

    set_csr_bits(mie, MIP_MTIP);
    set_csr_bits(mstatus, MSTATUS_MIE);

	/* Wait for a timer interrupt */
	for(;;);
}

