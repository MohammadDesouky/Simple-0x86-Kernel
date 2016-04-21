[BITS 16]	
[ORG 0x7C00]	
 
mov [DriveNumberWhereBIOSLoadedUs],dl;بعد ما البيوس بيحمل البوتلوودر بيبقى مخزن رقم الدرايف فى ال دي ال  ريجستر  الامر ده احنا بنحفظ بيه
		     ;بنحفظ بيه رقم الدرايف فى مكان فى الميموري عشان احنا هنتسخدم ال دي ال وهنغير القيمة اللى فيه 	

CALL LoadKernel 

CALL ToPM


JMP $ 		;   الامر ده معناه "نفذ الامر اللى فى المكان ده - الل احنا فيه-" ده بيعمل لوووب مبتخلصش انفنيت لووب



ToPM:
	cli
	lgdt [GDTDiscriptorPointers]
	
	mov EBX, cr0
	or EBX, 1
	mov cr0,EBX
	jmp 08h:PMStart 


LoadKernel:
	xor ax,ax
	MOV ES,AX
	mov bx,WhereKernelWillBeLoaded
	mov ah,0x02
	mov al,0x10  ;load 16 SECTOR
	mov ch,0
	mov DH,0
	mov cl,2  ;start from second sector

	mov dl,[DriveNumberWhereBIOSLoadedUs]
	int 0x13
	ret



	
EnterPMode: ; set bit 0 in CR0-go to pmode
	cli
	mov	eax, cr0			
	or	eax, 1
	mov	cr0, eax
	sti
	ret


	
DriveNumberWhereBIOSLoadedUs : db 0
	
WhereKernelWillBeLoaded equ 0x1000


%include 'Assembly/GDT.asm'

[bits 32]
PMStart:
	
	mov ax, DataSegment ; Now we are in protected mode , our old segments are meaningless ,
	
	mov ds, ax		  ; so we point our segment registers to the
	
	mov ss, ax
					  ; data selector we defined in our GDT
	mov es, ax

	mov fs, ax
	
	mov gs, ax


	mov ebp, 0x9000         ; Updating stack position so that it is right at the top of free space.
	mov esp, ebp             ; create stack frame(MOV DST, SRC : Stackpointer <----- Basepointer)

	
	JMP WhereKernelWillBeLoaded
	

TIMES 510-($-$$) DB 0
DW 0xAA55
