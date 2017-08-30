MEMORY
{
    CHIP_RAM (rx) : ORIGIN = 0x00000000, LENGTH = 0x07FFFF
}

SECTIONS {
    .text : {
        __text_start = .;
	KEEP(*(.startup_code*));
	*(.startup_code*)
	KEEP(*(.text));
        *(.text*)
	/* .rodata is not moved by ploink script
           so we are required to place it in .text */
	KEEP(*(.rodata));
	*(.rodata*)
        __text_end = .;
    } >CHIP_RAM

    .data : {
        __data_start = .;
	KEEP(*(.data));	
        *(.data*)
        __data_end = .;
    } >CHIP_RAM

    .bss : {
        __bss_start = .;
	KEEP(*(.bss));	
        *(.bss*)
        __bss_end = .;
    } >CHIP_RAM
}
