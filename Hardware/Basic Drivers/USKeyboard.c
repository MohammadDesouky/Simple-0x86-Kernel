#include <Keyboard.h>
#include <System.h>
#include <VGA.h>
#include <IO.h>
#include <Memory.h>
#include <String.h>
#include <Keyboard.h>

#define MAX_KEYBOARD_BUFFER 100 //in bytes
char ReadedString[MAX_KEYBOARD_BUFFER];
unsigned short ReadedCount=0;
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
void (* AppRecieverCallBack)(char *ReadedString);
char KeyboardBlocked=0;

void DisableKeyboard()
{
  KeyboardBlocked=1;
}
void EnableKeyboard()
{
  KeyboardBlocked=0;
}

void KeyboardIHandler(struct regs *r)
{
   if(KeyboardBlocked)return;
    unsigned char scancode;

    scancode = ReadByteFromPort(0x60);

   //elcondition dh hayt7a2a2 lamma el user y Release el Button
    if (scancode & 0x80)
    {
    }
    else
    {
    	unsigned char Character=kbdus[scancode];
    	if(Character=='\n')
    	{
    	  //Pass Readed String To Reader If Exists;

        if(AppRecieverCallBack)
        {
           AppRecieverCallBack(ReadedString);
           ClearKBBuffer();
        }
    	  //CursorToNextLine();
    	  //Stop();
    	}
    	else if(Character=='\b'&& ReadedCount>0)
          {
               ReadedString[--ReadedCount]=0;
               DeleteChar();
          }
    	 else if(isChar(Character)||isNumber(Character)||Character==' ')
          {
             if(ReadedCount<MAX_KEYBOARD_BUFFER-1)
             {
               ReadedString[ReadedCount]=Character;
               ReadedCount++;
               OutPutChar(Character);
             }
             //if buffer is full do nothing

          }
      }
}

/*Install the keyboard handler into IRQ1 */
void InstallKeyBoard()
{
    InstallIRQHandler(1, KeyboardIHandler);
    ClearKBBuffer();
}
void ClearKBBuffer()
{

    MemorySetToValueByte(ReadedString,0,MAX_KEYBOARD_BUFFER);
    ReadedCount=0;
}

//el kernel bta3na haysta'3al 3an 6aree2 el call back mn el interrupt diect 3ashan el wa2t
//elly 3ayz el keyboard input hay3'yar el method elly hanadeha lamma y7sal Press 3ala el (ENTER)
//dh msh sa7 bas sare3 3ashan tasleem el mashroo3 ^_^
void SetAppReciever(void (* AppReciever)(char *ReadedString))
{
    AppRecieverCallBack = AppReciever;
}
