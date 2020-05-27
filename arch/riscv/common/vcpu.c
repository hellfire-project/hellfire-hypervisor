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
 * @file vcpu.c
 * 
 * @section DESCRIPTION
 * 
 * VCPU related function calls (context save, restore and instruction emulation).
 */

#include <vcpu.h> 
#include <types.h>
#include <libc.h>
#include <globals.h>
#include <hal.h>
#include <proc.h>
#include <scheduler.h>
#include <guest_interrupts.h>

/**
 * @brief Save the VCPU context. Saving only the necessary registers for 
 * the supported OSs. 
 */
void contextSave(){
	vcpu_t *vcputosave;
	
	if (!is_vcpu_executing){
		return;
	}
	
	vcputosave = vcpu_in_execution;
	
	if (vcputosave->init == 0){
		/* FIXME: CSR registers to save? .*/
		gpr_context_save(vcputosave->gpr);
	}

	fp_context_save((uint64_t*)vcputosave->fp_registers);

	vcputosave->cp0_registers[0] = read_csr(sstatus);
	vcputosave->cp0_registers[1] = read_csr(sie);
	vcputosave->cp0_registers[2] = read_csr(sip);
	vcputosave->pc = read_csr(mepc);
}

/**
 * @brief The hypervisor performs this routine when there is 
 * 	no VCPU read to execute. In this case the hypervisor 
 * 	will wait by the next interrupt event. 
 */ 
static void cpu_idle(){
	while(1){
		/* No VCPU read for execution. Wait by the next interrupt. */
		/* FIXME: Code to put the processor in idle mode. */
	}
}

/** 
 * @brief  Configure the processor to enter in idle mode. 
 * 
 */
static void config_idle_cpu(){
	write_csr(mepc, (long)cpu_idle);
}

/**
 * @brief  Restore the VCPU context on context switch. 
 */
void contextRestore(){

	vcpu_t *vcpu = vcpu_in_execution;

	/* There are not VCPUs ready to execute. Put CPU in adle mode. */
	if(!vcpu){
		config_idle_cpu();
		return;
	}

	/* Mark the VCPU as initialized. */
	if(vcpu_in_execution->init){
		vcpu_in_execution->init = 0;
	}else{
		write_csr(sstatus, vcpu->cp0_registers[0]);
		write_csr(sie, vcpu->cp0_registers[1]);
		write_csr(sip, vcpu->cp0_registers[2] | vcpu->guestclt2);
	}
	
	fp_context_restore((uint32_64_t*)vcpu->fp_registers);


	/* FIXME: Code for context restore should be here!!*/	
	
	setEPC(vcpu->pc);

	#if defined(RISCV64)
	write_csr(mstatus, (read_csr(mstatus) & 0xFFFFFFFFFFFFEFFF));
	write_csr(satp, (8ULL<<60) | (((uint64_t)vcpu->vm->id)<<44) | (uint64_t)vcpu->vm->root_page_table >> 12);
	#else
	write_csr(mstatus, (read_csr(mstatus) & 0xFFFFEFFF));
	write_csr(satp, (1<<31) | (((uint32_64_t)vcpu->vm->id)<<22) | (uint32_64_t)vcpu->vm->root_page_table >> 12);
	#endif

	asm volatile ("SFENCE.VMA");

	gpr_context_restore(vcpu->gpr);


}

/**
 * @brief Call low level instruction emulation. Not all architectures will 
 * implement it. 
 * 
 * @param epc Error PC.
 * @return 0 on success, otherwise error.
 */
uint32_t instruction_emulation(uint32_t epc){
	return 0;
}

