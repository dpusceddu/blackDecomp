ENTRY(_start)
SECTIONS
{
  . = 0x100000;
  .text : { *(.text) *(.text.*) }
  . = ALIGN(0x40);
  .data : { *(.data) }
  .sdata : { *(.sdata) }
  .bss : { *(.bss) *(COMMON) }
}
