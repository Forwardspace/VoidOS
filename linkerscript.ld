ENTRY(_start) /* Entry symbol, refer to bootup/boot.asm */

/* Memory sections */
SECTIONS {
	. = 1M; /* Load kernel at 1MB */

	/* Multiboot and text section */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(0x1000)
    	{
        	*(.data)
   	 }

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
