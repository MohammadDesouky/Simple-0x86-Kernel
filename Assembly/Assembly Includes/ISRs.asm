GLOBAL ISR0
GLOBAL ISR1
GLOBAL ISR2
GLOBAL ISR3
GLOBAL ISR4
GLOBAL ISR5
GLOBAL ISR6
GLOBAL ISR7
GLOBAL ISR8
GLOBAL ISR9
GLOBAL ISR10
GLOBAL ISR11
GLOBAL ISR12
GLOBAL ISR13
GLOBAL ISR14
GLOBAL ISR15
GLOBAL ISR16
GLOBAL ISR17
GLOBAL ISR18
GLOBAL ISR19
GLOBAL ISR20
GLOBAL ISR21
GLOBAL ISR22
GLOBAL ISR23
GLOBAL ISR24
GLOBAL ISR25
GLOBAL ISR26
GLOBAL ISR27
GLOBAL ISR28
GLOBAL ISR29
GLOBAL ISR30
GLOBAL ISR31




ISR0:
CLI


    PUSH 0
    PUSH 0
    JMP ISRRoutine

;  1: Debug Exception
ISR1:
CLI


    PUSH 0
    PUSH 1
    JMP ISRRoutine

;  2: Non Maskable Interrupt Exception
ISR2:
CLI


	PUSH 0
    PUSH 2
    JMP ISRRoutine

;  3: Int 3 Exception
ISR3:
CLI



	PUSH 0
    PUSH 3
    JMP ISRRoutine

;  4: INTO Exception
ISR4:
	CLI


	PUSH 0
    PUSH 4
    JMP ISRRoutine

;  5: Out of Bounds Exception
ISR5:
	CLI


	PUSH 0
    PUSH 5
    JMP ISRRoutine

;  6: Invalid Opcode Exception
ISR6:
   
            CLI


PUSH 0
    PUSH 6
    JMP ISRRoutine

;  7: Coprocessor Not Available Exception
ISR7:
       CLI


PUSH 0
    PUSH 7
    JMP ISRRoutine

;  8: Double Fault Exception (With Error Code!)
ISR8:
       CLI


    PUSH 8
    JMP ISRRoutine

;  9: Coprocessor Segment Overrun Exception
ISR9:
   
     CLI


	PUSH 0
    PUSH 9
    JMP ISRRoutine

; 10: Bad TSS Exception (With Error Code!)
ISR10:
       CLI


    PUSH 10
    JMP ISRRoutine

; 11: Segment Not Present Exception (With Error Code!)
ISR11:
       CLI


    PUSH 11
    JMP ISRRoutine

; 12: Stack Fault Exception (With Error Code!)
ISR12:   
    CLI


    PUSH 12
    JMP ISRRoutine

; 13: General Protection Fault Exception (With Error Code!)
ISR13:
       CLI


    PUSH 13
    JMP ISRRoutine

; 14: Page Fault Exception (With Error Code!)
ISR14:
     CLI


    PUSH 14
    JMP ISRRoutine

; 15: Reserved Exception
ISR15:
	CLI


	PUSH 0
    PUSH 15
    JMP ISRRoutine

; 16: Floating Point Exception
ISR16:
   
     	CLI


	PUSH 0
    PUSH 16
    JMP ISRRoutine

; 17: Alignment Check Exception
ISR17:
	CLI


	PUSH 0
    PUSH 17
    JMP ISRRoutine

; 18: Machine Check Exception
ISR18:
	CLI


	PUSH 0
    PUSH 18
    JMP ISRRoutine

; 19: Reserved
ISR19:
	CLI


	PUSH 0
    PUSH 19
    JMP ISRRoutine

; 20: Reserved
ISR20:
   
     	CLI


	PUSH 0
    PUSH 20
    JMP ISRRoutine

; 21: Reserved
ISR21:
	CLI


	PUSH 0
    PUSH 21
    JMP ISRRoutine

; 22: Reserved
ISR22:
   
	CLI


	PUSH 0
    PUSH 22
    JMP ISRRoutine

; 23: Reserved
ISR23:
	CLI


	PUSH 0
    PUSH 23
    JMP ISRRoutine

; 24: Reserved
ISR24:
	CLI


	PUSH 0
    PUSH 24
    JMP ISRRoutine

; 25: Reserved
ISR25:
   
    	CLI


	PUSH 0t
    PUSH 25
    JMP ISRRoutine

; 26: Reserved
ISR26:
	CLI


	PUSH 0
    PUSH 26
    JMP ISRRoutine

; 27: Reserved
ISR27:
   
	CLI


	PUSH 0
    PUSH 27
    JMP ISRRoutine

; 28: Reserved
ISR28:
	CLI


	PUSH 0
PUSH 28
    JMP ISRRoutine

; 29: Reserved
ISR29:
   
     CLI


	PUSH 0
    PUSH 29
    JMP ISRRoutine

		; 30: Reserved
ISR30:
	CLI


	PUSH 0
    PUSH 30
    JMP ISRRoutine

; 31: Reserved
ISR31:
	CLI


	PUSH 0
    PUSH 31
    JMP ISRRoutine





EXTERN ISRRoutineCFunction ; w D mt3arafa f file ISRs.c

ISRRoutine:
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
    MOV EAX, ISRRoutineCFunction; e3tberha  Exception handler elly bthandl kol el exception mn 0 l7ad 31 w dol elly 7agezhom el processor 3ashan el exceptions
    CALL EAX
    POP EAX
    POP GS
    POP FS
    POP ES
    POP DS
    POPA
    ADD ESP, 8
 
    IRET
