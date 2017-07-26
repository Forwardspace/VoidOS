; Declare constants for the multiboot header.
MBALIGN  equ  1<<0              ; align loaded modules on page boundaries
MEMINFO  equ  1<<1              ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 4
stack_bottom:
resb 16384 ; 16 KiB
stack_top:

; Call startUp (see boot.cpp) and hangs

section .text
global _start:function (_start.end - _start)s
_start:
	mov esp, stack_top

	push ebx ; Push the multiboot struct

	extern startUp
	call startUp

	cli
	.hang:
		hlt
		jmp .hang
.end:
