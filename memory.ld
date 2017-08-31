MEMORY
{
    CHIP_RAM (rx) : ORIGIN = 0x00000000, LENGTH = 0x07FFFF
}

SECTIONS {
    .text : {
        KEEP(*(CODE*));
        *(CODE*)
	KEEP(*(.text));
        *(.text*)
	/* .rodata is not moved by ploink script
           so we are required to place it in .text */
	KEEP(*(.rodata));
	*(.rodata*)
    } >CHIP_RAM

    .data : {
	KEEP(*(.data));	
        *(.data*)
	__font_start = .;
	*(.font*)
	__font_end = .;
    } >CHIP_RAM

    .bss : {
	KEEP(*(.bss));	
        *(.bss*)
    } >CHIP_RAM
}
