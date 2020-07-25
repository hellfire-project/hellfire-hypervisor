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
 */

#ifndef __RISCV__
#define __RISCV__

#define MTIME           (*(volatile long long *)(0x02000000 + 0xbff8))
#define MTIMECMP        (*(volatile long long *)(0x02000000 + 0x4000))

#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); __tmp; })

#define write_csr(reg, val) ({ \
  asm volatile ("csrw " #reg ", %0" :: "rK"(val)); })

#define set_csr_bits(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
  __tmp; })

#define clear_csr_bits(reg, bit) ({ unsigned long __tmp; \
  asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "rK"(bit)); \
  __tmp; })


#define read_instret() ({ unsigned long __tmp; \
  asm volatile ("rdinstret %0" : "=r"(__tmp)); __tmp; })


#define __riscv_xlen 64

#define CSR_FFLAGS      1
#define CSR_FRM         2
#define CSR_FCSR        3
#define CSR_MCYCLE      4
#define CSR_MINSTRET    5
#define CSR_MCYCLEH     6
#define CSR_MINSTRETH   7
#define CSR_CYCLE       8
#define CSR_TIME        9
#define CSR_INSTRET     10
#define CSR_CYCLEH      11
#define CSR_TIMEH       12
#define CSR_INSTRETH    13
#define CSR_MVENDORID   14
#define CSR_MARCHID     15
#define CSR_MIMPID      16
#define CSR_MHARTID     17
#define CSR_MSTATUS     18
#define CSR_MISA        19
#define CSR_MEDELEG     20
#define CSR_MIDELEG     21
#define CSR_MIE         22
#define CSR_MTVEC       23
#define CSR_MCOUNTEREN  24
#define CSR_MSCRATCH    25
#define CSR_MEPC        26
#define CSR_MCAUSE      27
#define CSR_MTVAL       28
#define CSR_MIP         29
#define CSR_SSTATUS     30
#define CSR_SEDELEG     31
#define CSR_SIDELEG     32
#define CSR_SIE         33
#define CSR_STVEC       34
#define CSR_SCOUNTEREN  35
#define CSR_SSCRATCH    36
#define CSR_SEPC        37
#define CSR_SCAUSE      38
#define CSR_STVAL       39
#define CSR_SIP         40
#define CSR_SATP        41
#define CSR_PMPCFG0     42
#define CSR_PMPCFG1     43
#define CSR_PMPCFG2     44
#define CSR_PMPCFG3     45
#define CSR_PMPADDR0    46
#define CSR_PMPADDR1    47
#define CSR_PMPADDR2    48
#define CSR_PMPADDR3    49
#define CSR_PMPADDR4    50
#define CSR_PMPADDR5    51
#define CSR_PMPADDR6    52
#define CSR_PMPADDR7    53
#define CSR_PMPADDR8    54
#define CSR_PMPADDR9    55
#define CSR_PMPADDR10   56
#define CSR_PMPADDR11   57
#define CSR_PMPADDR12   58
#define CSR_PMPADDR13   59
#define CSR_PMPADDR14   60
#define CSR_PMPADDR15   61

#define MSTATUS_UIE         0x00000001
#define MSTATUS_SIE         0x00000002
#define MSTATUS_HIE         0x00000004
#define MSTATUS_MIE         0x00000008
#define MSTATUS_UPIE        0x00000010
#define MSTATUS_SPIE        0x00000020
#define MSTATUS_HPIE        0x00000040
#define MSTATUS_MPIE        0x00000080
#define MSTATUS_SPP         0x00000100
#define MSTATUS_HPP         0x00000600
#define MSTATUS_MPP         0x00001800
#define MSTATUS_FS          0x00006000
#define MSTATUS_XS          0x00018000
#define MSTATUS_MPRV        0x00020000
#define MSTATUS_SUM         0x00040000
#define MSTATUS_MXR         0x00080000
#define MSTATUS_TVM         0x00100000
#define MSTATUS_TW          0x00200000
#define MSTATUS_TSR         0x00400000
#define MSTATUS32_SD        0x80000000
#define MSTATUS64_SD        0x8000000000000000

#define SSTATUS_UIE         0x00000001
#define SSTATUS_SIE         0x00000002
#define SSTATUS_UPIE        0x00000010
#define SSTATUS_SPIE        0x00000020
#define SSTATUS_SPP         0x00000100
#define SSTATUS_FS          0x00006000
#define SSTATUS_XS          0x00018000
#define SSTATUS_SUM         0x00040000
#define SSTATUS_MXR         0x00080000
#define SSTATUS32_SD        0x80000000
#define SSTATUS64_SD        0x8000000000000000

