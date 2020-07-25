OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY{
  ram   (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 32768
}

_stack = ORIGIN(ram) + LENGTH(ram);
_stack_size = 512;

PHDRS{
  text PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
}

SECTIONS{
  .text : {
    PROVIDE(_text_start = .);
    *(.e_entry)
    *(.text.init) *(.text .text.*)
    PROVIDE(_text_end = .);
  } >ram AT>ram :text

  .rodata : {
    . = ALIGN(8);
    PROVIDE(_rodata_start = .);
    *(.rodata .rodata.*)
    PROVIDE(_rodata_end = .);
  } >ram AT>ram :data


  .data : {
    . = ALIGN(8);
    PROVIDE(_data_start = .);
    *(.sdata .sdata.*) *(.data .data.*)
    PROVIDE(_data_end = .);
  } >ram AT>ram :data

  .bss :{
    PROVIDE(_bss_start = .);
    *(.sbss .sbss.*) *(.bss .bss.*)
    PROVIDE(_bss_end = .);
  } >ram AT>ram :bss

  PROVIDE(_memory_start = ORIGIN(ram));
  PROVIDE(_memory_end = ORIGIN(ram) + LENGTH(ram));
}

_end = .;
. = ALIGN(8); 
_heap_start = . ;
_heap_size = LENGTH(ram) - (_heap_start - ORIGIN(ram)) - 8 - _stack_size;
