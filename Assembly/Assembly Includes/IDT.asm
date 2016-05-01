
GLOBAL LoadIDTToProcessor

EXTERN IDTPointerForCPU ; dh mt3araf f file IDT.c

LoadIDTToProcessor:
    LIDT [IDTPointerForCPU]; (LIDT) el instruction elly  beha bn3araf el processor fen el IDT fl memory (bysagel hwa el pointer dh f regesiter gwa el CPU esmo IDTR=interrupt discrptor table register )
    RET
