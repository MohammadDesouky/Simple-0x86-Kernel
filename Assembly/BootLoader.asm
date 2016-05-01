[BITS 16]
[ORG 0x7C00]

mov [DriveNumberWhereBIOSLoadedUs],dl;بعد ما البيوس بيحمل البوتلوودر بيبقى مخزن رقم الدرايف فى ال دي ال  ريجستر  الامر ده احنا بنحفظ بيه
		     ;بنحفظ بيه رقم الدرايف فى مكان فى الميموري عشان احنا هنتسخدم ال دي ال وهنغير القيمة اللى فيه

CALL LoadKernel

CALL ToPM


JMP $ 		;   الامر ده معناه "نفذ الامر اللى فى المكان ده - الل احنا فيه-" ده بيعمل لوووب مبتخلصش انفنيت لووب



ToPM:
	CLI
	LGDT [GDTDiscriptorPointers]

	mov EBX, cr0
	or EBX, 1
	mov cr0,EBX
	jmp 0x08:PMStart


LoadKernel:
	xor ax,ax
	MOV ES,AX
	mov bx,WhereKernelWillBeLoaded
	mov ah,0x02
	mov al,0x20  ;load 32 SECTOR 16 KiB
	mov ch,0
	mov DH,0
	mov cl,2  ;start from second sector

	mov dl,[DriveNumberWhereBIOSLoadedUs]
	int 0x13
	ret






DriveNumberWhereBIOSLoadedUs : db 0

WhereKernelWillBeLoaded equ 0x2000


%include 'Assembly/Assembly Includes/BootLoaderGDT.asm'

[bits 32]
PMStart:
	mov ax, 0x10 ; Now we are in protected mode , our old segments are meaningless ,

	mov ds, ax		  ; so we point our segment registers to the

	mov ss, ax
					  ; data selector we defined in our GDT
	mov es, ax

	mov fs, ax

	mov gs, ax

  	;CALL EnableA20Asm     ; A20 : A20 dh 3obara 3an line lazem t5aleh enabled 3ashan t3raf t access el memory kolaha
											 ;7aga kda 3ashan el gded lazem yb2a compatable m3a el adee

	mov ebp, 0x9000         ; Updating stack position so that it is right at the top of free space.
	mov esp, ebp             ; create stack frame(MOV DST, SRC : Stackpointer <----- Basepointer)


	JMP WhereKernelWillBeLoaded
	JMP $

EnableA20Asm:
	in al, 0x92
	or al, 2
	out 0x92, al
	ret

TIMES 510-($-$$) DB 0
DW 0xAA55
