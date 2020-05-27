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
 * @file hal.c
 * 
 * @section DESCRIPTION
 * 
 * Functions for access and configuration of the CP0 and Guest CP0. 
 * Supports the M5150 processor core and initial hypervisor configuration. 
 */

#include <libc.h>
#include <types.h>
#include <hal.h>
#include <globals.h>
#include <proc.h>
#include <board.h>
#include <malloc.h>
#include <vm.h>
#include <driver.h>
#include <timer.h>
#include <libc.h>

/* HEAP size as calculated by the linker script. */
extern uint32_t _heap_size;
extern uint64_t __pages_start;

/* Stringfy compiler parameters. */
#define STR(x) #x
#define STR_VALUE(x) STR(x)

/** @brief Read the misa register and translate the extention bits 
 *   to a string. 
 *  @param ex Char array.  
 *  @param sz Size of the array.
 *  @return pointer to the array.
 */
static char* get_extensions(char *ex, uint32_t sz){
    uint32_t i, c = 0, mask = 1;
    uint32_t misa = read_csr(misa);

    for(i=0; (i<26) & (i<sz); i++){
        if(misa & mask){
            ex[c++] = 65 + i;
        }
        mask = mask << 1;
    }

    ex[c] = 0;

    return ex;
}


/** @brief Determine the number of valid ASID bits in the SATP register.
 *  @return number of valid bits.
 */
static int get_asid_sz(){
	uint64_t asid;
	uint32_t i = 0;
	
	write_csr(satp, SATP_ASID_MASK);

	asid = get_field(read_csr(satp), SATP_ASID_MASK);

	while(asid & 0x1){
		i++;
		asid >>= 1;
	}

	return i;
}

/**
 * @brief Early boot message. 
 * 	Print to the stdout usefull hypervisor information.
 */
static void print_config(void){
    char ex[26];

	INFO("===========================================================");
	INFO("prplHypervisor %s [%s, %s]", STR_VALUE(HYPVERSION), __DATE__, __TIME__);
	INFO("Copyright (c) 2016, prpl Foundation");
	INFO("===========================================================");
	INFO("CPU Core:      %s", STR_VALUE(CPU_ID));
    INFO("Extentions:    %s", get_extensions(ex, sizeof(ex)));
    INFO("ASID size:     %dbits", get_asid_sz());
    INFO("Pages Address  0x%x", (uint64_t)&__pages_start);
	INFO("Board:         %s", STR_VALUE(CPU_ARCH));
	INFO("System Clock:  %dMHz", CPU_FREQ/1000000);
	INFO("Heap Size:     %dKbytes", (int)(&_heap_size)/1024);
	INFO("Scheduler:     %dms", QUANTUM_SCHEDULER_MS);
	INFO("Guest Tick:    %dms", SYSTEM_TICK_US/1000);
	INFO("VMs:           %d\n", NVMACHINES);
}

/**
 * @brief C code entry. This is the first C code performed during 
 * hypervisor initialization. Called from early boot stage to perform 
 * overall hypervisor configuration. 
 * 
 * The hypervisor should never return form this call. The start_timer()
 * call should configure the system timer and wait by the first 
 * timer interrupt.
 * 
  */
void hyper_init(){
	
	/* Specific board configuration. */
	early_platform_init();    
	
	/* early boot messages with hypervisor configuration. */
	print_config();
	
	/* Processor inicialization */
	if(LowLevelProcInit()){
		CRITICAL("Low level processor initialization error.");
	}
	
	/* Configure the HEAP space on the allocator */ 
	init_mem();

	/*Enable global interrupt. IE bit in status register.*/
	enableIE();

	/*Initialize VCPUs and virtual machines*/
	initializeMachines();
	
	/* Initialize device drivers */    
	drivers_initialization();
	
	/* Start system timer. Should not return from this call.
	 *	   This call will wait for the first timer interrupt. */
	start_timer();
	
	/* Should never reach this point !!! */
	CRITICAL("Hypervisor initialization error.");
}


/**
 * @brief Verify if the processor is in root-kernel mode. 
 * @return 1 for root-kernel mode, 0 otherwise.
 */
int32_t isRootMode(){
	return 0;
}


/**
 * @brief Verify if the processor implements the VZ module . 
 * @return 1 VZ module available, 0 otherwise.
 */
int32_t hasVZ(){
	return 0;
}


/**
 * @brief Set the GPR Shadow Bank. 
 *      The hypervisor uses the GPR shadow page 0. The others GPR shadows keep the VM's context.
 * 
 * @return 0 for error or 1 for success.
 */
int32_t ConfigureGPRShadow(){
	return 0;
}


/**
 * @brief Low level processor initialization. 
 *      Called once during hypervisor Initialization.
 * 
 * @return 1 for error or 0 for success.
 */
int32_t LowLevelProcInit(){

	write_csr(mstatus, read_csr(mstatus) | 0x100000);

	/* Enable fp instructions */
	write_csr(mstatus, read_csr(mstatus) | (1 << 13));
    
	return 0;
}


/**
 * @brief Extract the execCode field from cause register
 * 
 * @return ExecCode value.
 */
uint32_t getCauseCode(){
	return 0;
}


/**
 * @brief Extract the hypercall code from hypercall instruction. 
 * 
 * @return Hypercall code.
 */
uint64_t getHypercallCode(){
	return MoveFromPreviousGuestGPR(REG_A7);	
}


