
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256K
  SRAM  (wr) : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
  __IRQ_TABLE_SIZE__         = 0x150;
  __gnuld_flash_load_start__ = 0x08000000;
  __gnuld_flash_load_end__   = 0x08040000;
  __gnuld_sram_load_start__  = 0x20000000;
  __gnuld_sram_load_end__    = 0x20010000;
  __gnuld_stack_top__        = __gnuld_sram_load_end__ - 4;
  __gnuld_stack_bottom__     = __gnuld_sram_load_start__ + (0x10000 / 2);

  __irq_table_load_start__ = ALIGN(__gnuld_flash_load_start__, 4);
  .irq_table __irq_table_load_start__ :
  {
    KEEP(*(.irq_table))
  } > FLASH
  __irq_table_load_end__ = .;
  . = ASSERT (SIZEOF(.irq_table) == __IRQ_TABLE_SIZE__, "error: irq table is wrong mofo.");

  __gnuld_code_load_start__ = ALIGN(__irq_table_load_end__, 4);
  .text __gnuld_code_load_start__ :
  {
    *(.text)
    *(.text*)
    *(.rodata)
    *(.rodata*)
    *(.glu_7)
    *(.glu_7t)
    *(.eh_frame)
    KEEP(*(.init))
    KEEP(*(.fini))
    _etext = .;
    _exit = .;
  } > FLASH
  __gnuld_code_load_end__ = .;
  . = ASSERT (__gnuld_code_load_end__ >= __gnuld_flash_load_start__ &&
              __gnuld_code_load_end__ < __gnuld_flash_load_end__,
              "error: .text cannot fit into FLASH memory.");

  __gnuld_data_start__ = ALIGN(__gnuld_code_load_end__, 4);
  .data : AT ( __gnuld_data_start__ )
  {
    __gnuld_data_load_start__ = .;
    *(.data)
    *(.data*)
    __gnuld_data_load_end__ = ALIGN(., 4);
  } > SRAM
  __gnuld_data_end__ = ALIGN(., 4);
  __gnuld_data_size__ = SIZEOF(.data);
  . = ASSERT (SIZEOF(.data) < (0x8000),
      "error: .data size cannot fit into SRAM.");

  .bss ALIGN(__gnuld_data_load_end__, 4) :
  {
    __gnuld_bss_load_start__ = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __gnuld_bss_load_end__ = ALIGN(., 4);
  } > SRAM
  __gnuld_bss_size__ = SIZEOF(.bss);
  . = ASSERT (__gnuld_bss_load_end__ >= __gnuld_sram_load_start__ &&
      __gnuld_bss_load_end__ < __gnuld_sram_load_end__,
      "error: .bss size cannot fit into SRAM.");

  /DISCARD/ :
  {
    *(.ARM.exidx)
    *(.comment)
    *(.ARM.attributes)
  }
}
