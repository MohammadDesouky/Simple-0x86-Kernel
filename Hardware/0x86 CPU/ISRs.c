#include <System.h>
#include <VGA.h>
#include <IO.h>
extern void  ISR0();
extern void  ISR1();
extern void  ISR2();
extern void  ISR3();
extern void  ISR4();
extern void  ISR5();
extern void  ISR6();
extern void  ISR7();
extern void  ISR8();
extern void  ISR9();
extern void  ISR10();
extern void  ISR11();
extern void  ISR12();
extern void  ISR13();
extern void  ISR14();
extern void  ISR15();
extern void  ISR16();
extern void  ISR17();
extern void  ISR18();
extern void  ISR19();
extern void  ISR20();
extern void  ISR21();
extern void  ISR22();
extern void  ISR23();
extern void  ISR24();
extern void  ISR25();
extern void  ISR26();
extern void  ISR27();
extern void  ISR28();
extern void  ISR29();
extern void  ISR30();
extern void  ISR31();


//zy el GDT el IDT leh bardo structure lazem tb2a 3arfha el 0x8E el flags kol bit leh ma3na
//awel 32 entry el handler bta3hom 3andena hwa el isr 0,1,2,... >>>> bel tarteb
//el string elly el mafrod ntba3ha lamma el exception ygy mn 0>>31 mawgooda ta7t
void InstallISRs()
{
    //lazem n3arafhom bl tare2a el 3'abya d 3ashan mafesh loop b esm el functions :D ISR0,ISR1,....
    //ClearScreen();

    SetIDTRow(0,(unsigned long)(void(*)) &ISR0, 0x0008, 0x8E);
    SetIDTRow(1,(unsigned long)(void(*)) &ISR1, 0x0008, 0x8E);
    SetIDTRow(2,(unsigned long)(void(*)) &ISR2, 0x0008, 0x8E);
    SetIDTRow(3,(unsigned long)(void(*)) &ISR3, 0x0008, 0x8E);
    SetIDTRow(4,(unsigned long)(void(*)) &ISR4, 0x0008, 0x8E);
    SetIDTRow(5,(unsigned long)(void(*)) &ISR5, 0x0008, 0x8E);
    SetIDTRow(6,(unsigned long)(void(*)) &ISR6, 0x0008, 0x8E);
    SetIDTRow(7,(unsigned long)(void(*)) &ISR7, 0x0008, 0x8E);

    SetIDTRow(8,(unsigned long)(void(*))  &ISR8, 0x0008, 0x8E);
    SetIDTRow(9,(unsigned long)(void(*)) 	&ISR9, 0x0008, 0x8E);
    SetIDTRow(10,(unsigned long)(void(*)) &ISR10, 0x0008, 0x8E);
    SetIDTRow(11,(unsigned long)(void(*)) &ISR11, 0x0008, 0x8E);
    SetIDTRow(12,(unsigned long)(void(*)) &ISR12, 0x0008, 0x8E);
    SetIDTRow(13,(unsigned long)(void(*)) &ISR13, 0x0008, 0x8E);
    SetIDTRow(14,(unsigned long)(void(*)) &ISR14, 0x0008, 0x8E);
    SetIDTRow(15,(unsigned long)(void(*)) &ISR15, 0x0008, 0x8E);

    SetIDTRow(16,(unsigned long)(void(*)) &ISR16, 0x0008, 0x8E);
    SetIDTRow(17,(unsigned long)(void(*)) &ISR17, 0x0008, 0x8E);
    SetIDTRow(18,(unsigned long)(void(*)) &ISR18, 0x0008, 0x8E);
    SetIDTRow(19,(unsigned long)(void(*)) &ISR19, 0x0008, 0x8E);
    SetIDTRow(20,(unsigned long)(void(*)) &ISR20, 0x0008, 0x8E);
    SetIDTRow(21,(unsigned long)(void(*)) &ISR21, 0x0008, 0x8E);
    SetIDTRow(22,(unsigned long)(void(*)) &ISR22, 0x0008, 0x8E);
    SetIDTRow(23,(unsigned long)(void(*)) &ISR23, 0x0008, 0x8E);

    SetIDTRow(24,(unsigned long)(void(*)) &ISR24, 0x0008, 0x8E);
    SetIDTRow(25,(unsigned long)(void(*)) &ISR25, 0x0008, 0x8E);
    SetIDTRow(26,(unsigned long)(void(*)) &ISR26, 0x0008, 0x8E);
    SetIDTRow(27,(unsigned long)(void(*)) &ISR27, 0x0008, 0x8E);
    SetIDTRow(28,(unsigned long)(void(*)) &ISR28, 0x0008, 0x8E);
    SetIDTRow(29,(unsigned long)(void(*)) &ISR29, 0x0008, 0x8E);
    SetIDTRow(30,(unsigned long)(void(*)) &ISR30, 0x0008, 0x8E);
    SetIDTRow(31,(unsigned long)(void(*)) &ISR31, 0x0008, 0x8E);

}


const char *ExceptionMessagesArray[] =
{
    "\nDivision By Zero\0",
    "\nDebug\0",
    "\nNon Maskable Interrupt\0",
    "\nBreakpoint\0",
    "\nInto Detected Overflow\0",
    "\nOut of Bounds\0",
    "\nInvalid Opcode\0",
    "\nNo Coprocessor\0",

    "\nDouble Fault\0",
    "\nCoprocessor Segment Overrun\0",
    "\nBad TSS\0",
    "\nSegment Not Present\0",
    "\nStack Fault\0",
    "\nGeneral Protection Fault\0",
    "\nPage Fault\0",
    "\nUnknown Interrupt\0",

    "\nCoprocessor Fault\0",
    "\nAlignment Check\0",
    "\nMachine Check\0",
    "\nReserved 1\0",
    "\nReserved 2\0",
    "\nReserved 3\0",
    "\nReserved 4\0",
    "\nReserved 5\0",
    "\nReserved 6\0",
    "\nReserved 7\0",
    "\nReserved 8\0",
    "\nReserved 9\0",
    "\nReserved 10\0",
    "\nReserved 11\0",
    "\nReserved 12\0",
    "\nReserved 13\0"
};


void ISRRoutineCFunction(struct regs *R)// el function d bnadeha m el assembly bsabab en feh instruction esmaha iret el compiler msh bynafezha lmma el function bt5las bynafez ret instruction w d msh bt3ml pop ll resgisters m el stack
{

    if (R->InterruptNumber < 32)//int_no
    {
        PrintString(ExceptionMessagesArray[R->InterruptNumber]);
        //PrintString("\nException. System Halted!\n\0");
         if (R->InterruptNumber >= 40)
	    {
	 	//bn2ol ll PIC el slave en el interrupt 5alas ethandle eb3at elly ba3do aw delwa2ty aw ba3den t2dar tb3at elly ba3do
		 SendByteToPort(0xA0, 0x20);
	    }

	    //bn2ol ll PIC el master en el interrupt 5alas ethandle eb3at elly ba3do aw delwa2ty aw ba3den t2dar tb3at elly ba3do
	    SendByteToPort(0x20, 0x20);//for (;;);//infinte loop ^_^ not really halt
    }
}
