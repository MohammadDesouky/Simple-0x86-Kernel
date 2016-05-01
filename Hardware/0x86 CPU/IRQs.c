#include <System.h>
#include <IO.h>


extern void IRQ0();
extern void IRQ1();
extern void IRQ2();
extern void IRQ3();
extern void IRQ4();
extern void IRQ5();
extern void IRQ6();
extern void IRQ7();
extern void IRQ8();
extern void IRQ9();
extern void IRQ10();
extern void IRQ11();
extern void IRQ12();
extern void IRQ13();
extern void IRQ14();
extern void IRQ15();

void * IRQFunctions[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,//first PIC
    0, 0, 0, 0, 0, 0, 0, 0//second PIC ^_^
};

void InstallIRQHandler(int IRQNumber, void (*handler)(struct regs *R))
{
    IRQFunctions [IRQNumber]= handler;
}

void UninstallIRQHandler(int IRQNumber)
{
    IRQFunctions[IRQNumber] = 0;
}


void RemapPICIRQs()
{
 unsigned char a1, a2;
    a1=ReadByteFromPort(0x21);
    a2=ReadByteFromPort(0xA1);
    SendByteToPort(0x20, 0x11);
    SendByteToPort(0xA0, 0x11);
    SendByteToPort(0x21, 0x20);//han3ml redirect badal mn 0 hayb2a mn 32
    SendByteToPort(0xA1, 0x28);// w badal mn 8 hayb2a 52 ^_^
    SendByteToPort(0x21, 0x04);
    SendByteToPort(0xA1, 0x02);
    SendByteToPort(0x21, 0x01);
    SendByteToPort(0xA1, 0x01);
    SendByteToPort(0x21, a1);
    SendByteToPort(0xA1, a2);
}


void InstallIRQs()
{
    RemapPICIRQs();
    SetIDTRow(32,(unsigned int)(void(*)) &IRQ0, 0x0008, 0x8E);
    SetIDTRow(33,(unsigned int)(void(*)) &IRQ1, 0x0008, 0x8E);
    SetIDTRow(34,(unsigned int)(void(*)) &IRQ2, 0x0008, 0x8E);
    SetIDTRow(35,(unsigned int)(void(*)) &IRQ3, 0x0008, 0x8E);
    SetIDTRow(36,(unsigned int)(void(*)) &IRQ4, 0x0008, 0x8E);
    SetIDTRow(37,(unsigned int)(void(*)) &IRQ5, 0x0008, 0x8E);
    SetIDTRow(38,(unsigned int)(void(*)) &IRQ6, 0x0008, 0x8E);
    SetIDTRow(39,(unsigned int)(void(*)) &IRQ7, 0x0008, 0x8E);

    SetIDTRow(40,(unsigned int)(void(*)) &IRQ8,  0x0008, 0x8E);
    SetIDTRow(41,(unsigned int)(void(*)) &IRQ9,  0x0008, 0x8E);
    SetIDTRow(42,(unsigned int)(void(*)) &IRQ10, 0x0008, 0x8E);
    SetIDTRow(43,(unsigned int)(void(*)) &IRQ11, 0x0008, 0x8E);
    SetIDTRow(44,(unsigned int)(void(*)) &IRQ12, 0x0008, 0x8E);
    SetIDTRow(45,(unsigned int)(void(*)) &IRQ13, 0x0008, 0x8E);
    SetIDTRow(46,(unsigned int)(void(*)) &IRQ14, 0x0008, 0x8E);
    SetIDTRow(47,(unsigned int)(void(*)) &IRQ15, 0x0008, 0x8E);

}


void IRQRoutineCFunction(struct regs *R)
{

    void (*handler)(struct regs *R);
    unsigned short interrupt=R->InterruptNumber - 32;
    handler = IRQFunctions[interrupt];
    if (handler)
    {
	     handler(R);
    }
    //2ol ll PIC enna 5alasna hat elly ba3do :P :D
    if (interrupt >= 8)
    {
    	//bn2ol ll PIC el slave en el interrupt 5alas ethandle eb3at elly ba3do aw delwa2ty aw ba3den t2dar tb3at elly ba3do
        SendByteToPort(0xA0, 0x20);
    }

    //bn2ol ll PIC el master en el interrupt 5alas ethandle eb3at elly ba3do aw delwa2ty aw ba3den t2dar tb3at elly ba3do
    SendByteToPort(0x20, 0x20);
}
