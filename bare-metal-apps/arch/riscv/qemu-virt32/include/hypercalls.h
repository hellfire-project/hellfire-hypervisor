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

#ifndef  __HYPERCALLS_H
#define  __HYPERCALLS_H

#include <hypercall_defines.h>

/* Read from privileged address  */
#define readio(addr) ({ int32_t __value; \
asm volatile ("nop"); })

/* Write to privileged address */
#define writeio(reg, value) ({ int32_t __ret; \
asm volatile ("nop"); })

/* interVM send message  */
#define ipc_send(targed_id, msg, size) ({ int32_t __ret; \
asm volatile (                    \
"move a0, %z1 \n \
 move a1, %z2 \n \
 move a2, %z3 \n \
 li a7, %4 \n\
 ecall \n\
  move %0, a0" \
 : "=r" (__ret) : "r" ((uint32_t) (target_id)), "r" ((uint32_t) (msg)), "r" ((uint32_t) (size)), "I" (HCALL_IPC_SEND_MSG) : "a0", "a1", "a2","a7"); \
 __ret; })
 
 /* interVM recv message  */
#define ipc_recv(source_id, msg) ({ int32_t __ret; \
asm volatile (                    \
"move a0, %z2 \n\
 li a7, %3 \n\
 ecall \n\
 sw a1, 0(%z1)\n \
 move %0, a0 " \
 : "=r" (__ret) : "r" ((uint32_t) (source_id)), "r" ((uint32_t) (msg)), "I" (HCALL_IPC_RECV_MSG) : "a0", "a1", "a7"); \
 __ret; })

 
/* Get own guest ID  */
#define get_guestid() ({ int32_t __ret; \
asm volatile (                    \
"li a7, %1 \n\
 ecall \n\
 move %0, a0 " \
 : "=r" (__ret) : "I" (HCALL_GET_VM_ID) : "a0", "a7"); \
 __ret; })

 /* Ethernert link checker */
#define eth_watch() ({ int32_t __ret; \
asm volatile ("nop"); })
 
/* Ethernert get mac */
#define eth_mac(msg) asm volatile (                    \
asm volatile ("nop"); )

/* Ethernet send message  */
#define eth_send_frame(msg, size) ({ int32_t __ret; \
asm volatile ("nop"); })
 
 /* Ethernet recv message  */
#define eth_recv_frame(msg) ({ int32_t __ret; \
asm volatile ("nop"); })
 
/* USB get device descriptor   */
#define usb_get_device_descriptor(descriptor, size) ({ int32_t __ret; \
asm volatile ("nop"); })
 
/* USB polling. Updates the USB state machines.   */
#define usb_polling() ({ int32_t __ret; \
asm volatile ("nop"); })
 
/* USB send data  */
#define usb_control_send(msg, size) ({ int32_t __ret; \
asm volatile ("nop"); })

/* Re-enable an interrupt */
#define reenable_interrupt(irq) ({ int32_t __ret; \
asm volatile ("nop"); })

/* Read 1K byte from flash - PUF specific function.  */
#define read_1k_data_flash(buf) ({ int32_t __ret; \
asm volatile ("nop"); })

/* Write 1K byte to flash - PUF specific function.  */
#define write_1k_data_flash(buf) ({ int32_t __ret; \
asm volatile ("nop"); })

/* Peformance counter start.  */
#define performance_counter_start(perf0, perf1) ({ int32_t __ret; \
asm volatile ("nop"); })
 
/* Performance counter stop.  */
#define performance_counter_stop(buf) ({ int32_t __ret; \
asm volatile ("nop"); })

 /* UART send msg */
#define uart_send(msg, size) ({ int32_t __ret; \
asm volatile (                    \
"move a0, %z1 \n \
 move a1, %z2 \n \
 li   a7, %3 \n\
 ecall \n\
 move %0, a0" \
 : "=r" (__ret) : "r" ((uint32_t) (msg)), "r" ((uint32_t) (size)), "I" (HCALL_UART_SEND) : "a0", "a1", "a7"); \
 __ret; })

#define get_mtimer_value() ({ int32_t __ret; \
asm volatile (                    \
"li a7, %1 \n\
 ecall \n\
 move %0, a0 " \
 : "=r" (__ret) : "I" (HCALL_GET_MTIMER_VALUE) : "a0", "a7"); \
 __ret; })

#define get_performed_inst() ({ int32_t __ret; \
asm volatile (                    \
"li a7, %1 \n\
 ecall \n\
 move %0, a0 " \
 : "=r" (__ret) : "I" (HCALL_PERFORMED_INST) : "a0", "a7"); \
 __ret; })

#endif

