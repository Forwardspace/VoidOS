global enablePaging
enablePaging:
	push ebp
	mov ebp, esp
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	pop ebp
	ret

global disablePaging
disablePaging:
	push ebp
	mov ebp, esp
	mov eax, cr0
	and eax, 0x3FFFFFFF
	mov cr0, eax
	pop ebp
	ret

global setPageDir
setPageDir:
	pop DWORD ebx	; Return address
	pop DWORD eax	; Arg 1
	cli
	mov cr3, eax
	sti
	push ebx
	ret

global ISR14ASM
extern ISR14CPP
extern switchDesc
extern restoreDesc
ISR14ASM:
	pusha
	call switchDesc
	call ISR14CPP
	call restoreDesc
	popa
	iret
