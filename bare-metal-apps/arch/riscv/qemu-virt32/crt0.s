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


.equ REGBYTES, 4

.macro lxsp a, b
lw \a, ((\b)*REGBYTES)(sp)
.endm

.macro sxsp a, b
sw \a, ((\b)*REGBYTES)(sp)
.endm
    

.align 4
trap_vector:
    # Save registers.
    addi    sp, sp, -124
    sxsp    ra, 0
    sxsp    sp, 1
    sxsp    gp, 2
    sxsp    fp, 3
    sxsp    tp, 4
    sxsp    a0, 5
    sxsp    a1, 6
    sxsp    a2, 7
    sxsp    a3, 8
    sxsp    a4, 9
    sxsp    a5, 10
    sxsp    a6, 11
    sxsp    a7, 12
    sxsp    s1, 13
    sxsp    s2, 14
    sxsp    s3, 15
    sxsp    s4, 16
    sxsp    s5, 17
    sxsp    s6, 18
    sxsp    s7, 19
    sxsp    s8, 20
    sxsp    s9, 21
    sxsp    s10, 22
    sxsp    s11, 23
    sxsp    t0, 24
    sxsp    t1, 25
    sxsp    t2, 26
    sxsp    t3, 27
    sxsp    t4, 28
    sxsp    t5, 29
    sxsp    t6, 30

    # Invoke the handler.
    csrr    a0, scause
    csrr    a1, sepc
    jal     _irq_handler

    # Restore registers.
    lxsp    ra, 0
    lxsp    sp, 1
    lxsp    gp, 2
    lxsp    fp, 3
    lxsp    tp, 4
    lxsp    a0, 5
    lxsp    a1, 6
    lxsp    a2, 7
    lxsp    a3, 8
    lxsp    a4, 9
    lxsp    a5, 10
    lxsp    a6, 11
    lxsp    a7, 12
    lxsp    s1, 13
    lxsp    s2, 14
    lxsp    s3, 15
    lxsp    s4, 16
    lxsp    s5, 17
    lxsp    s6, 18
    lxsp    s7, 19
    lxsp    s8, 20
    lxsp    s9, 21
    lxsp    s10, 22
    lxsp    s11, 23
    lxsp    t0, 24
    lxsp    t1, 25
    lxsp    t2, 26
    lxsp    t3, 27
    lxsp    t4, 28
    lxsp    t5, 29
    lxsp    t6, 30
    addi sp, sp, 124
    sret

.section .e_entry
.globl _start
_start:
    
    # setup default trap vector
    la      t0, trap_vector
    csrw    stvec, t0

    la  sp, _stack
    la  a0, _bss_end
    la  a1, _bss_start
BSS_CLEAR:
1:  sw  zero, 0(a1)
    addi a1, a1, 4
    bne a1, a0, 1b
    nop
	jal     init_mem
	nop
	jal     init_proc
	nop
	jal     init_network
	nop
	jal     main
    nop
2:  j 2b
    nop


	
	