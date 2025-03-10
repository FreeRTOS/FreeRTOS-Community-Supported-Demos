MEMORY
{
	ROM : ORIGIN = 0x0, LENGTH = 131072
	OPT : ORIGIN = 0x1010008, LENGTH = 44
	ECCRAM : ORIGIN = 0x20000000, LENGTH = 4096
	RAM : ORIGIN = 0x20004000, LENGTH = 12288
}

EXTERN(vec InterruptVectors ExceptVectors Option_OFS0 Option_OFS1 Option_FPR Option_OSIS init fini Option_SECS Option_AWS Option_UIDS0 Option_UIDS1 Option_UIDS2 Option_UIDS3 preinit_array init_array fini_array)

SECTIONS
{
	.vec 0x0: AT(0x0)
	{
		*/start.o (.text)
	} > ROM

	.vects 0xC0: AT(0xC0)
	{
		KEEP(*(.vects))
	} > ROM

	.nvect 0x1C0: AT(0x1C0)
	{
		KEEP(*(.nvect))
	} > ROM

	.option_ofs0 0x400 : AT(0x400)
	{
		KEEP(*(.option_ofs0))
	} > ROM

	.option_ofs1 0x404 : AT(0x404)
	{
		KEEP(*(.option_ofs1))
	} > ROM

	.option_frp 0x408 : AT(0x408)
	{
		KEEP(*(.option_frp))
	} > ROM

	.option_osis 0x800 : AT(0x800)
	{
		KEEP(*(.option_osis))
	} > ROM

	__mdata = .;

	 .text (ALIGN(. + __romdatacopysize + __romdataeccramcopysize, 256)):
	{
		*(.text)
		*(.text.*)
		/*INPUT_SECTION_FLAGS(SHF_EXECINSTR) *(*_n)*/
	} >ROM AT>ROM

	.init :
	{
		KEEP(*(.init))
	} >ROM

	.fini :
	{
		KEEP(*(.fini))
	} >ROM

	.rodata :
	{
		. = ALIGN(4);
		__rodata = .;
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(4);
		*(.const)
		*(.const.*)

		. = ALIGN(4);
		PROVIDE(__preinit_array_start = .);
		KEEP(*(.preinit_array))
		PROVIDE(__preinit_array_end = .);
		PROVIDE(__init_array_start = .);
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		PROVIDE(__init_array_end = .);
		PROVIDE(__fini_array_start = .);
		KEEP(*(.fini_array))
		KEEP(*(SORT(.fini_array.*)))
		PROVIDE(__fini_array_end = .);	
		__erodata = .;
	}>ROM

	.eh_frame_hdr :
	{
		KEEP(*(.eh_frame_hdr))
	} > ROM

	.eh_frame :
	{
		KEEP(*(.eh_frame))
	} > ROM

	.option_secs 0x1010008 : AT(0x1010008)
	{
		KEEP(*(.option_secs))
	} > OPT

	.option_aws 0x1010010 : AT(0x1010010)
	{
		KEEP(*(.option_aws))
	} > OPT

	.option_uids0 0x1010018 : AT(0x1010018)
	{
		KEEP(*(.option_uids0))
	} > OPT

	.option_uids1 0x1010020 : AT(0x1010020)
	{
		KEEP(*(.option_uids1))
	} > OPT

	.option_uids2 0x1010028 : AT(0x1010028)
	{
		KEEP(*(.option_uids2))
	} > OPT

	.option_uids3 0x1010030 : AT(0x1010030)
	{
		KEEP(*(.option_uids3))
	} > OPT

	.data 0x20004000 : AT(__mdata)
	{
		. = ALIGN(4);
		PROVIDE (__datastart = .);
		__data = .;
        *(.sdata .sdata.*)
		*(.data)
		*(.data.*)
		. = ALIGN(4);
		/*INPUT_SECTION_FLAGS(!SHF_EXECINSTR, SHF_WRITE, SHF_ALLOC) *(*_n)*/
		__edata = .;
	} >RAM

	PROVIDE(__romdatastart = LOADADDR(.data));
	PROVIDE (__romdatacopysize = SIZEOF(.data));

	.data_eccram : AT(LOADADDR(.data)+(__edata - __data))
	{
		PROVIDE( _mdata_eccram = LOADADDR(.data_eccram) );
		. = ALIGN(4);
		PROVIDE (__dataeccramstart = .);
		__data_eccram = .;
		*(.data_eccram)
		*(.data_eccram.*)
		. = ALIGN(4);
		__edata_eccram = .;
	} >ECCRAM

	PROVIDE(__romdataeccramstart = LOADADDR(.data_eccram));
	PROVIDE (__romdataeccramcopysize = SIZEOF(.data_eccram));

	.bss :
	{
		PROVIDE(__bssstart = .);
		. = ALIGN(4);
		__bss = .;
        *(.sbss .sbss.*)
		*(.bss)
		*(.bss.*)
		. = ALIGN(4);
		*(.bss_bit)
		. = ALIGN(4);
		*(COMMON)
		. = ALIGN(4);
		__ebss = .;
		end = .;
	} >RAM AT>RAM
	PROVIDE(__bsssize = SIZEOF(.bss));

	.bss_eccram (NOLOAD) :
	{
		. = ALIGN(4);
		__bss_eccram = .;
		*(.bss_eccram)
		*(.bss_eccram.**)
		. = ALIGN(4);
		__ebss_eccram = .;
	} >ECCRAM

	PROVIDE(__stack_size = 0x800);
	.stack 0x20006FFC (NOLOAD) : AT(0x20006FFC)
	{
		PROVIDE(__stack = .);
		ASSERT((__stack > (end + __stack_size)), "Error: Too much data - no room left for the stack");
	} >RAM

    /DISCARD/ :
	{
		*(.note)
		*(.note.*)
		*(.gnu.warning*)
	}
}
