#include <System.h>
#include <Memory.h>
struct IDTRow
{
    unsigned short BaseAddressLow;
    unsigned short Selector;
    unsigned char ReservedAndAlways0;
    unsigned char Flags;
    unsigned short BaseAddressHigh;
}__attribute__((packed));

struct IDTPointer
{
    unsigned short Length;
    unsigned int Address;
}__attribute__((packed));



//256 row mn 0>>>255 elly ma7goz menhom ll processor mn 0>>>31
struct IDTRow IDTTable[256];
struct IDTPointer IDTPointerForCPU;



void SetIDTRow(unsigned char RowNumber, unsigned long BaseAddress, unsigned short Selector, unsigned char Flags)
{

    IDTTable[RowNumber].BaseAddressLow = (unsigned short)BaseAddress & 0xFFFF;
    IDTTable[RowNumber].Selector = Selector;
    IDTTable[RowNumber].ReservedAndAlways0 = 0;
    IDTTable[RowNumber].Flags = Flags;
    IDTTable[RowNumber].BaseAddressHigh = (BaseAddress >> 16) & 0xFFFF;
}

void InstallIDT()
{
    // kol row mn el IDT tolo 8 byte
    unsigned short IDTLength= (sizeof (struct IDTRow) * 256) - 1;

    MemorySetToValueByte(&IDTTable, 0, 256*8);

    IDTPointerForCPU.Length= IDTLength;
    IDTPointerForCPU.Address = (unsigned int)(void *)&IDTTable;

    LoadIDTToProcessor();

}
void ZeroTheIDT()
{
    IDTPointerForCPU.Length= 0;
    IDTPointerForCPU.Address = 0;
}
