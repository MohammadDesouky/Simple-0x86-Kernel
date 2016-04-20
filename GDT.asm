DefinitionStart:

NullDiscriptor:
    dd 0x0
    dd 0x0

CodeDiscriptor:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

DataDiscriptor:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

DefinitionEnd:


GDTDiscriptorPointers:

    dw DefinitionEnd - DefinitionStart - 1
    dd DefinitionStart

CodeSegment equ CodeDiscriptor - DefinitionStart
DataSegment equ DataDiscriptor - DefinitionStart

