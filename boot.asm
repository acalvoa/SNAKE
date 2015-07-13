[ORG 0x7c00]
[BITS 16]
	JMP boot
	WELCOME DB "Loading System",0x0A,0x0D,0x00
boot:
	; DEFINIMOS EL MODO DE VIDEO
    
    MOV BX,WELCOME
    CALL print
    ;ESCRIBIMOS EL COMIENZO DEL KERNEL
    ; JMP load_kernel

load_kernel:	
	  MOV 	BP , 0xFFFF
	  MOV 	SP , BP	
    CALL 	disk_load
	  JMP 	kernel_offset
    JMP   $
disk_load:
	MOV 	AH,0x02 	; BIOS read sector function
	MOV 	AL,23		; Read DH sectors
	MOV 	CH,0x00 	; Select cylinder 0
	MOV 	DH,0x00 	; Select head 0
	MOV 	CL,0x02 	; Start reading from second sector ( i.e.
						; after the boot sector )

	MOV 	BX, 0
	MOV 	ES, BX
	MOV 	BX, kernel_offset

	INT 	0x13 		; BIOS interrupt
	JC 		disk_error 	; Jump if error ( i.e. carry flag set )
	RET
disk_error:
	MOV 	BX,DISK_ERROR_MSG
	CALL  print
  JMP 	$
	DISK_ERROR_MSG db " Disk read error !",0
print:
	PUSHA
	MOV AH,0Eh
.repeat_print:
	MOV	AL,[BX]
	CMP	AL,0
	JE	.end_print
	INT 0x10
	ADD	BX,1
	JMP	.repeat_print
.end_print:
	POPA
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FIRMA DE BOTEO
times 510 -($-$$) db 0
dw 0xaa55
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; FIN DEL SECTOR 1, COMENZAMOS CON EL SECTOR 2
kernel_offset: