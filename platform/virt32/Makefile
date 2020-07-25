#
#Copyright (c) 2016, prpl Foundation
#
#Permission to use, copy, modify, and/or distribute this software for any purpose with or without 
#fee is hereby granted, provided that the above copyright notice and this permission notice appear 
#in all copies.
#
#THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
#INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE 
#FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
#LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, 
#ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
#This code was written by Carlos Moratelli at Embedded System Group (GSE) at PUCRS/Brazil.

#Input CFG file for VMs configuration
#CFG_FILE = cfg/perfinstr1.cfg
#CFG_FILE = cfg/sample-ping-pong.cfg
#CFG_FILE = cfg/test.cfg
CFG_FILE = cfg/sample-blink.cfg

# CROSS Compiler 
CROSS_COMPILER = riscv32-unknown-elf-

# Optional Device Drivers
#CONFIG_GUEST_SERVICES = yes
CONFIG_INTERVMCOMM_DRV = yes
#CONFIG_NO_VMS_DRV = yes
#CONFIG_PIC32MZ_USB_DRV = yes
#CONFIG_PIC32MZ_ETHERNET_DRV = yes
#CONFIG_VIRTUAL_IO_DRV = yes
#CONFIG_INTERRUPT_REDIRECT_DRV = yes

# The PIC32MZ Ethernet shared driver allows to share the 
# ethernet device among several VMs. See instruction on the
# pic32mz-ethernet-shared.c file. 
# To use it comment the CONFIG_PIC32MZ_ETHERNET_DRV.
#CONFIG_PIC32MZ_ETHERNET_SHARED_DRV = yes

# The following drivers is only for tests/performance purpose. 
#CONFIG_TIMER_TEST_DRV = yes
#CONFIG_PERFORMANCE_COUNTER_DRV = yes
#CONFIG_INTERRUPT_LATENCY_TEST_DRV = yes

# Platform info
CFLAGS = -DCPU_ID="RISCv 32"
CFLAGS += -DCPU_ARCH="QEMU VIRT 32"
CFLAGS += -DCPU_FREQ=20000000

# Define DEBUG_GUEST to yes if you desire to compile the guests for debug. The code optimization will be O0.
DEBUG_GUEST = no


########################################################################################################
# SHOULD NOT BE NEEDED TO MODIFY ANYTHING FROM WHERE. UNLESS YOU ARE ADDING NEW HYPERVISOR SOURCE FILES
# OR PORTING TO A NEW PLATFORM.
########################################################################################################
APP_LIST = ""

SHELL := /bin/bash

# Setup PIC32MZEF core configuration to be used with Microchip_UART.hex bootloader
BAUDRATE=115200
F_CLK=200000000
SERIAL_DEV=/dev/ttyACM0

TOPDIR=../../

PLATFORM_DIR=platform/qemu-virt32/
VERSION:=$(shell $(TOPDIR)/scripts/genversion.sh)

LINKER_SCRIPT = ../../arch/riscv/qemu-virt32/qemu-virt32.ld

### GCC flags configuration: processor tunning ###
CFLAGS += -O3 -march=rv32imac -mabi=ilp32 -Wall -fpie -ffunction-sections -fdata-sections -DRISCV32
#MIPZ VZ support
CFLAGS += -Wno-duplicate-decl-specifier -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast#-Wa, 
#flointing pointing options
CFLAGS +=  #-mno-check-zero-division -msoft-float -fshort-double
#General options
CFLAGS += -g -c -ffreestanding -nostdlib -fomit-frame-pointer #-G 0
#Additional features flags
CFLAGS += -DCPU_SPEED=$(F_CLK) -DHYPVERSION=${VERSION}
# LD flags
LDFLAGS = 

### Include dirs ###
INC_DIRS = -I$(TOPDIR)arch/riscv/qemu-virt32/include \
           -I$(TOPDIR)arch/riscv/common/include \
           -I$(TOPDIR)/platform/include \
           -I$(TOPDIR)sys/lib/include \
           -I$(TOPDIR)sys/kernel/include \
           -I$(TOPDIR)platform/virt32/include \
           -I$(TOPDIR)/include

