#include <System.h>
#include <IO.h>
struct OneGDTRow
{
    unsigned short LimitLow;
    unsigned short BaseAddressLow;
    unsigned char BaseAddressMiddle;
    unsigned char Access;
    unsigned char Granularity;
    unsigned char BaseAddressHigh;
}__attribute__((packed)); //3ashan tmna3 el compile mn el optimization

struct GDTPointer
{
    unsigned short Length;
    unsigned int BaseAddress;
}__attribute__((packed));

//han3araf el GDT table bta3na feh 3 rows bas, Note: momken t3araf l7ad 8192 row
//d a2al 7aga 3ashan el simplicity

struct OneGDTRow GDTTable[3];
struct GDTPointer GDTPointerForCPU;

//mt3arafa f file el assembly GDT.asm


//this method will set the row of a GDT table entry
void SetTheGDTRow(int RowNumber, unsigned long BaseAddress, unsigned long MemoryLimit, unsigned char Access, unsigned char Granularity)
{
    GDTTable[RowNumber].BaseAddressLow = (BaseAddress & 0xFFFF);

    GDTTable[RowNumber].BaseAddressMiddle = (BaseAddress >> 16) & 0xFF;
    GDTTable[RowNumber].BaseAddressHigh = (BaseAddress >> 24) & 0xFF;
    GDTTable[RowNumber].LimitLow = (MemoryLimit & 0xFFFF);
    GDTTable[RowNumber].Granularity = ((MemoryLimit >> 16) & 0x0F);
    GDTTable[RowNumber].Granularity|=(Granularity & 0xF0);

    GDTTable[RowNumber].Access = Access;
};

//d hanadeha m el kernel 3ashan n3ml setup ll GDT isA ya3ni ^_^
void InstallGDT()
{


    //bngeb el tool bta3 el GDT

    GDTPointerForCPU.Length = (unsigned short)((sizeof(struct OneGDTRow) * 3) - 1);///na2s wa7ed 3ashan el bytes btba2 mn el 0 (zero-based)
    GDTPointerForCPU.BaseAddress = (unsigned int)(GDTTable[0].LimitLow);

    // null row lazem yb2a fl GDT, hwa kda el CPU by2olak lazem yb2a null 7atta law feh data maynf3sh tsta5demo (hardware byfred 3alek kda ^_^)


     SetTheGDTRow(0, 0, 0, 0, 0);

    // el structrue bta3et el GDT lazem tb2a 3arefha b el tafseel el 9A wel CF dol kol bit fehom leh ma3na refere ll GDT
    SetTheGDTRow(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);//dh row ll code
    SetTheGDTRow(2, 0, 0xFFFFFFFF, 0x92, 0xCF);//w dh row ll DATA

    LoadGDTToProcessor();
};
