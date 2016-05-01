#include <System.h>
#include <VGA.h>
#include <RTC.h>
#include <Apps.Main.h>
void KernelMain() //d el function elly nadenaha mn file el assembly bta3 el entry point
{


	__asm__ __volatile__ ("CLI");
	ClearScreen();
	PrintString("CU FOS OS Kernel Called From Bootloader\0");
  PrintString("\nInterrupts was disabled untill initialization\nInitialization Starts...\0");
	PrintString("\nGDT (Global Discriptor Table) [Boot Loader Loaded Our GDT]");
  PrintString("\nLoading IDT(Interrupt Discriptor Table)...\0");
	InstallIDT();
	PrintString("\nIDT Loaded Successfully!\0");
	PrintString("\nFilling the ISRs (Interrupt Service Routines)...\0");
	InstallISRs();
	PrintString("\nISRs Filled Successfully!\0");
	PrintString("\nFilling the IRQs (Interrupt Requests Handlers)...\0");
	InstallIRQs();
	InstallTimer();
 	InstallKeyBoard();
	InstallCMOSHandler();
	PrintString("\nIRQs Filled Successfully!\0");
	PrintString("\nEnabling Interrupts...\0");
	__asm__ __volatile__ ("STI");
	PrintString("\nInterrupts Enabled\0");
	PrintString("\nIntialization Done\nCU FOS OS is Ready!\0");
	StartAppMain();
	for(;;);

}
