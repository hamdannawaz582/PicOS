MEMORY {
    FLASH(rx) : ORIGIN = 0x10000000, LENGTH = 2048k
    RAM(rwx) : ORIGIN = 0x20000000, LENGTH = 256k
}

ENTRY(kinit)

SECTIONS {
    _sptr = ORIGIN(RAM) + LENGTH(RAM);
    _dummy = .;

    .flash_begin : {
        __flash_binary_start = .;
    } > FLASH

    .boot2 : {
        __boot2_start__ = .;
        KEEP (*(.boot2))
        __boot2_end__ = .;
    } > FLASH

    ASSERT(__boot2_end__ - __boot2_start__ == 0x100,
        "ERROR: Pico second stage bootloader must be 256 bytes in size")

    .text : {
        KEEP (*(.vtable))
        KEEP (*(.binary_info_header))
        . = . + 0x100;
        KEEP (*(.reset))
    } > FLASH

    .rodata : {
        . = ALIGN(4);
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    .data : {
        __data_start__ = .;
        *(.data*)
        . = ALIGN(4);
        __data_end__ = .;
    } > RAM AT> FLASH

    .bss : {
        . = ALIGN(4);
        __bss_start = .;
        *(SORT_BY_ALIGNMENT(SORT_BY_NAME(.bss*)))
        *(COMMON)
        . = ALIGN(4);
        __bss_end__ = .;
    } > RAM
}