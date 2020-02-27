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
 * @file guest_services.c
 * 
 * @section DESCRIPTION
 * 
 * This driver implements the guests hypercalls.
 */

#include <hypercall.h>
#include <scheduler.h>
#include <hal.h>
#include <globals.h>
#include <tlb.h>
#include <driver.h>
#include <hypercall_defines.h>
#include <proc.h>
#include <guest_interrupts.h>
#include <libc.h>

/**
 * @brief Hypercall implementation. Returns the VM identifier number for the calling VM. 
 * V0 guest register will be replaced with the VM id. 
 */
void get_vm_id(){
	MoveToPreviousGuestGPR(REG_A0,vcpu_in_execution->vm->id);
}

/**
 * @brief Driver init call.  Registers the hypercalls. 
 */
void guest_services_init(){
	if (register_hypercall(get_vm_id, HCALL_GET_VM_ID) < 0){
		ERROR("Error registering the HCALL_GET_VM_ID hypercall");
		return;
	}
    
	INFO("Hypercall Guest ID implemented.");
}

driver_init(guest_services_init);