#if defined(RISCV64)
#define MCAUSE_INT			(1ULL<<63)
#define MCAUSE_MASK			0x7FFFFFFFFFFFFFFF
#define SATP_ASID_MASK		0x0FFFF00000000000
#define SATP_ASID_OFFSET	44
#else
#define MCAUSE_INT			(1<<31)
#define MCAUSE_MASK			0x7FFFFFFF
#define SATP_ASID_MASK		0x0FFFF000
#define SATP_ASID_OFFSET	12
#endif


#define SATP_PPN_MASK		0xFFFFFFFFFFF

#define DCSR_XDEBUGVER      (3U<<30)
#define DCSR_NDRESET        (1<<29)
#define DCSR_FULLRESET      (1<<28)
#define DCSR_EBREAKM        (1<<15)
#define DCSR_EBREAKH        (1<<14)
#define DCSR_EBREAKS        (1<<13)
#define DCSR_EBREAKU        (1<<12)
#define DCSR_STOPCYCLE      (1<<10)
#define DCSR_STOPTIME       (1<<9)
#define DCSR_CAUSE          (7<<6)
#define DCSR_DEBUGINT       (1<<5)
#define DCSR_HALT           (1<<3)
#define DCSR_STEP           (1<<2)
#define DCSR_PRV            (3<<0)

#define DCSR_CAUSE_NONE     0
#define DCSR_CAUSE_SWBP     1
#define DCSR_CAUSE_HWBP     2
#define DCSR_CAUSE_DEBUGINT 3
#define DCSR_CAUSE_STEP     4
#define DCSR_CAUSE_HALT     5

#define MCONTROL_TYPE(xlen)    (0xfULL<<((xlen)-4))
#define MCONTROL_DMODE(xlen)   (1ULL<<((xlen)-5))
#define MCONTROL_MASKMAX(xlen) (0x3fULL<<((xlen)-11))

#define MCONTROL_SELECT     (1<<19)
#define MCONTROL_TIMING     (1<<18)
#define MCONTROL_ACTION     (0x3f<<12)
#define MCONTROL_CHAIN      (1<<11)
#define MCONTROL_MATCH      (0xf<<7)
#define MCONTROL_M          (1<<6)
#define MCONTROL_H          (1<<5)
#define MCONTROL_S          (1<<4)
#define MCONTROL_U          (1<<3)
#define MCONTROL_EXECUTE    (1<<2)
#define MCONTROL_STORE      (1<<1)
#define MCONTROL_LOAD       (1<<0)

#define MCONTROL_TYPE_NONE      0
#define MCONTROL_TYPE_MATCH     2

#define MCONTROL_ACTION_DEBUG_EXCEPTION   0
#define MCONTROL_ACTION_DEBUG_MODE        1
#define MCONTROL_ACTION_TRACE_START       2
#define MCONTROL_ACTION_TRACE_STOP        3
#define MCONTROL_ACTION_TRACE_EMIT        4

#define MCONTROL_MATCH_EQUAL     0
#define MCONTROL_MATCH_NAPOT     1
#define MCONTROL_MATCH_GE        2
#define MCONTROL_MATCH_LT        3
#define MCONTROL_MATCH_MASK_LOW  4
#define MCONTROL_MATCH_MASK_HIGH 5

#define MIP_SSIP            (1 << IRQ_S_SOFT)
#define MIP_HSIP            (1 << IRQ_H_SOFT)
#define MIP_MSIP            (1 << IRQ_M_SOFT)
#define MIP_STIP            (1 << IRQ_S_TIMER)
#define MIP_HTIP            (1 << IRQ_H_TIMER)
#define MIP_MTIP            (1 << IRQ_M_TIMER)
#define MIP_SEIP            (1 << IRQ_S_EXT)
#define MIP_HEIP            (1 << IRQ_H_EXT)
#define MIP_MEIP            (1 << IRQ_M_EXT)

#define SIP_SSIP MIP_SSIP
#define SIP_STIP MIP_STIP

#define PRV_U 0
#define PRV_S 1
#define PRV_H 2
#define PRV_M 3

#define SPTBR32_MODE 0x80000000
#define SPTBR32_ASID 0x7FC00000
#define SPTBR32_PPN  0x003FFFFF
#define SPTBR64_MODE 0xF000000000000000
#define SPTBR64_ASID 0x0FFFF00000000000
#define SPTBR64_PPN  0x00000FFFFFFFFFFF

