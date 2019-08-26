/*
 * Copyright (c) 2016, prpl Foundation
 * 
 * Permission to use, copy, modify, and/or distribute this software for any purpose with or without 
 * fee is hereby granted, provided that the above copyright notice and this permission notice appear 
 * in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE 
 * FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, 
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 * 
 * This code was written by Carlos Moratelli at Embedded System Group (GSE) at PUCRS/Brazil.
 * 
 */

/**
 * @file reset.c
 * 
 * @section DESCRIPTION
 * 
 * This is a software reset driver to the PIC32MZ Starter Kit since it lacks a reset button. 
 * 
 * 
 */

#include <rv8.h>
#include <driver.h>
#include <globals.h>
#include <libc.h>
#include <hal.h>
#include <interrupts.h>


/**
 * @brief Performs a software reset to the board. 
 * 
 */
void SoftReset(){
    

}

/**
 * @brief This call must be used in cases where the hypervisor is halted and must be reseted. 
 */
void wait_for_reset(){

}

/**
 * @brief Interrupt handler for the SW1 button.
 */
void sw1_button_handler(){

}


/**
 * @brief Driver init. Registers the interrupt handler routine and configures the RB12 pin
 * associated to the SW1 button. 
 */
void sw1_button_interrupt_init(){
    
	
}

driver_init(sw1_button_interrupt_init);
