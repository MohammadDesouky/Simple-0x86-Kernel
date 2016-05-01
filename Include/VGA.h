#ifndef CU_FOS_OS_VGA
#define CU_FOS_OS_VGA

void PrintStringAndInt(char * s,int x);
void PrintStringPosition(const char *a,unsigned int Position);
void PrintString(const char *a);
void PrintCursorPosition();
void PrintoneNewLine(const char *a);
void ClearScreen();
void MoveCursor();
void OutPutChar(char a);
void PrintChar(char a,unsigned int Position,char Attributes);
void CursorToNextLine();
void  DeleteChar();
void PrintEmptyLine(int LineNumber);
void ScrollScreen();
void PrintStringError(char *s);

#endif
