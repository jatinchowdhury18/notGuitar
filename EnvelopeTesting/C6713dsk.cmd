/*C6713dsk.cmd  Linker command file*/

MEMORY
{
  IVECS:    org=0h,  		len=0x220
  IRAM:		org=0x00000220,	len=0x0002FDE0 /*internal memory*/
  SDRAM:	org=0x80000000, len=0x00100000 /*external memory*/
  FLASH:	org=0x90000000, len=0x00020000 /*flash memory*/                    
}

SECTIONS
{
  .EXT_RAM :> SDRAM
  .vecs	   :> IVECS	/*in vector file*/
  .text    :> IRAM	/*Created by C Compiler*/
  .bss     :> IRAM
  .cinit   :> IRAM
  .stack   :> IRAM
  .sysmem  :> IRAM
  .const   :> IRAM
  .switch  :> IRAM
  .far     :> IRAM
  .cio     :> IRAM
  .csldata :> IRAM
}