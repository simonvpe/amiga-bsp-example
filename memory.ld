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
	KEEP(*(.font));
	*(.font*)
	__font_end = .;

	bitplane1 = .;
	KEEP(*(.bitplane1*));
	*(.bitplane1*)
	
	bitplane2 = .;
	KEEP(*(.bitplane2*));	
	*(.bitplane2*)

	bitplane3 = .;
	KEEP(*(.bitplane3*));	
	*(.bitplane3*)

	bitplane4 = .;
	KEEP(*(.bitplane4*));	
	*(.bitplane4*)

	bitplane5 = .;
	KEEP(*(.bitplane5*));	
	*(.bitplane5*)

    } >CHIP_RAM

    .bss : {
	KEEP(*(.bss));	
        *(.bss*)
    } >CHIP_RAM
}
