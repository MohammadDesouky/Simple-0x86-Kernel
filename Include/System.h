
#ifndef CU_FOS_OS_SYSTEM
#define CU_FOS_OS_SYSTEM


//Assembly functions
void LoadGDTToProcessor();
void LoadIDTToProcessor();

//GDT.c functions
void InstallGDT();


//IDT.c functiosn
void SetIDTRow(unsigned char RowNumber, unsigned long BaseAddress, unsigned short Selector, unsigned char Flags);
void InstallIDT();
void ZeroTheIDT();

//ISRs.c functions
 void InstallISRs();

//IRQs.c function
 void  InstallIRQs();
 void UninstallIRQHandler(int IRQNumber);

 void Stop();

//UI Draw functions
 void PrintTopBorder();
 void PrintBottomBorder();
 void PrintRightBorder();
 void PrintLeftBorder();
 void PrintVerticalBorder(unsigned Position);
 void PrintHorizontalBorder(unsigned Position);
 void DrawUI();
 void DrawUIBorder();


//Time.c file functions
 void InstallTimer();


//USKeayboard.c file functions

 void InstallKeyBoard();

 void Restart();

//-3 El processor Registers fl el stack
struct regs
{
  unsigned GS, FS, ES, DS,
  	  EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX,
	  InterruptNumber, ErrorCode,
	  EIP, CS, EFalgs, UserESP, SS;
};

 void InstallIRQHandler(int IRQNumber,  void (*handler)(struct regs *R));

#endif
