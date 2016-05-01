#include <Apps.Main.h>
#include <System.h>
#include <String.h>
#include <Memory.h>
#include <VGA.h>
#include <Keyboard.h>
#include <RTC.h>


#define READ_BUFFER_SIZE 512
char  ReadedBuffer[READ_BUFFER_SIZE];//4iKB Buffer
char Readed=0;
char * LinePrefix="CU FOS OS Basic Console >\0";
char * HelpString="===========================CU FOS OS Basic Console Help=========================\n-Command List with short Discrption:\n---->\"clear\" or \"clr\" to Clear The Screen.\n---->\"funny\" to run funny App. (Play With Screen Colors Exit After 10 Seconds).\n---->\"restart\", \"reset\" or \"rst\" to Restart The Machine.\n---->\"date\", \"time\" or \"datetime\" to Show Current System Date Time.\n---->\"help\" or \"hlp\"  to show This message.\0";
void StartAppMain(char* Params)
{
  //install Keyboard Reciever;
  SetAppReciever(RecieveFromKeyboardHandler);

    ConsoleNewLine();
    while(1)
    {
      ReadString();
      if(StringLength(ReadedBuffer)==0){ConsoleNewLine();continue;}
      if(SearchString(ReadedBuffer,"restart\0")||SearchString(ReadedBuffer,"reset\0")||SearchString(ReadedBuffer,"rst\0"))
      {
        ClearReadedBuffer();
        Restart();
      }
      else if (SearchString(ReadedBuffer,"clear\0")||SearchString(ReadedBuffer,"clr\0"))
      {
        ClearScreen();
        ConsoleOutput(LinePrefix);
        UpdateDeleteToPosition();
        ClearReadedBuffer();
        continue;
      }
      else if(SearchString(ReadedBuffer,"help\0")||SearchString(ReadedBuffer,"hlp\0"))
      {
        ClearScreen();
        ConsoleOutput(HelpString);
      }
      else if (SearchString(ReadedBuffer,"date\0")||SearchString(ReadedBuffer,"time\0")||SearchString(ReadedBuffer,"datetime\0"))
      {
          ConsoleNewLine();
          ConsoleOutput("Current System Date Time: \0");
          ConsoleOutput(GetDateTime());
      }
      else
      {
        ConsoleNewLine();
        ConsoleOutputError("ERROR:[\0");
        ConsoleOutputError(ReadedBuffer);
        ConsoleOutputError("]\0");
        ConsoleOutput(" INVALID COMMAND! for Help Type \"help\" or \"hlp\" then Press <ENTER>\0");
      }
      ClearReadedBuffer();
      ConsoleNewLine();
    }

}
//awel matsta2bl m el keyboard  t3'yar el flag 3ashan el ReadString Tkamel
void RecieveFromKeyboardHandler(char * ReadedString)
{
   CopyMemory(ReadedString,ReadedBuffer,(unsigned)StringLength(ReadedString));
   Readed=1;
}
void ReadString()
{
   while(!Readed);
   Readed=0;
}
void ClearReadedBuffer()
{
  MemorySetToValueByte(ReadedBuffer,0,READ_BUFFER_SIZE);
}
void ConsoleOutput(char * s)
{
  DisableKeyboard();
  PrintString(s);
  EnableKeyboard();
}
extern int MinPositionToDelete;
extern int CurrentCursor;

void ConsoleOutputError(char *s)
{
  DisableKeyboard();
  PrintStringError(s);
  EnableKeyboard();
}
void ConsoleNewLine()
{
  ConsoleOutput("\nCU FOS OS Main Console >\0");
  UpdateDeleteToPosition();
}
void UpdateDeleteToPosition()
{
   MinPositionToDelete=CurrentCursor;
}
