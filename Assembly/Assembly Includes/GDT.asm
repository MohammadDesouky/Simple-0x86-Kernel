GLOBAL LoadGDTToProcessor

EXTERN GDTPointerForCPU  ;dh mt3araf gwa el GDT.c


LoadGDTToProcessor:
    LGDT [GDTPointerForCPU]
    MOV AX, 0x10       ;0x10 dh el makan elly feh el data segement gwa el GDT table 0x10 ya3ni 16 bl decimal yan3i el entry el 3 fl global discriptor table ;)
    MOV DS, AX
    MOV ES, AX
    MOV FS, AX
    MOV GS, AX
    MOV SS, AX
    JMP 0x08:JMPToMustFarAfterCR0IntelSaysxD

JMPToMustFarAfterCR0IntelSaysxD:
    RET
