#include <System.h>

#ifndef CU_FOS_OS_KEYBOARD
#define CU_FOS_OS_KEYBOARD

void DisableKeyboard();
void EnableKeyboard();
void SetAppReciever(void (* AppReciever)(char *ReadedString));
void InstallKeyBoard();
void KeyboardIHandler(struct regs *r);
void ClearKBBuffer();
#endif
