#include <System.h>
#ifndef CU_FOS_OS_RTC
#define CU_FOS_OS_RTC


int IsUpdateLoading();
unsigned char  GetRTCRegister(int reg);
void ReadRTC();
char * GetDateTime();

void InstallCMOSHandler();
void CMOSHandler(struct regs *Registers);
#endif