/**
 * @brief Checks if the exception happend on a branch delay slot. 
 * 
 * @return 0 for non branch delay slot, otherwise greater than 0.
 */
uint32_t getCauseBD(){
	return 0;
}


/**
 * @brief Extracts the  Guest ExecCode field from guestctl0 register. 
 * 
 * @return Guest ExecCode.
 */
uint32_t getGCauseCode(){
	return 0;
}


/**
 * @brief Extracts the interrupt pending bits (IP0:IP9) from cause register.
 * 
 * @return Interrupt pending bits.
 */
uint32_t getInterruptPending(){
	return 0;
}	


/**
 * @brief Set the Compare register to the next timer interruption.
 * 
 */
void confTimer(uint32_t quantum){
}


/**
 * @brief Set the IM bits on the status reg.
 * 
 */
void setInterruptMask(uint32_t im){
}


/**
 * @brief Clear the IM bits on the status reg .
 * 
 */
void clearInterruptMask(uint32_t im){
	
}


/**
 * @brief Enable global interrupt. IE bit in status register.
 * 
 */
void enableIE(){

	write_csr(mstatus, read_csr(mstatus) | 0xa);
	
	write_csr(mideleg, read_csr(mideleg) | 0x22);
		
}


/**
 * @brief Verify if the processor implements GuestID field.
 * 
 * @return 1 for guestid supported, 0 otherwise.
 */
uint32_t hasGuestID(){
	return 0;
}


/**
 * @brief Verify if the processor allow direct root mode.
 * 
 * @return 1 for direct root supported, 0 otherwise.
 */
uint32_t isDirectRoot(){
	return 0;
}


/**
 * @brief Set CP0 EPC. 
 * 
 */
void setEPC(uint64_t epc){
    write_csr(mepc, epc);   
}


/**
 * @brief Get CP0 EPC. 
 * 
 * @return EPC address.
 */
uint32_t getEPC(){
	return 0;
}


/**
 * @brief Set root GuestID mode. 
 * 
 */
void setGuestRID(uint32_t guestrid){
}


/**
 * @brief Set GuestID. 
 * 
 */
void setGuestID(uint32_t guestid){
	
}


/**
 * @brief Get GuestID. 
 * 
 */
uint32_t getGuestID(void){
	return 0;
}


/**
 * @brief Check if the processor uses root ASID. 
 * 
 * @return 1 for root ASID supported, 0 otherwise
 */
uint32_t isRootASID(){
	return 0;
}


/**
 * @brief Set the processor's to Guest Mode bit. 
 * 
 */
void setGuestMode(){
	
}

/**
 * @brief Clear the processor's to Guest Mode bit. 
 * 
 */
void clearGuestMode(){
	
}


/**
 * @brief Set specific bits on CP0 STATUS reg.. 
 * 
 */
void setStatusReg(uint32_t bits){
	
}


/**
 * @brief Check if the processor supports 1k page size. 
 * 
 * @return 0 for not supported, greather than 0 for supported. 
 */
uint32_t has1KPageSupport(){
	return  0;
}


/**
 * @brief Disable 1K page support to keep compatibility with 4K page size. 
 * 
 */
void Disable1KPageSupport(){
	
}


/**
 * @brief Check if the processor will enter in guest mode on next eret instruction.
 * @return 1 is entering in guest mode, 0 no entering in guest mode. 
 */
int32_t isEnteringGuestMode(){
	return 0;
}


/**
 * @brief Get bad instruction address .
 * @return Bad instruction address. 
 */
uint32_t getBadVAddress(){
	return 0;
}

/**
 * @brief Set the Lowest GPR Shadow.
 * @return GPR value. 
 */
void setLowestGShadow(uint32_t lowestshadow){
	
}


/**
 * @brief Get the Lowest GPR Shadow.
 * @return Lowest guest GPR shadow. 
 */
uint32_t getLowestGShadow(void){
	return 0;
}


/**
 * @brief Set the previous shadow set.
 */
void setPreviousShadowSet(uint32_t shadow_set){
}

/**
 * @brief Get the previous  GPR Shadow.
 * @return Previous guest GPR shadow. 
 */
uint32_t getPreviousShadowSet(){
	return 0;
}

/**
 * @brief Get the number of GPR Shadows.
 * @return Number of GPR shadows. 
 */
uint32_t getNumberGPRShadow(){
	return 0;
}


/**
 * @brief Return the CP0 COUNTER.
 * @return CP0 COUNTER. 
 */
uint32_t getCounter(void){
	return 0;
}


/**
 * @brief Set CP0 GTOffset .
 */
void setGTOffset(int32_t gtoffset){
    
}


/**
 * @brief Set CP0 GuestCLT2 .
 */
void setGuestCTL2(uint32_t guestclt2){
    
}

/**
 * @brief Get CP0 GuestCLT2 .
 * 
 * @return guestctl2 register value.
 */
uint32_t getGuestCTL2(){
    return 0;
}


/**
 * @brief Get CP0 Random .
 * @return Random value.
 */
uint32_t getRandom(){
    return 0;
}

/**
 * @brief Get the most recent instruction which caused a exception.
 * @return Bad Instruction.
 */
uint32_t getBadInstruction(){
	return 0;
}


/**
 * @brief Wait for microseconds. 
 * @param usec Wait time.
 */
void udelay (uint32_t usec){

}

