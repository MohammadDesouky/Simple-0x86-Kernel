GLOBAL IRQ0
GLOBAL IRQ1
GLOBAL IRQ2
GLOBAL IRQ3
GLOBAL IRQ4
GLOBAL IRQ5
GLOBAL IRQ6
GLOBAL IRQ7
GLOBAL IRQ8
GLOBAL IRQ9
GLOBAL IRQ10
GLOBAL IRQ11
GLOBAL IRQ12
GLOBAL IRQ13
GLOBAL IRQ14
GLOBAL IRQ15


IRQ0:   				;i'll remap all PIC interrupts starting from 44 not from 0 (note u can use or remap to any number above 31 cuz from 0 to 32 is used by intel (reserved by it))
		
	 
	PUSH 0
    	PUSH 32
    	JMP IRQRoutine


IRQ1:
		
	 
	PUSH 0
    	PUSH 33
	JMP IRQRoutine


IRQ2:
		
	 
	PUSH 0
    	PUSH 34
	JMP IRQRoutine


IRQ3:
		
	 
	PUSH 0
   	PUSH 35
	JMP IRQRoutine


IRQ4:
		
	 
	PUSH 0
   	 PUSH 36
    	JMP IRQRoutine


IRQ5:
		
	 
	PUSH 0
   	 PUSH 37
    	JMP IRQRoutine


IRQ6:
		
	 
	PUSH 0
   	 PUSH 38
    	JMP IRQRoutine


IRQ7:
		
	 
	PUSH 0
   	 PUSH 39
    	JMP IRQRoutine


IRQ8:
		
	 
	PUSH 0
   	 PUSH 40
    	JMP IRQRoutine

IRQ9:
		
	 
	PUSH 0
   	 PUSH 41
    	JMP IRQRoutine

IRQ10:
		
	 
	PUSH 0
   	PUSH 42
    	JMP IRQRoutine

IRQ11:
		
	 
	PUSH 0
   	PUSH 43
    	JMP IRQRoutine

IRQ12:
		
	 
	PUSH 0
   	PUSH 44
    	JMP IRQRoutine

IRQ13:
		
	 
	PUSH 0
   	PUSH 45
    	JMP IRQRoutine

IRQ14:
		
	 
	PUSH 0
    	PUSH 46
	JMP IRQRoutine

IRQ15:
		
	 
	PUSH 0
   	PUSH 47
	JMP IRQRoutine






EXTERN IRQRoutineCFunction      ;mt3arafa f file IRQs.c

IRQRoutine:
    PUSHA
    PUSH DS
    PUSH ES
    PUSH FS
    PUSH GS
    MOV AX, 0x10; el data segment bta3et el data zy ma2olna 2bl kda f file GDT.asm
    MOV DS,AX
    MOV ES,AX
    MOV FS,AX
    MOV GS,AX
    MOV EAX,ESP
    PUSH EAX
    MOV EAX, IRQRoutineCFunction
    CALL EAX
    POP EAX
    POP GS
    POP FS
    POP ES
    POP DS
    POPA
    ADD ESP, 8
    IRET
