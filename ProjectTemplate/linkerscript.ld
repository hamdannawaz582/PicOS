ENTRY(main)
SECTIONS {
	. = 0x0;

	.text : ALIGN(2){
		*(.text*)
	}

	.rodata : ALIGN(2){
		*(.rodata*)
	}

	.data : ALIGN(2){
		*(.data*)
	}

	.bss : ALIGN(2){
		*(.bss*)
	}
}
