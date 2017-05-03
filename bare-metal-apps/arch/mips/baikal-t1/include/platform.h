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

#ifndef _PLATFORM_H
#define _PLATFORM_H

#include <types.h>

#define CPU_TICK_TO_US(ticks) ((ticks)/((CPU_SPEED/2)/100000))
#define CPU_TICK_TO_MS(ticks) ((ticks)/((CPU_SPEED/2)/1000))
#define MS_TO_CPU_TICK(ms) (ms*((CPU_SPEED/2)/1000))

#define START_TIMER() 	mtc0(CP0_STATUS, 0, mfc0(CP0_STATUS, 0) | (1 << 15))
#define NEXT_TIMER() 	mtc0(CP0_COMPARE, 0, mfc0(CP0_COUNT, 0) + MS_TO_CPU_TICK(1))
	
#define ENABLE_INTERVM_INT() mtc0(CP0_STATUS, 0, mfc0(CP0_STATUS, 0) | ((GUEST_INTERVM_INT << STATUS_IM_SHIFT) << 2))

typedef void interrupt_handler_t();

uint32_t interrupt_register(interrupt_handler_t *handler, uint32_t interrupt);
void init_proc();
uint32_t wait_time(uint32_t old_time, uint32_t ms_delay);

#endif