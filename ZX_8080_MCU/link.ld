MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    RAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 64K
}

SECTIONS
{
    /* The Entry Point (where the CPU starts) */
    .text :
    {
        *(.text)
        *(.text.*)
    } > FLASH

    .rodata :
    {
        *(.rodata)
        *(.rodata.*)
    } > FLASH

    .data :
    {
        *(.data)
        *(.data.*)
    } > RAM AT > FLASH

    .bss :
    {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    } > RAM
}
