ENTRY(main)
SECTIONS
{
    /* Set the load address to 1 MiB */
    . = 0x100000;

    /* Text (code) section */
    .text :
    {
        *(.text)
    }

    /* Data section */
    .data :
    {
        *(.data)
    }

    /* Read-only data section */
    .rodata :
    {
        *(.rodata)
    }

    /* BSS section (uninitialized data) */
    .bss :
    {
        *(COMMON)
        *(.bss)
    }
}