#define SPTBR_MODE_OFF  0
#define SPTBR_MODE_SV32 1
#define SPTBR_MODE_SV39 8
#define SPTBR_MODE_SV48 9
#define SPTBR_MODE_SV57 10
#define SPTBR_MODE_SV64 11

#define PMP_R     0x01
#define PMP_W     0x02
#define PMP_X     0x04
#define PMP_A     0x18
#define PMP_L     0x80
#define PMP_SHIFT     2
#define PMPCFG_COUNT  4
#define PMPADDR_COUNT 16

#define PMP_OFF   0x00
#define PMP_TOR   0x08
#define PMP_NA4   0x10
#define PMP_NAPOT 0x18

#define IRQ_S_SOFT   1
#define IRQ_H_SOFT   2
#define IRQ_M_SOFT   3
#define IRQ_S_TIMER  5
#define IRQ_H_TIMER  6
#define IRQ_M_TIMER  7
#define IRQ_S_EXT    9
#define IRQ_H_EXT    10
#define IRQ_M_EXT    11
#define IRQ_COP      12
#define IRQ_HOST     13

#define DEFAULT_RSTVEC     0x00001000
#define CLINT_BASE         0x02000000
#define CLINT_SIZE         0x000c0000
#define EXT_IO_BASE        0x40000000
#define DRAM_BASE          0x80000000

// page table entry (PTE) fields
#define PTE_V     0x001 // Valid
#define PTE_R     0x002 // Read
#define PTE_W     0x004 // Write
#define PTE_X     0x008 // Execute
#define PTE_U     0x010 // User
#define PTE_G     0x020 // Global
#define PTE_A     0x040 // Accessed
#define PTE_D     0x080 // Dirty
#define PTE_SOFT  0x300 // Reserved for Software

#define PTE_PPN_SHIFT 10

#define PTE_TABLE(PTE) (((PTE) & (PTE_V | PTE_R | PTE_W | PTE_X)) == PTE_V)

#ifdef __riscv

#if __riscv_xlen == 64
# define MSTATUS_SD MSTATUS64_SD
# define SSTATUS_SD SSTATUS64_SD
# define RISCV_PGLEVEL_BITS 9
# define SPTBR_MODE SPTBR64_MODE
#else
# define MSTATUS_SD MSTATUS32_SD
# define SSTATUS_SD SSTATUS32_SD
# define RISCV_PGLEVEL_BITS 10
# define SPTBR_MODE SPTBR32_MODE
#endif
#define RISCV_PGSHIFT 12
#define RISCV_PGSIZE (1 << RISCV_PGSHIFT)
#endif

#define TLB_LOAD_FETCH_EXCEPTION    	0x2
#define TLB_STORE_EXCEPTION    		0x3
#define GUEST_EXIT_EXCEPTION   		0x1b
#define GUEST_INSTRUCTION_EMULATION 0
#define GUEST_HYPERCALL 2
#define GUESTCTL1_RID_SHIFT     16
#define GUESTCLT2_GRIPL_SHIFT   24
#define GUESTCLT2_VIP_SHIFT   	10

/* RISCV REGISTERS */
#define REG_ZERO 0
#define REG_RA   1
#define REG_SP   2
#define REG_GP   3
#define REG_TP   4
#define REG_T0   5
#define REG_T1   6
#define REG_T2   7
#define REG_S0   8
#define REG_S1   9
#define REG_A0   10
#define REG_A1   11
#define REG_A2   12
#define REG_A3   13
#define REG_A4   14
#define REG_A5   15
#define REG_A6   16
#define REG_A7   17
#define REG_S2   18
#define REG_S3   19
#define REG_S4   20
#define REG_S5   21
#define REG_S6   22
#define REG_S7   23
#define REG_S8   24
#define REG_S9   25
#define REG_S10  26 
#define REG_S11  27
#define REG_T3   28 
#define REG_T4   29
#define REG_T5   30
#define REG_T6   31


#define PAGESIZE 4096
#define VIRTUALBASE 0x80000000

#define TIMER_INT 0X20

#if defined (RISCV64)

#define NUM_PAGE_TABLES 512
#define SND_PTE 0x3FE00000
#define TRD_PTE 0x1FF000

#define MPP_MASK 0xFFFFFFFFFFFFEFFF

#else

#define NUM_PAGE_TABLES 1024
#define SND_PTE 0x3FF000

#define MPP_MASK 0xFFFFFFFFFFFFEFFF

#endif




#endif 
