;Used for calling contructors and destructors

section .init
	pop ebp
	ret

section .fini
	pop ebp
	ret