BUILDDIR=build/hypervisor
 
#Configure CROSS COMPILER
AS = $(CROSS_COMPILER)as 
LD = $(CROSS_COMPILER)ld 
OBJDUMP = $(CROSS_COMPILER)objdump
READELF = $(CROSS_COMPILER)readelf
OBJCOPY = $(CROSS_COMPILER)objcopy
SIZE = $(CROSS_COMPILER)size
CC= $(CROSS_COMPILER)gcc
STRIP = $(CROSS_COMPILER)strip

APP = prplHypervisor

#all: config_vms lib kernel common pic32mz platform drivers $(APP) bare_apps generate_firmware
all: config_vms lib kernel common platform drivers qemu-virt32 $(APP) bare_apps generate_firmware

include $(TOPDIR)sys/sys.mk
include $(TOPDIR)arch/riscv/common/common.mk
include $(TOPDIR)arch/riscv/qemu-virt32/qemu-virt32.mk
include board/board.mk
include $(TOPDIR)/drivers/drivers.mk

$(APP): 
	$(LD) $(LDFLAGS) -g -T$(LINKER_SCRIPT) -Map $(APP).map -N -o $(APP).elf *.o $(OBJ)
	#$(STRIP) $(APP).elf
	$(OBJDUMP) --disassemble --reloc $(APP).elf > $(APP).lst
	$(OBJDUMP) -h $(APP).elf > $(APP).sec
	$(OBJDUMP) -s $(APP).elf > $(APP).cnt
	$(OBJCOPY) -O binary $(APP).elf $(APP).bin
#	$(OBJCOPY) -O ihex --change-addresses=0x80000000 $(APP).elf $(BIN).hex
	$(SIZE) $(APP).elf

bare_apps:
	for i in $(APP_LIST) ; do \
		$(MAKE) -C ../../bare-metal-apps/platform/virt32 APP=$$i CLEAN=1 clean; \
		$(MAKE) -C ../../bare-metal-apps/platform/virt32 APP=$$i CROSS_COMPILER=$(CROSS_COMPILER) F_CLK=$(F_CLK) FLASH_SIZE=`awk  '$$1=="'$$i'" {print $$2}' include/vms.info` RAM_SIZE=`awk '$$1=="'$$i'" {print $$3}' include/vms.info` DEBUG_GUEST=$(DEBUG_GUEST) \
	;done

make_genconf:
	gcc -o genconf ../cfg_reader/genconf.c -lconfig -DRISC_VIRT

generate_firmware:
	$(shell export BASE_ADDR=0x80000000; ../../scripts/genhex.sh $(APP_LIST))
	
config_vms: make_genconf
	#execute first and exit in case of errors
	./genconf $(CFG_FILE) || (exit 1)
	#execute and export to a makefile variable the ouput of the script
	$(eval APP_LIST:=$(shell ./genconf $(CFG_FILE) || (exit 1)))

start:
	$(HOME)/riscv-tools/qemu-4.2.0/riscv32-softmmu/qemu-system-riscv32 -M virt -nographic -bios firmware.bin -serial mon:stdio &

debug:
	$(HOME)/riscv-tools/qemu-4.2.0/riscv32-softmmu/qemu-system-riscv32 -M virt -icount shift=0 -nographic -bios firmware.bin -serial mon:stdio -s -S &

stop:
	killall qemu-system-riscv32 riscv32-unknown-elf-gdb | true

reload: stop all debug
	gnome-terminal -e "riscv32-unknown-elf-gdb --command gdb_cmd.txt"

clean: config_vms
	rm -f $(APP).* 
	rm -f *.o
	rm -f firmware.hex
	rm -f include/vms.info
	rm -f include/config.h
	rm -f genconf
	
	for i in $(APP_LIST) ; do \
		$(MAKE) -C ../../bare-metal-apps/platform/virt32 APP=$$i CLEAN=1 clean \
	;done

