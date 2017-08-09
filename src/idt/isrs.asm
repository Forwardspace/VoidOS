desc:
	dd 0

global switchDesc
switchDesc:
	mov ax, ds               ; Lower 16-bits of eax = ds
	mov ebx, desc
	mov [ebx], eax            ; save the data segment descriptor

	mov ax, 0x10  		; load the kernel data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	ret

global restoreDesc
restoreDesc:
	mov eax, [desc]       	 ; reload the original data segment descriptor
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	ret

global loadIDT
loadIDT:
	mov eax, [esp+4]
	lidt [eax]
	ret

extern genericISRCPP
global genericISR
genericISR:
	pusha
	call switchDesc
	call genericISRCPP
	call restoreDesc
	popa
	iret

extern ISR0CPP
global ISR0ASM
ISR0ASM:
	pusha
	call switchDesc
	call ISR0CPP
	call restoreDesc
	popa
	iret

extern ISR1CPP
global ISR1ASM
ISR1ASM:
	pusha
	call switchDesc
	call ISR1CPP
	call restoreDesc
	popa
	iret

extern ISR8CPP
global ISR8ASM
ISR8ASM:
	pop eax
	pusha
	push eax
	call switchDesc
	call ISR8CPP
	call restoreDesc
	popa
	iret

extern ISR13CPP
global ISR13ASM
ISR13ASM:
	pop eax
	pusha
	push eax
	call switchDesc
	call ISR13CPP
	call restoreDesc
	popa
	iret
